#pragma once

class CTexture;
class CCore :
	public CRoot
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// ���� ������ �ڵ�
	HDC			m_hDC;			// ���� ������ DC
	POINT		m_ptResolution; // ������ �ػ�

	CTexture*	m_pMemTex;		// ���� ���۸� �� Texture

	// �޴�
	HMENU		m_hMenu; // Tool Scene ������ ���		

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

