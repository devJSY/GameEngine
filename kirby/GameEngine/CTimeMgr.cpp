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
	// 이번 프레임 카운트 수
	QueryPerformanceCounter(&m_llCurCountl);

	// 이번 프레임 빈도수 
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	// 이번 프레임 카운트 수
	QueryPerformanceCounter(&m_llCurCountl);

	// 이번 프레임 빈도수 
	QueryPerformanceFrequency(&m_llFrequency);

	// DT = 현재 프레임 카운트 - 이전 프레임 카운트  / 빈도수 
	m_dDT = (double)(m_llCurCountl.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;

	// 현재 프레임 카운트 수를 이전 프레임 카운트로 업데이트
	m_llPrevCount = m_llCurCountl;


// 최대 60프레임 제한
#ifdef _DEBUG
	if (m_dDT > (1.f / 60.f))
		m_dDT = (1.f / 60.f);
#endif
}

void CTimeMgr::render(HDC _dc)
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT 누적

	if (m_dAcc > 1.f)
	{
		// 1 초 동안 누적된 량 = FPS
		m_iFPS = m_iCallCount;

		m_dAcc = 0;
		m_iCallCount = 0;

		// 윈도우 이름 값 받아오기
		wchar_t strBuffer[255] = {};
		LoadString(nullptr, IDC_GAMEENGINE, strBuffer, 255);

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"%s FPS : %d, DT : %lf", strBuffer, m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
