#include "global.h"
#include "CCore.h"

#include "CObject.h"

#include "CTexture.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CColliderMgr.h"
#include "GDIMgr.h"
#include "CResMgr.h"


CCore::CCore()
	: m_hWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
{	
}

CCore::~CCore()
{
	// 윈도우핸들, DC 삭제
	ReleaseDC(m_hWnd, m_hDC);
}


int CCore::init(HWND _hWnd, POINT _ptResloution)
{
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);
	m_ptResolution = _ptResloution;

	// 윈도우 크기, 위치 설정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, HWND_TOP, 100, 100, rt.right- rt.left, rt.bottom - rt.top, 0);

	// 이중 버퍼링
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// 매니저 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	GDIMgr::GetInst()->CreateBrushPen();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress()
{
	// 화면 Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Manager upate
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();
	CColliderMgr::GetInst()->upadte();

	// Manager render
	CTimeMgr::GetInst()->render(m_pMemTex->GetDC());
	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());

	// Dead 체크된 Object 삭제
	CSceneMgr::GetInst()->DeadObjectErase();

	// m_hDC 에 m_memDC에 그려진 비트맵을 옮겨 담는다
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);


	// 이벤트 처리
	CEventMgr::GetInst()->update();
}
