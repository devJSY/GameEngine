#include "global.h"
#include "CScene_Animation_Tool.h"

#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CCamera.h"
#include "CSceneMgr.h"
#include "CCore.h"
#include "CPathMgr.h"

#include "Kirby.h"

#include "SelectGDI.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimPlayer.h"


CScene_Animation_Tool::CScene_Animation_Tool()
	: m_pTex(nullptr)
	, m_DragTrig(false)
	, CurAinmData{}
{
}

CScene_Animation_Tool::~CScene_Animation_Tool()
{
}

void CScene_Animation_Tool::update()
{
	CScene::update();

	if (KEY_TAP(KEY::RBTN))
	{
		m_vTapPos = MOUSE_POS;
		m_DragTrig = true;
		vAccPos = CCamera::GetInst()->GetLookAt();	// 클릭 당시 위치 값 저장

		CurAinmData = {};	// 재 클릭시 현재 애니메이션 초기화
	}

	if (KEY_AWAY(KEY::RBTN))
	{
		m_vAwayPos = MOUSE_POS;
		m_DragTrig = false;

		// 슬라이스 사이즈 저장
		CurAinmData.vSlice = (m_vTapPos - m_vAwayPos) - vCamDist;
		CurAinmData.vSlice.Vec2_abs();

		// 좌상단 절대값 저장
		CurAinmData.vLT = CCamera::GetInst()->GetRealPos(m_vTapPos - vCamDist);
		//CurAinmData.vLT.Vec2_abs();

		// 우하단 절대값 저장
		CurAinmData.vRB = CCamera::GetInst()->GetRealPos(m_vAwayPos);
		//CurAinmData.vRB.Vec2_abs();		

		// 드래그 위치에 따라 좌상단, 우하단 위치 결정
		if (CurAinmData.vLT.x > CurAinmData.vRB.x )
		{
			float fTemp = CurAinmData.vLT.x;
			CurAinmData.vLT.x = CurAinmData.vRB.x;
			CurAinmData.vRB.x = fTemp;
		}

		if (CurAinmData.vLT.y > CurAinmData.vRB.y)
		{
			float fTemp = CurAinmData.vLT.y;
			CurAinmData.vLT.y = CurAinmData.vRB.y;
			CurAinmData.vRB.y = fTemp;
		}

		// 마우스 좌표에 따른 지정한 범위의 프레임 데이터 벡터에 저장
		//frameData.push_back(CurAinmData);
	}

	// 클릭 당시 위치값과 현재 위치값의 차이, 즉 카메라 이동량을 구함
	vCamDist = CCamera::GetInst()->GetLookAt() - vAccPos;

	if (KEY_AWAY(KEY::SPACE))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Animation_Tool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_pTex)
	{
		int iWidth = m_pTex->Width();
		int iHeight = m_pTex->Height();

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)iWidth
			, (int)iHeight
			, m_pTex->GetDC()
			, 0, 0, SRCCOPY);
	}

		
	if (m_DragTrig)
	{
		Vec2 vMousePos = MOUSE_POS;

		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::GREEN);

		Vec2 vTagPos = CCamera::GetInst()->GetRenderPos(m_vTapPos);

		Rectangle(_dc
			, (int)(m_vTapPos.x - vCamDist.x)	// 클릭한 순간 부터 카메라 영향 받음
			, (int)(m_vTapPos.y - vCamDist.y)	// 클릭한 순간 부터 카메라 영향 받음
			, (int)vMousePos.x
			, (int)vMousePos.y);
	}

	// 생성한 프레임 렌더링
	//for (size_t i = 0; i < frameData.size(); ++i)
	//{
	//	Vec2 vLT = CCamera::GetInst()->GetRenderPos(frameData[i].vLT);
	//	Vec2 vRB = CCamera::GetInst()->GetRenderPos(frameData[i].vRB);

	//	Rectangle(_dc
	//		, (int)vLT.x	
	//		, (int)vLT.y	
	//		, (int)vRB.x
	//		, (int)vRB.y);
	//}

	if (CurAinmData.vLT != Vec2(0.f, 0.f))
	{
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::GREEN);

		// 현재 프레임 렌더링
		Vec2 vLT = CCamera::GetInst()->GetRenderPos(CurAinmData.vLT);
		Vec2 vRB = CCamera::GetInst()->GetRenderPos(CurAinmData.vRB);

		Rectangle(_dc
			, (int)vLT.x
			, (int)vLT.y
			, (int)vRB.x
			, (int)vRB.y);
	}

	CScene::render(_dc);
}

void CScene_Animation_Tool::Enter()
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"AnimTex", L"Texture\\KirbyRight.bmp");

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(Vec2(vResolution /2.f ));
	CCamera::GetInst()->SetMovsSpeed(800.f);

	CObject* PlayAnim = new CAnimPlayer;
	PlayAnim->SetName(L"PlayAnim");
	PlayAnim->SetPos(Vec2(1100.f, 200.f));

	EnterAddObject(PlayAnim, GROUP_TYPE::PLAYER);
}

void CScene_Animation_Tool::Exit()
{
	DeleteAll();
}

void CScene_Animation_Tool::SaveAnimation(UINT _FrameCount, const wchar_t* _Name, const wchar_t* _FileName, float _fDuration)
{
	// 애니메이션 생성및 저장
	CAnimation SaveAnim;

	wstring AnimAddress = L"animation\\";
	AnimAddress += _FileName;
	AnimAddress += L".anim";

	CurAinmData.vLT = CurAinmData.vLT.Vec2_abs();
	CurAinmData.vRB = CurAinmData.vRB.Vec2_abs();

	SaveAnim.Create(m_pTex, CurAinmData.vLT, Vec2(CurAinmData.vSlice.x / _FrameCount, CurAinmData.vSlice.y), Vec2(CurAinmData.vSlice.x / _FrameCount, 0.f), _fDuration, _FrameCount);
	SaveAnim.SetName(_Name);
	SaveAnim.Save(AnimAddress);
}

void CScene_Animation_Tool::LoadAnimation(const wchar_t* _Name, const wchar_t* _FileName)
{
	wstring AnimAddress = L"animation\\";
	AnimAddress += _FileName;
	AnimAddress += L".anim";

	CObject* PlayAnim = nullptr;

	const vector<CObject*>& objvec =  GetGroupObject(GROUP_TYPE::PLAYER);

	for (size_t i = 0; i < objvec.size(); ++i)
	{
		if (L"PlayAnim" == objvec[i]->GetName())
		{
			PlayAnim = objvec[i];
		}
	}

	assert(PlayAnim);

	((CAnimPlayer*)PlayAnim)->SetAnimation(AnimAddress, _Name, true);
}

void CScene_Animation_Tool::LoadTexture()
{
	wchar_t szName[256] = {};
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0BITMAP\0*.bmp\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"Texture";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_pTex = CResMgr::GetInst()->LoadTexture(strRelativePath, strRelativePath);

		// 카메라 위치 초기화
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));
	}
}



// ======================
// Anim Save Window Proc
// ======================
INT_PTR CALLBACK AnimSave(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t AnimName[256] = {};
			wchar_t AnimFileName[256] = {};
			UINT AnimFrameCount = GetDlgItemInt(hDlg, IDC_FRAME_COUNT, nullptr, false);
			float AnimDuration = (float)GetDlgItemInt(hDlg, IDC_ANIM_DURATION, nullptr, false);

			// ms 단위로 변경
			AnimDuration /= 1000.f;

			GetDlgItemText(hDlg, IDC_ANIM_NAME, AnimName, 256);
			GetDlgItemText(hDlg, IDC_ANIM_ADDRESS, AnimFileName, 256);


			// 입력이 없었을경우 아무것도 안하고 종료
			if ('\0' == AnimName[0] || '\0' == AnimFileName[0] || 0 == AnimFrameCount || 0.f == AnimDuration)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// CScene_Animation_Tool 확인
			CScene_Animation_Tool* pToolScene = dynamic_cast<CScene_Animation_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveAnimation(AnimFrameCount, AnimName, AnimFileName, AnimDuration);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK AnimLoad(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			wchar_t AnimName[256] = {};
			wchar_t AnimFileName[256] = {};

			GetDlgItemText(hDlg, IDC_ANIM_NAME, AnimName, 256);
			GetDlgItemText(hDlg, IDC_ANIM_ADDRESS, AnimFileName, 256);
			
			// 입력이 없었을경우 아무것도 안하고 종료
			if ('\0' == AnimName[0] || '\0' == AnimFileName[0])
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// CScene_Animation_Tool 확인
			CScene_Animation_Tool* pToolScene = dynamic_cast<CScene_Animation_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadAnimation(AnimName, AnimFileName);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
