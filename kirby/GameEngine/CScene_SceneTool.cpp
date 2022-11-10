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
	, m_tempdc(nullptr)
	, m_temphBit(nullptr)
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

	if (nullptr != m_tempdc)
	{
		DeleteDC(m_tempdc);
	}

	if (nullptr != m_ForeGroundAnim)
	{
		DeleteObject(m_ForeGroundAnim);
	}	
}

void CScene_SceneTool::update()
{
	CScene::update();

	if (KEY_AWAY(KEY::LSHIFT))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_SceneTool::render(HDC _dc)
{
	// 텍스쳐 렌더링
	if (nullptr != m_TexBackGround)
	{
		tAnimFrm tAnim = m_BackGroundAnim->GetFrame(0);

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링

		Vec2 vResolution = CCore::GetInst()->GetResolution();

		BitBlt(_dc
			, (int)vRenderPos.x
			, (int)vRenderPos.y
			, (int)vResolution.x
			, (int)vResolution.y
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
			, (int)vRenderPos.x + vResolution.x
			, (int)vRenderPos.y + vResolution.y
			, m_tempdc
			, (int)tAnim.vLT.x
			, (int)tAnim.vLT.y
			, (int)tAnim.vLT.x + vResolution.x
			, (int)tAnim.vLT.y + vResolution.y
			, RGB(0, 18, 127));
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
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		m_TexForeGround = CResMgr::GetInst()->LoadTexture(L"ForeGround", L"Texture\\ForeGround.bmp");

		if (nullptr != m_ForeGroundAnim)
		{
			delete m_ForeGroundAnim;
		}

		m_ForeGroundAnim = new CAnimation;

		m_ForeGroundAnim->Load(strRelativePath);

		// 카메라 위치 초기화
		Vec2 vResolution = CCore::GetInst()->GetResolution();
		CCamera::GetInst()->SetLookAt(Vec2(vResolution / 2.f));




		wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		strFilePath += L"Texture\\ForeGround.bmp";

		// 인자 경로의 파일을 읽어와서 m_hBit 비트맵 초기화
		m_temphBit = (HBITMAP)LoadImage(nullptr, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		assert(m_temphBit);

		// 이중 버퍼링용 DC생성
		m_tempdc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
		HBITMAP hPreveBlt = (HBITMAP)SelectObject(m_tempdc, m_temphBit);
		DeleteObject(hPreveBlt);




		tAnimFrm tAnim = m_ForeGroundAnim->GetFrame(0);

		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(Vec2(0.f, 0.f));	// ( 0 , 0 ) 부터 텍스쳐 렌더링
	}
}
