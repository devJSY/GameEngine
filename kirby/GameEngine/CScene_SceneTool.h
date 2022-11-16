#pragma once
#include "CScene.h"

class CTexture;
class CAnimation;

struct tStageConf
{
    CTexture*               TexBackGround;
    CTexture*               TexForeGround;
    CAnimation*             BackGroundAnim;
    CAnimation*             ForeGroundAnim;
    wstring                 BackGroundPath;
    wstring                 ForeGroundPath;
    Vec2                    SceneOffset;
    //vector<CObject*>        vecObj;
};

class CScene_SceneTool :
    public CScene
{
private:
    // Scene
    tStageConf              m_tStageConf;
    Vec2                    m_vPrevMousePos;

    // Tile
    vector<CObject*>        m_vTile;
    Vec2                    m_vTapPos;
    Vec2                    m_vAwayPos;
    Vec2                    m_vAccPos;
    Vec2                    m_vCamDist;
    bool                    m_DragTrig;

   


public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    void LoadBackGround();
    void LoadForeGround();

public:
    CTexture* GetBackGroundTex() { return m_tStageConf.TexBackGround; }
    CTexture* GetForeGroundTex() { return m_tStageConf.TexForeGround; }
    CAnimation* GetBackGroundAnim() { return m_tStageConf.BackGroundAnim; }
    CAnimation* GetForeGroundAnim() { return m_tStageConf.ForeGroundAnim; }

public:
    void Save(const wstring& _strName);
    void Load(const wstring& _strName);

public:
    void TileDetectCheck(Vec2 _vLT, Vec2 _vRB);


public:
    CScene_SceneTool();
    ~CScene_SceneTool();
};

