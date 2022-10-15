#pragma once
#include "CRoot.h"

class CObject;

class CScene :
    public CRoot
{
private:
    vector<CObject*>    m_arrObj[(UINT)GROUP_TYPE::END];
    wstring             m_strName;

public:
    void SetName(const wstring& _strName) { m_strName = _strName; }
    const wstring& GetName() { return m_strName; }

    virtual void update();
    virtual void Component_update();
    virtual void render(HDC _dc);

    virtual void Enter() = 0;
    virtual void Exit() = 0;

private:
    void AddObject(CObject* _pObj, GROUP_TYPE _GroupType)
    {
        m_arrObj[(UINT)_GroupType].push_back(_pObj);
    }

    friend class CEventMgr;

public:
    CScene();
    virtual ~CScene();
};

