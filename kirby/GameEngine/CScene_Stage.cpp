#include "global.h"
#include "CScene_Stage.h"

#include "CCore.h"
#include "Kirby.h"
#include "CGround.h"
#include "CAnimation.h"
#include "CTexture.h"

#include "CCamera.h"
#include "CColliderMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CResMgr.h"


CScene_Stage::CScene_Stage()
	: m_TexBackGround(nullptr)
	, m_TexForeGround(nullptr)
	, m_BackGroundAnim(nullptr)
	, m_ForeGroundAnim(nullptr)
{
}

CScene_Stage::~CScene_Stage()
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
}

void CScene_Stage::update()
{
	CScene::update();

	if (KEY_AWAY(KEY::LSHIFT))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Stage::render(HDC _dc)
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

void CScene_Stage::Enter()
{
	Load(L"Stage_01");

	CCore::GetInst()->DividMenu();

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	CObject* pKirby = new Kirby;
	pKirby->SetName(L"Kirby");
	pKirby->SetPos(Vec2(640.f, 384.f));
	pKirby->SetScale(Vec2(100.f, 100.f));

	EnterAddObject(pKirby, GROUP_TYPE::PLAYER);

	CGround* pGround = new CGround;
	pGround->SetName(L"Ground");
	pGround->SetPos(Vec2(640.f, 700.f));
	pGround->SetScale(Vec2(80000.f, 60.f));

	EnterAddObject(pGround, GROUP_TYPE::GROUND);

	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	CCamera::GetInst()->SetTarget(pKirby);

	start();
}

void CScene_Stage::Exit()
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

	DeleteAll();
}

void CScene_Stage::Load(const wstring& _strName)
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