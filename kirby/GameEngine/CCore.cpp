#include "global.h"
#include "CCore.h"

#include "CObject.h"

#include "CTexture.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CEventMgr.h"
#include "CPathMgr.h"
#include "CColliderMgr.h"
#include "GDIMgr.h"
#include "CResMgr.h"


CCore::CCore()
	: m_hWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
{	
}

CCore::~CCore()
{
	// �������ڵ�, DC ����
	ReleaseDC(m_hWnd, m_hDC);
}


int CCore::init(HWND _hWnd, POINT _ptResloution)
{
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);
	m_ptResolution = _ptResloution;

	// ������ ũ��, ��ġ ����
	RECT rt = { 0, 0, m_ptResolution.x, m_ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, HWND_TOP, 100, 100, rt.right- rt.left, rt.bottom - rt.top, 0);

	// ���� ���۸�
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	// �Ŵ��� �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	GDIMgr::GetInst()->CreateBrushPen();
	CSceneMgr::GetInst()->init();

	return S_OK;
}

void CCore::progress()
{
	// ȭ�� Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Manager upate
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CSceneMgr::GetInst()->update();
	CColliderMgr::GetInst()->upadte();

	// Manager render
	CTimeMgr::GetInst()->render(m_pMemTex->GetDC());
	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());

	// Dead üũ�� Object ����
	CSceneMgr::GetInst()->DeadObjectErase();

	// m_hDC �� m_memDC�� �׷��� ��Ʈ���� �Ű� ��´�
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);


	// �̺�Ʈ ó��
	CEventMgr::GetInst()->update();
}
