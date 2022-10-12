#include "global.h"
#include "CCore.h"


CCore::CCore()
	: m_hWnd(nullptr)
	, m_dc(nullptr)
	, m_ptResloution{}


{

}

CCore::~CCore()
{

}


int CCore::init(HWND _hWnd, POINT _ptResloution)
{
	m_hWnd = _hWnd;
	m_ptResloution = _ptResloution;

	RECT rt = { 0, 0, m_ptResloution.x, m_ptResloution.y };




	return S_OK;
}

void CCore::progress()
{
}
