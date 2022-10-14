#include "global.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CEventMgr.h"

CCore::CCore()
	: m_hWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_hBit(nullptr)
	, m_memDC(nullptr)
{	
}

CCore::~CCore()
{
	// 윈도우핸들, DC 삭제
	ReleaseDC(m_hWnd, m_hDC);

	// 더블 버퍼링용 비트맵, DC 삭제
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	// m_hBit 핸들 설정
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	// 매니저 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress()
{
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);	

	// Manager upate
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();

	// Manager render
	CTimeMgr::GetInst()->render(m_memDC);
	CSceneMgr::GetInst()->render(m_memDC);

	// m_hDC 에 m_memDC에 그려진 비트맵을 옮겨 담는다
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);


	// 이벤트 처리
	CEventMgr::GetInst()->update();
}
