#include "global.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_llCurCountl{}
	, m_llPrevCount{}
	, m_llFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
	, m_iFPS(0)

{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// �̹� ������ ī��Ʈ ��
	QueryPerformanceCounter(&m_llCurCountl);

	// �̹� ������ �󵵼� 
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	// �̹� ������ ī��Ʈ ��
	QueryPerformanceCounter(&m_llCurCountl);

	// �̹� ������ �󵵼� 
	QueryPerformanceFrequency(&m_llFrequency);

	// DT = ���� ������ ī��Ʈ - ���� ������ ī��Ʈ  / �󵵼� 
	m_dDT = (double)(m_llCurCountl.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;

	// ���� ������ ī��Ʈ ���� ���� ������ ī��Ʈ�� ������Ʈ
	m_llPrevCount = m_llCurCountl;


// �ִ� 60������ ����
#ifdef _DEBUG
	if (m_dDT > (1.f / 60.f))
		m_dDT = (1.f / 60.f);
#endif
}

void CTimeMgr::render(HDC _dc)
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ����

	if (m_dAcc > 1.f)
	{
		// 1 �� ���� ������ �� = FPS
		m_iFPS = m_iCallCount;

		m_dAcc = 0;
		m_iCallCount = 0;

		// ������ �̸� �� �޾ƿ���
		wchar_t strBuffer[255] = {};
		LoadString(nullptr, IDC_GAMEENGINE, strBuffer, 255);

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"%s FPS : %d, DT : %lf", strBuffer, m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
