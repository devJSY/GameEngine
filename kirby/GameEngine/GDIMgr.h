#pragma once

class GDIMgr :
    public CRoot
{
    SINGLE(GDIMgr);

private:
    HPEN	m_arrPen[(UINT)PEN_TYPE::END];
    HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];

public:
    void CreateBrushPen();
    HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
    HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
};

