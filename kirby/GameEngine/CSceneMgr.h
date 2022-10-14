#pragma once

#include "CRoot.h"

class CScene;

class CSceneMgr :
    public CRoot
{
    SINGLE(CSceneMgr);

private:
   CScene* m_arrScene[(UINT)SCENE_TYPE::END];   // ��� ��
   CScene* m_pCurScene;                         // ���� ��

public:
    void init();
    void update();
    void render(HDC _dc);


public:
    CScene* GetCurScene() { return m_pCurScene; }

private:
    void ChangeScene(SCENE_TYPE _eNext);


private:
    virtual void Root() {};
};

