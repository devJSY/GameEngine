#include "global.h"
#include "CCore.h"


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
	// �������ڵ�, DC �赥
	ReleaseDC(m_hWnd, m_hDC);

	// ���� ���۸��� ��Ʈ��, DC ����
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

}


int CCore::init(HWND _hWnd, POINT _ptResloution)
{
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);
	m_ptResolution = _ptResloution;

	// ������ ũ��, ��ġ ����
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, HWND_TOP, 100, 100, rt.right- rt.left, rt.bottom - rt.top, 0);

	// ���� ���۸�
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	// m_hBit �ڵ� ����
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	return S_OK;
}

void CCore::progress()
{
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	Rectangle(m_memDC, 0, 0, 50, 50);

	// m_hDC �� m_memDC�� �׷��� ��Ʈ���� �Ű� ��´�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_memDC, 0, 0, SRCCOPY);	
}
