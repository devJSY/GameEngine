#include "global.h"
#include "CScene_AnimTool.h"

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


CScene_AnimTool::CScene_AnimTool()
	: m_pTex(nullptr)
	, m_DragTrig(false)
	, m_CurAinmData{}
	, m_AnimAxis(0)
{
}

CScene_AnimTool::~CScene_AnimTool()
{
}

void CScene_AnimTool::update()
{
	CScene::update();

	if (KEY_TAP(KEY::RBTN))
	{
		m_vTapPos = MOUSE_POS;
		m_DragTrig = true;
		m_vAccPos = CCamera::GetInst()->GetLookAt();	// Ŭ�� ��� ��ġ �� ����

		m_CurAinmData = {};	// �� Ŭ���� ���� �ִϸ��̼� �ʱ�ȭ
	}

	if (KEY_AWAY(KEY::RBTN))
	{
		m_vAwayPos = MOUSE_POS;
		m_DragTrig = false;

		// �����̽� ������ ����
		m_CurAinmData.vSlice = (m_vTapPos - m_vAwayPos) - m_vCamDist;
		m_CurAinmData.vSlice.Vec2_abs();

		// �»�� ���밪 ����
		m_CurAinmData.vLT = CCamera::GetInst()->GetRealPos(m_vTapPos - m_vCamDist);

		// ���ϴ� ���밪 ����
		m_CurAinmData.vRB = CCamera::GetInst()->GetRealPos(m_vAwayPos);		

		// �巡�� ��ġ�� ���� �»��, ���ϴ� ��ġ ����
		if (m_CurAinmData.vLT.x > m_CurAinmData.vRB.x )
		{
			float fTemp = m_CurAinmData.vLT.x;
			m_CurAinmData.vLT.x = m_CurAinmData.vRB.x;
			m_CurAinmData.vRB.x = fTemp;
		}

		if (m_CurAinmData.vLT.y > m_CurAinmData.vRB.y)
		{
			float fTemp = m_CurAinmData.vLT.y;
			m_CurAinmData.vLT.y = m_CurAinmData.vRB.y;
			m_CurAinmData.vRB.y = fTemp;
		}
	}

	// ������ �巡�� �̵� ó��
	Vec2 vMousePos = MOUSE_POS;
	Vec2 CurAnimvLT = CCamera::GetInst()->GetRenderPos(m_CurAinmData.vLT);
	Vec2 CurAnimvRB = CCamera::GetInst()->GetRenderPos(m_CurAinmData.vRB);	

	if (CurAnimvLT.x <= vMousePos.x && vMousePos.x <= CurAnimvRB.x
		&& CurAnimvLT.y <= vMousePos.y && vMousePos.y <= CurAnimvRB.y)
	{
		if (KEY_HOLD(KEY::LBTN))
		{
			Vec2 vMouseDiff = MOUSE_POS - m_vPrevMousePos;
			Vec2 vCamDiff = CCamera::GetInst()->GetLookAt() - m_vPrevCamLookAt; 

			if (m_AnimAxis)
			{
				// X�� �̵�
				m_CurAinmData.vLT.x += vMouseDiff.x + vCamDiff.x;
				m_CurAinmData.vRB.x += vMouseDiff.x + vCamDiff.x;
			}
			else
			{
				// Y�� �̵�
				m_CurAinmData.vLT.y += vMouseDiff.y + vCamDiff.y;
				m_CurAinmData.vRB.y += vMouseDiff.y + vCamDiff.y;
			}
		}
	}

	if (KEY_AWAY(KEY::R))
	{
		m_AnimAxis = !m_AnimAxis;
	}

	if (KEY_AWAY(KEY::SPACE))
	{
		m_frameData.push_back(m_CurAinmData);
	}

	if (KEY_AWAY(KEY::CTRL))
	{
		m_frameData.clear();
	}

	// Ŭ�� ��� ��ġ���� ���� ��ġ���� ����, �� ī�޶� �̵����� ����
	m_vCamDist = CCamera::GetInst()->GetLookAt() - m_vAccPos;

	// ���� ������ ī�޶� ��ġ
	m_vPrevCamLookAt = CCamera::GetInst()->GetLookAt();	

	// ���� ������ ���콺 ��ġ 
	m_vPrevMousePos = MOUSE_POS;

	if (KEY_AWAY(KEY::LSHIFT))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_AnimTool::render(HDC _dc)
{
	// �ؽ��� ������
	if (nullptr != m_pTex)
	{
		Vec2 vResolution = CCore::GetInst()->GetResolution();

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) ���� �ؽ��� ������

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)(vResolution.x + abs(vRenderPos.x)) // ���� ȭ�鸸ŭ�� �߶󳻼� ������
			, (int)(vResolution.y + abs(vRenderPos.y))
			, m_pTex->GetDC()
			, 0, 0, SRCCOPY);
	}

		
	if (m_DragTrig)
	{
		Vec2 vMousePos = MOUSE_POS;

		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::RED);

		Vec2 vTagPos = CCamera::GetInst()->GetRenderPos(m_vTapPos);

		Rectangle(_dc
			, (int)(m_vTapPos.x - m_vCamDist.x)	// Ŭ���� ���� ���� ī�޶� ���� ����
			, (int)(m_vTapPos.y - m_vCamDist.y)	// Ŭ���� ���� ���� ī�޶� ���� ����
			, (int)vMousePos.x
			, (int)vMousePos.y);
	}

	// ������ ������ ������
	for (size_t i = 0; i < m_frameData.size(); ++i)
	{
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::GREEN);

		Vec2 vLT = CCamera::GetInst()->GetRenderPos(m_frameData[i].vLT);
		Vec2 vRB = CCamera::GetInst()->GetRenderPos(m_frameData[i].vRB);

		Rectangle(_dc
			, (int)vLT.x	
			, (int)vLT.y	
			, (int)vRB.x
			, (int)vRB.y);
	}

	// ���� ���� ���� ������
	if (m_CurAinmData.vLT != Vec2(0.f, 0.f))
	{
		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::RED);
		
		Vec2 vLT = CCamera::GetInst()->GetRenderPos(m_CurAinmData.vLT);
		Vec2 vRB = CCamera::GetInst()->GetRenderPos(m_CurAinmData.vRB);

		Rectangle(_dc
			, (int)vLT.x
			, (int)vLT.y
			, (int)vRB.x
			, (int)vRB.y);
	}

	CScene::render(_dc);
}

void CScene_AnimTool::Enter()
{
	CCore::GetInst()->DockMenu();

	m_pTex = CResMgr::GetInst()->LoadTexture(L"AnimTex", L"Texture\\KirbyRight.bmp");

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(Vec2(vResolution /2.f ));
	CCamera::GetInst()->SetMovsSpeed(800.f);

	CObject* PlayAnim = new CAnimPlayer;
	PlayAnim->SetName(L"PlayAnim");
	PlayAnim->SetPos(Vec2(1100.f, 200.f));

	EnterAddObject(PlayAnim, GROUP_TYPE::PLAYER);
}

void CScene_AnimTool::Exit()
{
	// ������ �����ߴ� ������ ������ �ʱ�ȭ
	m_frameData.clear();
	m_CurAinmData = {};

	DeleteAll();
}

void CScene_AnimTool::SaveAnimation(const wchar_t* _FileName, float _fDuration)
{
	// �ִϸ��̼� ������ ����
	CAnimation SaveAnim;

	wstring AnimAddress = L"animation\\";
	AnimAddress += _FileName;
	AnimAddress += L".anim";

	SaveAnim.SetTexture(m_pTex);

	for (size_t i = 0; i < m_frameData.size(); ++i)
	{
		m_frameData[i].vLT = m_frameData[i].vLT.Vec2_abs();
		m_frameData[i].vRB = m_frameData[i].vRB.Vec2_abs();

		SaveAnim.AddFrameVec(m_frameData[i].vLT, m_frameData[i].vSlice, _fDuration);
	}
	
	SaveAnim.SetName(_FileName);
	SaveAnim.Save(AnimAddress);
}

void CScene_AnimTool::LoadAnimation(const wchar_t* _FileName)
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

	((CAnimPlayer*)PlayAnim)->SetAnimation(AnimAddress, _FileName, true);
}

void CScene_AnimTool::LoadTexture()
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

		// ī�޶� ��ġ �ʱ�ȭ
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));

		// ������ �����ߴ� ������ ������ �ʱ�ȭ
		m_frameData.clear();
		m_CurAinmData = {};
	}
}


// ======================
// Anim Tool Window Proc
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
			wchar_t AnimFileName[256] = {};
			float AnimDuration = (float)GetDlgItemInt(hDlg, IDC_ANIM_DURATION, nullptr, false);

			// ms ������ ����
			AnimDuration /= 1000.f;

			GetDlgItemText(hDlg, IDC_ANIM_ADDRESS, AnimFileName, 256);


			// �Է��� ��������� �ƹ��͵� ���ϰ� ����
			if ('\0' == AnimFileName[0] || 0.f == AnimDuration)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// CScene_AnimTool Ȯ��
			CScene_AnimTool* pToolScene = dynamic_cast<CScene_AnimTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveAnimation(AnimFileName, AnimDuration);

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
			wchar_t AnimFileName[256] = {};

			GetDlgItemText(hDlg, IDC_ANIM_ADDRESS, AnimFileName, 256);

			// �Է��� ��������� �ƹ��͵� ���ϰ� ����
			if ('\0' == AnimFileName[0])
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// CScene_AnimTool Ȯ��
			CScene_AnimTool* pToolScene = dynamic_cast<CScene_AnimTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadAnimation(AnimFileName);

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
