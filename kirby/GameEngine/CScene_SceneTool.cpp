#include "global.h"

#include "CScene_SceneTool.h"
#include "CResMgr.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "SelectGDI.h"


#include "CSceneMgr.h"

CScene_SceneTool::CScene_SceneTool()
	: m_TexBackGround(nullptr)
	, m_TexForeGround(nullptr)
	, m_BackGroundAnim(nullptr)
	, m_ForeGroundAnim(nullptr)
{
}

CScene_SceneTool::~CScene_SceneTool()
{
	if (nullptr != m_TexBackGround)
	{
		delete m_BackGroundAnim;

		m_BackGroundAnim = nullptr;
	}

	if (nullptr != m_ForeGroundAnim)
	{
		delete m_ForeGroundAnim;

		m_ForeGroundAnim = nullptr;
	}

	m_BackGroundPath = L"";
	m_ForeGroundPath = L"";

	m_SceneOffset = Vec2(0.f, 0.f);
	vPrevMousePos = Vec2(0.f, 0.f);
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
		m_SceneOffset.y -= MOUSE_POS.y - vPrevMousePos.y;
	}

	vPrevMousePos = MOUSE_POS;	
}

void CScene_SceneTool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_TexBackGround)
	{
		tAnimFrm tAnim = m_BackGroundAnim->GetFrame(0);

		//Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링

		Vec2 vRenderPos = Vec2(0.f, 0.f);	// ( 0 , 0 ) 부터 고정 렌더링
		Vec2 vResolution = CCore::GetInst()->GetResolution();

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)(vResolution.x + abs(vRenderPos.x)) // 현재 화면만큼만 잘라내서 가져옴
			, (int)(vResolution.y + abs(vRenderPos.y))
			, m_TexBackGround->GetDC()
			, (int)tAnim.vLT.x
			, (int)tAnim.vLT.y
			, SRCCOPY);
	}	

	if (nullptr != m_TexForeGround)
	{
		tAnimFrm tAnim = m_ForeGroundAnim->GetFrame(0);

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링
		Vec2 vResolution = CCore::GetInst()->GetResolution();

		TransparentBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)(vResolution.x + abs(vRenderPos.x)) // 현재 화면만큼만 잘라내서 가져옴
			, (int)(vResolution.y + abs(vRenderPos.y))
			, m_TexForeGround->GetDC()
			, (int)(tAnim.vLT.x + m_SceneOffset.x)
			, (int)(tAnim.vLT.y + m_SceneOffset.y)
			, (int)(vResolution.x + abs(vRenderPos.x)) // 현재 화면만큼만 잘라내서 가져옴
			, (int)(vResolution.y + abs(vRenderPos.y))
			, RGB(0, 18, 127));
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
}

void CScene_SceneTool::Exit()
{
	m_BackGroundPath = L"";
	m_ForeGroundPath = L"";

	m_SceneOffset = Vec2(0.f, 0.f);
	vPrevMousePos = Vec2(0.f, 0.f);
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
		m_BackGroundPath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_TexBackGround = CResMgr::GetInst()->LoadTexture(L"BackGround", L"Texture\\BackGround.bmp");

		if (nullptr != m_BackGroundAnim)
		{
			delete m_BackGroundAnim;
		}

		m_BackGroundAnim = new CAnimation;

		m_BackGroundAnim->Load(m_BackGroundPath);

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
		m_ForeGroundPath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_TexForeGround = CResMgr::GetInst()->LoadTexture(L"ForeGround", L"Texture\\ForeGround.bmp");

		if (nullptr != m_ForeGroundAnim)
		{
			delete m_ForeGroundAnim;
		}

		m_ForeGroundAnim = new CAnimation;

		m_ForeGroundAnim->Load(m_ForeGroundPath);

		// 카메라 위치 초기화
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));
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
	strName = string(m_TexBackGround->GetKey().begin(), m_TexBackGround->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[BackGround Texture Path]\n");
	strName = string(m_TexBackGround->GetRelativePath().begin(), m_TexBackGround->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[BackGround Path]\n");
	strName = string(m_BackGroundPath.begin(), m_BackGroundPath.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// ForeGround 텍스쳐
	fprintf(pFile, "[ForeGround Texture Name]\n");
	strName = string(m_TexForeGround->GetKey().begin(), m_TexForeGround->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[ForeGround Texture Path]\n");
	strName = string(m_TexForeGround->GetRelativePath().begin(), m_TexForeGround->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[ForeGround Path Path]\n");
	strName = string(m_ForeGroundPath.begin(), m_ForeGroundPath.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	// ========
	fprintf(pFile, "[Scene Offset]\n");
	fprintf(pFile, "%f %f\n", m_SceneOffset.x, m_SceneOffset.y);


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
	m_TexBackGround = CResMgr::GetInst()->LoadTexture(wstr, wScenePath);

	// BackGround Path 
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	m_BackGroundPath = wstring(ScenePath.begin(), ScenePath.end());

	if (nullptr != m_BackGroundAnim)
	{
		delete m_BackGroundAnim;
	}

	m_BackGroundAnim = new CAnimation;

	m_BackGroundAnim->Load(m_BackGroundPath);

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
	m_TexForeGround = CResMgr::GetInst()->LoadTexture(wstr, wScenePath);

	// BackGround Path 
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	m_ForeGroundPath = wstring(ScenePath.begin(), ScenePath.end());

	if (nullptr != m_ForeGroundAnim)
	{
		delete m_ForeGroundAnim;
	}

	m_ForeGroundAnim = new CAnimation;

	m_ForeGroundAnim->Load(m_ForeGroundPath);

	FScanf(szBuff, pFile);
	fscanf_s(pFile, "%f %f", &m_SceneOffset.x, &m_SceneOffset.y);
	
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
