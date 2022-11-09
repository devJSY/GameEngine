#include "global.h"

#include "CScene_SceneTool.h"
#include "CResMgr.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CAnimation.h"

CScene_SceneTool::CScene_SceneTool()
	: m_TexBackGround(nullptr)
	, m_TexForeGround(nullptr)
	, m_BackGroundAnim(nullptr)
	, m_ForeGroundAnim(nullptr)
{
}

CScene_SceneTool::~CScene_SceneTool()
{
	if (nullptr != m_BackGroundAnim)
	{
		delete m_BackGroundAnim;
	}

	if (nullptr != m_ForeGroundAnim)
	{
		delete m_ForeGroundAnim;
	}
}

void CScene_SceneTool::update()
{
	CScene::update();

	if (KEY_AWAY(KEY::LSHIFT))
	{
		ChangeScene(SCENE_TYPE::START);
	}

	if (KEY_AWAY(KEY::ENTER))
	{
		LoadBackGround();
	}
}

void CScene_SceneTool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_TexBackGround)
	{
		tAnimFrm tAnim = m_BackGroundAnim->GetFrame(0);

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)tAnim.vSlice.x
			, (int)tAnim.vSlice.y
			, m_TexBackGround->GetDC()
			, (int)tAnim.vLT.x
			, (int)tAnim.vLT.y
			, SRCCOPY);
	}

	//CScene::render(_dc);

	
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
}

void CScene_SceneTool::LoadBackGround()
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
	strTileFolder += L"Animation\\BackGround";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_TexBackGround = CResMgr::GetInst()->LoadTexture(L"BackGround", L"Texture\\BackGround.bmp");

		if (nullptr != m_BackGroundAnim)
		{
			delete m_BackGroundAnim;
		}

		m_BackGroundAnim = new CAnimation;

		m_BackGroundAnim->Load(strRelativePath);

		// 카메라 위치 초기화
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));
	}
}

void CScene_SceneTool::LoadForeGround()
{
}
