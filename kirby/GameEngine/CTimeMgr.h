#pragma once

class CTimeMgr :
    public CRoot
{
    SINGLE(CTimeMgr);

private:
    LARGE_INTEGER m_llCurCountl; // 현재 프레임 카운트 
    LARGE_INTEGER m_llPrevCount; // 이전 프레임 카운트
    LARGE_INTEGER m_llFrequency; // 프레임 빈도수

    double m_dDT;
    double m_dAcc;
    UINT m_iCallCount;
    UINT m_iFPS;

public:
    void init();
    void update();
    void render(HDC _dc);

private:
    virtual void Root() {};

};

