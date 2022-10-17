#pragma once

class CTexture;
class CCore :
	public CRoot
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// 메인 윈도우 핸들
	HDC			m_hDC;			// 메인 윈도우 DC
	POINT		m_ptResolution; // 윈도우 해상도

	CTexture*	m_pMemTex;		// 이중 버퍼링 용 Texture

public:
	int init(HWND _hWnd, POINT _ptResloution);
	void progress();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

	POINT GetResolution() { return m_ptResolution; }
};

