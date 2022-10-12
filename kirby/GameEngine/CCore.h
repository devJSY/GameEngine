#pragma once

class CCore
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// 메인 윈도우 핸들
	HDC			m_dc;			// 메인 윈도우 DC
	POINT		m_ptResolution; // 윈도우 해상도

	HBITMAP		m_hBit;
	HDC			m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResloution);
	void progress();
};

