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

	// 메뉴
	HMENU		m_hMenu; // Tool Scene 에서만 사용		

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

public:
	void DockMenu();
	void DividMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

	POINT GetResolution() { return m_ptResolution; }
};

