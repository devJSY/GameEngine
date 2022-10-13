#pragma once

class CCore :
	public CRoot
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// ���� ������ �ڵ�
	HDC			m_hDC;			// ���� ������ DC
	POINT		m_ptResolution; // ������ �ػ�

	HBITMAP		m_hBit;			// ���� ���۸��� ��Ʈ��
	HDC			m_memDC;		// ���� ���۸��� DC

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

