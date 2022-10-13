#pragma once

class CCore :
	public CRoot
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// 메인 윈도우 핸들
	HDC			m_hDC;			// 메인 윈도우 DC
	POINT		m_ptResolution; // 윈도우 해상도

	HBITMAP		m_hBit;			// 이중 버퍼링용 비트맵
	HDC			m_memDC;		// 이중 버퍼링용 DC

public:
	int init(HWND _hWnd, POINT _ptResloution);
	void progress();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	HDC GetMemoryDC() { return m_memDC; }

private:
	virtual void Root() {};
};

