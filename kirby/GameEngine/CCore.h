#pragma once

class CCore
{
	SINGLE(CCore);

private:
	HWND	m_hWnd;			// ���� ������ �ڵ�
	HDC		m_dc;			// ���� ������ DC
	POINT	m_ptResloution; // ������ �ػ�

public:
	int init(HWND _hWnd, POINT _ptResloution);
	void progress();
};

