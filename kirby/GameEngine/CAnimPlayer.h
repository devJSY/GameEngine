#pragma once
#include "CObject.h"

class CAnimPlayer :
    public CObject

{
public:
    virtual void start();   

private:
    void SetAnimation(const wstring& _strRelativePath, const wstring& _strName, bool _bRepeat);

public:
    CLONE(CAnimPlayer);

private:
    CAnimPlayer();
    virtual ~CAnimPlayer();

    friend class CScene_AnimTool;
};

