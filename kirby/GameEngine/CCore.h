#pragma once

class CCore
{
	SINGLE(CCore);

private:
	HWND		m_hWnd;			// ���� ������ �ڵ�
	HDC			m_dc;			// ���� ������ DC
	POINT		m_ptResolution; // ������ �ػ�

	HBITMAP		m_hBit;
	HDC			m_memDC;

public:
	int init(HWND _hWnd, POINT _ptResloution);
	void progress();
};

