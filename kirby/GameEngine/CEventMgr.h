#pragma once

struct tEvent
{
    EVENT_TYPE  eEven;
    DWORD_PTR   lParam;
    DWORD_PTR   wParam;
};

class CObject;

class CEventMgr :
    public CRoot
{
    SINGLE(CEventMgr);
private:
    vector<tEvent>   m_vecEvent; // 이번 프레임 이벤트 저장 vector 

    vector<CObject*> m_vecDead; // Dead Object 저장 vector 

public:
    void update();
    void AddEvent(const tEvent& _eve);

private:
    void Excute(const tEvent& _eve);
};

