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
class CAnimation;

class CScene_Animation_Tool :
    public CScene
{
private:
    CTexture*               m_pTex;

    Vec2                    m_vTapPos;
    Vec2                    m_vAwayPos;
    bool                    m_DragTrig;

    Vec2                    vAccPos;
    Vec2                    vCamDist;

    AnimFrmData             CurAinmData;
    vector<AnimFrmData>     frameData;

    
    Vec2                    vPrevMousePos;
    Vec2                    vPrevCamLookAt;
        
public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

    void SaveAnimation(UINT _FrameCount, const wchar_t* _Name, const wchar_t* _FileName, float _fDuration);
    void LoadAnimation(const wchar_t* _Name, const wchar_t* _FileName);
    void LoadTexture();

    CTexture* GetTexture() { return m_pTex; }

public:
    CScene_Animation_Tool();
    ~CScene_Animation_Tool();
};

