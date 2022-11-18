#include "global.h"
#include "GDIMgr.h"

GDIMgr::GDIMgr()
	: m_arrPen{}
	, m_arrBrush{}
{}

GDIMgr::~GDIMgr()
{
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}

void GDIMgr::CreateBrushPen()
{
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::WHITE] = (HBRUSH)GetStockObject(WHITE_BRUSH);

	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 241, 64));
	m_arrPen[(UINT)PEN_TYPE::PINK] = CreatePen(PS_SOLID, 1, RGB(232, 115, 215));
	m_arrPen[(UINT)PEN_TYPE::PURPLE] = CreatePen(PS_SOLID, 1, RGB(160, 27, 140));
	m_arrPen[(UINT)PEN_TYPE::BLACK] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}
