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
    vector<tEvent>   m_vecEvent; // �̹� ������ �̺�Ʈ ���� vector 

    vector<CObject*> m_vecDead; // Dead Object ���� vector 

public:
    void update();
    void AddEvent(const tEvent& _eve);

private:
    void Excute(const tEvent& _eve);
};

