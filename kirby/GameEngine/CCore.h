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

public:
	int init(HWND _hWnd, POINT _ptResloution);
	void progress();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }

	POINT GetResolution() { return m_ptResolution; }
};

