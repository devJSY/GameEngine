#pragma once

class CTimeMgr :
    public CRoot
{
    SINGLE(CTimeMgr);

private:
    LARGE_INTEGER m_llCurCountl; // ���� ������ ī��Ʈ 
    LARGE_INTEGER m_llPrevCount; // ���� ������ ī��Ʈ
    LARGE_INTEGER m_llFrequency; // ������ �󵵼�

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

