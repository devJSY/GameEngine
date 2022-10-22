#pragma once
#include "CScene.h"

struct AnimFrmData
{
    Vec2 vLT;
    Vec2 vRB;
    Vec2 vSlice;
    Vec2 vOffset;
    float fDuration;
};

class CTexture;

class CScene_Animation_Tool :
    public CScene
{
private:
    CTexture*               m_CurTex;

    Vec2                    m_vTapPos;
    Vec2                    m_vAwayPos;
    bool                    m_DragTrig;

    Vec2                    vAccPos;

    AnimFrmData             CurAinmData;
    vector<AnimFrmData>     frameData;
        
public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    CScene_Animation_Tool();
    ~CScene_Animation_Tool();
};

