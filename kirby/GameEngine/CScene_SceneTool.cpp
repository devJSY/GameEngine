#include "global.h"
#include "CScene_SceneTool.h"

#include "CTexture.h"
#include "CAnimation.h"
#include "CTile.h"


#include "CResMgr.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "SelectGDI.h"
#include "CSceneMgr.h"



CScene_SceneTool::CScene_SceneTool()
	: m_tStageConf{}
	, m_DragTrig(false)
{
}

CScene_SceneTool::~CScene_SceneTool()
{
	if (nullptr != m_tStageConf.BackGroundAnim)
	{
		delete m_tStageConf.BackGroundAnim;
	}

	if (nullptr != m_tStageConf.ForeGroundAnim)
	{
		delete m_tStageConf.ForeGroundAnim;
	}
}

void CScene_SceneTool::update()
{
	CScene::update();

	if (KEY_AWAY(KEY::LSHIFT))
	{
		ChangeScene(SCENE_TYPE::START);
	}

	if (KEY_HOLD(KEY::LBTN))
	{
		m_tStageConf.SceneOffset.y -= MOUSE_POS.y - m_vPrevMousePos.y;
	}

	// 오브젝트 생성
	if (KEY_TAP(KEY::RBTN))
	{
		m_DragTrig = true;
		m_vTapPos = MOUSE_POS;
		m_vAccPos = CCamera::GetInst()->GetLookAt();	// 클릭 당시 위치 값 저장
	}

	if (KEY_AWAY(KEY::RBTN))
	{
		m_DragTrig = false;
		m_vAwayPos = MOUSE_POS;

		Vec2 vLT = m_vTapPos;
		Vec2 vRB = m_vAwayPos;
		
		// 카메라 이동거리 만큼 체크박스 확장 적용
		vRB += m_vCamDist;

		// 드래그 위치에 따라 좌상단, 우하단 위치 결정
		if (vLT.x > vRB.x)
		{
			float fTemp = vLT.x;
			vLT.x = vRB.x;
			vRB.x = fTemp;
		}

		if (vLT.y > vRB.y)
		{
			float fTemp = vLT.y;
			vLT.y = vRB.y;
			vRB.y = fTemp;
		}	

		// 카메라 이동거리 더해준만큼 다시 빼서 체크박스 위치 조정
		vLT -= m_vCamDist;
		vRB -= m_vCamDist;

		TileDetectCheck(vLT, vRB);
	}

	
	m_vPrevMousePos = MOUSE_POS;
	m_vCamDist = CCamera::GetInst()->GetLookAt() - m_vAccPos;
}

void CScene_SceneTool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_tStageConf.BackGroundAnim)
	{
		tAnimFrm tAnim = m_tStageConf.BackGroundAnim->GetFrame(0);

		Vec2 vRenderPos = Vec2(0.f, 0.f);	// ( 0 , 0 ) 부터 고정 렌더링
		Vec2 vResolution = CCore::GetInst()->GetResolution();

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)(vResolution.x + abs(vRenderPos.x)) // 현재 화면만큼만 잘라내서 가져옴
			, (int)(vResolution.y + abs(vRenderPos.y))
			, m_tStageConf.TexBackGround->GetDC()
			, (int)tAnim.vLT.x
			, (int)tAnim.vLT.y
			, SRCCOPY);
	}

	if (nullptr != m_tStageConf.ForeGroundAnim)
	{
		tAnimFrm tAnim = m_tStageConf.ForeGroundAnim->GetFrame(0);

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링
		Vec2 vResolution = CCore::GetInst()->GetResolution();

		TransparentBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)(vResolution.x + abs(vRenderPos.x)) // 현재 화면만큼만 잘라내서 가져옴
			, (int)(vResolution.y + abs(vRenderPos.y))
			, m_tStageConf.TexForeGround->GetDC()
			, (int)(tAnim.vLT.x + m_tStageConf.SceneOffset.x)
			, (int)(tAnim.vLT.y + m_tStageConf.SceneOffset.y)
			, (int)(vResolution.x + abs(vRenderPos.x)) // 현재 화면만큼만 잘라내서 가져옴
			, (int)(vResolution.y + abs(vRenderPos.y))
			, RGB(0, 18, 127));
	}

	if (m_DragTrig)
	{
		Vec2 vMousePos = MOUSE_POS;

		SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI p(_dc, PEN_TYPE::RED);

		Vec2 vTagPos = CCamera::GetInst()->GetRenderPos(m_vTapPos);

		Rectangle(_dc
			, (int)(m_vTapPos.x - m_vCamDist.x)	// 클릭한 순간 부터 카메라 영향 받음
			, (int)(m_vTapPos.y - m_vCamDist.y)	// 클릭한 순간 부터 카메라 영향 받음
			, (int)vMousePos.x
			, (int)vMousePos.y);
	}

	CScene::render(_dc);	
}

void CScene_SceneTool::Enter()
{
	CCore::GetInst()->DockMenu();

	// 카메라 위치 초기화
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));
	CCamera::GetInst()->SetMovsSpeed(800.f);

	// BackGround 초기화
	m_tStageConf.BackGroundPath = L"Animation\\BackGround\\1.anim";
	m_tStageConf.TexBackGround = CResMgr::GetInst()->LoadTexture(L"BackGround", L"Texture\\BackGround.bmp");

	if (nullptr != m_tStageConf.BackGroundAnim)
	{
		delete m_tStageConf.BackGroundAnim;
	}

	m_tStageConf.BackGroundAnim = new CAnimation;

	m_tStageConf.BackGroundAnim->Load(m_tStageConf.BackGroundPath);

	// ForeGround 초기화
	m_tStageConf.ForeGroundPath = L"Animation\\ForeGround\\1\\1.anim";
	m_tStageConf.TexForeGround = CResMgr::GetInst()->LoadTexture(L"ForeGround", L"Texture\\ForeGround.bmp");

	if (nullptr != m_tStageConf.ForeGroundAnim)
	{
		delete m_tStageConf.ForeGroundAnim;
	}

	m_tStageConf.ForeGroundAnim = new CAnimation;

	m_tStageConf.ForeGroundAnim->Load(m_tStageConf.ForeGroundPath);


	TileVecGenerate(m_tStageConf.ForeGroundAnim->GetFrame(0).vSlice.x, m_tStageConf.ForeGroundAnim->GetFrame(0).vSlice.y);
}

void CScene_SceneTool::Exit()
{
}


void CScene_SceneTool::TileDetectCheck(Vec2 _vLT, Vec2 _vRB)
{
	Vec2 vLT = _vLT;
	Vec2 vRB = _vRB;

	for (size_t i = 0; i < m_vTile.size(); ++i)
	{
		Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vTile[i]->GetPos());

		if (vLT.x < vPos.x && vRB.x > vPos.x
			&& vLT.y < vPos.y && vRB.y > vPos.y)
		{
			if (KEY_HOLD(KEY::CTRL))
			{
				((CTile*)m_vTile[i])->CheckingFalse();
			}
			else
			{
				((CTile*)m_vTile[i])->CheckingTrue();
			}
		}
	}
}

void CScene_SceneTool::TileVecGenerate(float _Width, float _Height)
{
	// 기존 타일 초기화
	if (!m_vTile.empty())
	{
		DeleteGroup(GROUP_TYPE::TILE);
		m_vTile.clear();
	}

	UINT iWidth = _Width / TILE_SIZE;
	UINT iHeight = _Height / TILE_SIZE;

	CTile* pTile = nullptr;

	for (int i = 0; i < iWidth; ++i)
	{
		for (int j = 0; j < iHeight; ++j)
		{
			pTile = new CTile;

			pTile->SetScale(Vec2(TILE_SIZE, TILE_SIZE));
			pTile->SetPos(Vec2(TILE_SIZE * i + (TILE_SIZE / 2.f), TILE_SIZE * j + (TILE_SIZE / 2.f)));

			int Idx = i * 10 + j;
			wstring TileName = L"Tile_";
			TileName += std::to_wstring(Idx);
			pTile->SetName(TileName);


			m_vTile.push_back(pTile);

			EnterAddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}












void CScene_SceneTool::LoadBackGround()
{
	wchar_t szName[256] = {};
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0ANIM\0*.anim\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"Animation\\BackGround";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		m_tStageConf.BackGroundPath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_tStageConf.TexBackGround = CResMgr::GetInst()->LoadTexture(L"BackGround", L"Texture\\BackGround.bmp");

		if (nullptr != m_tStageConf.BackGroundAnim)
		{
			delete m_tStageConf.BackGroundAnim;
		}

		m_tStageConf.BackGroundAnim = new CAnimation;

		m_tStageConf.BackGroundAnim->Load(m_tStageConf.BackGroundPath);

		// 카메라 위치 초기화
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));
	}
}

void CScene_SceneTool::LoadForeGround()
{
	wchar_t szName[256] = {};
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"All\0*.*\0ANIM\0*.anim\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"Animation\\ForeGround";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		m_tStageConf.ForeGroundPath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_tStageConf.TexForeGround = CResMgr::GetInst()->LoadTexture(L"ForeGround", L"Texture\\ForeGround.bmp");

		if (nullptr != m_tStageConf.ForeGroundAnim)
		{
			delete m_tStageConf.ForeGroundAnim;
		}

		m_tStageConf.ForeGroundAnim = new CAnimation;

		m_tStageConf.ForeGroundAnim->Load(m_tStageConf.ForeGroundPath);

		// Offset 초기화
		m_tStageConf.SceneOffset = Vec2(0.f, 0.f);

		// 카메라 위치 초기화
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));

		// 타일 재생성
		TileVecGenerate(m_tStageConf.ForeGroundAnim->GetFrame(0).vSlice.x, m_tStageConf.ForeGroundAnim->GetFrame(0).vSlice.y);
	}
}


void CScene_SceneTool::Save(const wstring& _strName)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"Animation\\Scene\\";
	strFilePath += _strName;
	strFilePath += L".scene";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");	// 파일 스트림 wb 방식으로 열기
	assert(pFile);

	// 이름 (데이터 직렬화)
	fprintf(pFile, "[Scene Name]\n");
	string strName = string(_strName.begin(), _strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// BackGround 텍스쳐
	fprintf(pFile, "[BackGround Texture Name]\n");
	strName = string(m_tStageConf.TexBackGround->GetKey().begin(), m_tStageConf.TexBackGround->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[BackGround Texture Path]\n");
	strName = string(m_tStageConf.TexBackGround->GetRelativePath().begin(), m_tStageConf.TexBackGround->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[BackGround Path]\n");
	strName = string(m_tStageConf.BackGroundPath.begin(), m_tStageConf.BackGroundPath.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// ForeGround 텍스쳐
	fprintf(pFile, "[ForeGround Texture Name]\n");
	strName = string(m_tStageConf.TexForeGround->GetKey().begin(), m_tStageConf.TexForeGround->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[ForeGround Texture Path]\n");
	strName = string(m_tStageConf.TexForeGround->GetRelativePath().begin(), m_tStageConf.TexForeGround->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[ForeGround Path Path]\n");
	strName = string(m_tStageConf.ForeGroundPath.begin(), m_tStageConf.ForeGroundPath.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// ========
	fprintf(pFile, "[Scene Offset]\n");
	fprintf(pFile, "%f %f\n", m_tStageConf.SceneOffset.x, m_tStageConf.SceneOffset.y);


	fclose(pFile);	// 파일 스트림 종료
}

void CScene_SceneTool::Load(const wstring& _strName)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"Animation\\Scene\\";
	strFilePath += _strName;
	strFilePath += L".scene";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");	// 파일 스트림 rb 방식으로 오픈
	assert(pFile);

	// 이름 (데이터 직렬화)
	string str, ScenePath;
	char szBuff[256] = {};

	// Scene Name
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	// BackGround
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;

	wstring wstr = wstring(str.begin(), str.end());
	wstring wScenePath = wstring(ScenePath.begin(), ScenePath.end());

	// 텍스쳐 설정
	m_tStageConf.TexBackGround = CResMgr::GetInst()->LoadTexture(wstr, wScenePath);

	// BackGround Path 
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	m_tStageConf.BackGroundPath = wstring(ScenePath.begin(), ScenePath.end());

	if (nullptr != m_tStageConf.BackGroundAnim)
	{
		delete m_tStageConf.BackGroundAnim;
	}

	m_tStageConf.BackGroundAnim = new CAnimation;

	m_tStageConf.BackGroundAnim->Load(m_tStageConf.BackGroundPath);

	// ForeGround
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;

	wstr = wstring(str.begin(), str.end());
	wScenePath = wstring(ScenePath.begin(), ScenePath.end());

	// 텍스쳐 설정
	m_tStageConf.TexForeGround = CResMgr::GetInst()->LoadTexture(wstr, wScenePath);

	// BackGround Path 
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	m_tStageConf.ForeGroundPath = wstring(ScenePath.begin(), ScenePath.end());

	if (nullptr != m_tStageConf.ForeGroundAnim)
	{
		delete m_tStageConf.ForeGroundAnim;
	}

	m_tStageConf.ForeGroundAnim = new CAnimation;

	m_tStageConf.ForeGroundAnim->Load(m_tStageConf.ForeGroundPath);

	FScanf(szBuff, pFile);
	fscanf_s(pFile, "%f %f", &m_tStageConf.SceneOffset.x, &m_tStageConf.SceneOffset.y);
	
	fclose(pFile);	// 파일 스트림 종료
}


// ======================
// Scene Tool Window Proc
// ======================
INT_PTR CALLBACK SceneSave(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

			GetDlgItemText(hDlg, IDC_SCENE_ADDRESS, AnimFileName, 256);

			// 입력이 없었을경우 아무것도 안하고 종료
			if ('\0' == AnimFileName[0])
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// CScene_AnimTool 확인
			CScene_SceneTool* pToolScene = dynamic_cast<CScene_SceneTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->Save(AnimFileName);

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

INT_PTR CALLBACK SceneLoad(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

			GetDlgItemText(hDlg, IDC_SCENE_ADDRESS, AnimFileName, 256);

			// 입력이 없었을경우 아무것도 안하고 종료
			if ('\0' == AnimFileName[0])
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// CScene_AnimTool 확인
			CScene_SceneTool* pToolScene = dynamic_cast<CScene_SceneTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->Load(AnimFileName);

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
