#include "global.h"
#include "CCore.h"


CCore::CCore()
	: m_hWnd(nullptr)
	, m_dc(nullptr)
	, m_ptResolution{}
	, m_hBit(nullptr)
	, m_memDC(nullptr)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_dc);

}


int CCore::init(HWND _hWnd, POINT _ptResloution)
{
	m_hWnd = _hWnd;
	m_dc = GetDC(m_hWnd);
	m_ptResolution = _ptResloution;

	// 윈도우 크기, 위치 설정
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, HWND_TOP, 100, 100, rt.right- rt.left, rt.bottom - rt.top, 0);


	return S_OK;
}

void CCore::progress()
{
	//Rectangle(m_dc, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}
