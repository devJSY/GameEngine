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
#include "CScene_SceneTool.h"


CScene_Stage::CScene_Stage()
	: m_tStageConf{}
{
}

CScene_Stage::~CScene_Stage()
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

	CScene::render(_dc);
}

void CScene_Stage::Enter()
{
	// 텍스쳐 설정
	Load(L"Stage_01");

	CCore::GetInst()->DividMenu();

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	CObject* pKirby = new Kirby;
	pKirby->SetName(L"Kirby");
	pKirby->SetPos(Vec2(640.f, 384.f));
	pKirby->SetScale(Vec2(100.f, 100.f));

	EnterAddObject(pKirby, GROUP_TYPE::PLAYER);

	CColliderMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	CCamera::GetInst()->SetTarget(pKirby);

	start();
}

void CScene_Stage::Exit()
{
	CCamera::GetInst()->ReleaseTarget();
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
	FScanf(szBuff, pFile);

	// BackGround Texture Name
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;
	FScanf(szBuff, pFile);

	// BackGround Texture Path
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	FScanf(szBuff, pFile);

	wstring wstr = wstring(str.begin(), str.end());
	wstring wScenePath = wstring(ScenePath.begin(), ScenePath.end());

	// 텍스쳐 설정
	m_tStageConf.TexBackGround = CResMgr::GetInst()->LoadTexture(wstr, wScenePath);

	// BackGround Path 
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	FScanf(szBuff, pFile);
	m_tStageConf.BackGroundPath = wstring(ScenePath.begin(), ScenePath.end());


	if (nullptr != m_tStageConf.BackGroundAnim)
	{
		delete m_tStageConf.BackGroundAnim;
	}

	m_tStageConf.BackGroundAnim = new CAnimation;

	m_tStageConf.BackGroundAnim->Load(m_tStageConf.BackGroundPath);

	// ForeGround Texture Path
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;
	FScanf(szBuff, pFile);

	// ForeGround Texture Path
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	FScanf(szBuff, pFile);

	wstr = wstring(str.begin(), str.end());
	wScenePath = wstring(ScenePath.begin(), ScenePath.end());

	// 텍스쳐 설정
	m_tStageConf.TexForeGround = CResMgr::GetInst()->LoadTexture(wstr, wScenePath);

	// ForeGround Path
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	ScenePath = szBuff;
	FScanf(szBuff, pFile);
	m_tStageConf.ForeGroundPath = wstring(ScenePath.begin(), ScenePath.end());

	if (nullptr != m_tStageConf.ForeGroundAnim)
	{
		delete m_tStageConf.ForeGroundAnim;
	}

	m_tStageConf.ForeGroundAnim = new CAnimation;

	m_tStageConf.ForeGroundAnim->Load(m_tStageConf.ForeGroundPath);

	// Scene Offset
	FScanf(szBuff, pFile);
	fscanf_s(pFile, "%f %f", &m_tStageConf.SceneOffset.x, &m_tStageConf.SceneOffset.y);
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	// ===========
	// Ground 생성
	// ===========

	int TileCount = 0;

	FScanf(szBuff, pFile);// [Tile Object Count]
	fscanf_s(pFile, "%d", &TileCount);  // Tile Object Count 읽기
	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	int Idx;
	string strIdx;
	wstring strName;
	size_t skipPos;
	Vec2 vVec;
	CGround* pGround = nullptr;

	// Generate Ground Object
	for (int i = 0; i < TileCount; ++i)
	{
		// Ground Name
		FScanf(szBuff, pFile); // [Tile Name] 
		FScanf(szBuff, pFile); // Tile Name 읽기
		str = szBuff;
		skipPos = str.rfind('_'); // 이름중 Tile_ 생략
		strIdx = str.substr(skipPos + 1);

		strName = L"Ground_";
		strName += wstring(strIdx.begin(), strIdx.end());
		

		pGround = new CGround;

		pGround->SetName(strName);

		// Ground Position
		FScanf(szBuff, pFile);
		fscanf_s(pFile, "%f %f", &vVec.x, &vVec.y);
		FScanf(szBuff, pFile);
		pGround->SetPos(vVec);

		// Ground Scale
		FScanf(szBuff, pFile);
		fscanf_s(pFile, "%f %f", &vVec.x, &vVec.y);
		pGround->SetScale(vVec);
		FScanf(szBuff, pFile);
		FScanf(szBuff, pFile);

		pGround->start();

		CreateObject(pGround, GROUP_TYPE::GROUND);
	}

	fclose(pFile);	// 파일 스트림 종료
}