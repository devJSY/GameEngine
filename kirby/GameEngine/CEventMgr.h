#pragma once

#include "CRoot.h"

struct tEvent
{
    EVENT_TYPE  eEven;
    DWORD_PTR   lParm;
    DWORD_PTR   wParm;
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

