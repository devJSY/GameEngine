#include "global.h"
#include "CUI.h"

#include "CKeyMgr.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}

void CUI::update()
{
	m_vUIPos = GetPos();

	// 부모 위치에 자신의 위치를 더함
	if (GetParent())
	{		
		m_vUIPos += GetParent()->GetUIPos();
	}

	// UI Mouse 체크
	MouseOnCheck();

	update_child();

	Component_update();
}

void CUI::render(HDC _dc)
{
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		m_vUIPos = CCamera::GetInst()->GetRenderPos(m_vUIPos);
	}

	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, int(m_vUIPos.x)
			, int(m_vUIPos.y)
			, int(m_vUIPos.x + vScale.x)
			, int(m_vUIPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(m_vUIPos.x)
			, int(m_vUIPos.y)
			, int(m_vUIPos.x + vScale.x)
			, int(m_vUIPos.y + vScale.y));
	}


	// child ui render
	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();
	
	if (m_bCamAffected) // 카메라의 영향을 받는다면 실제 위치로 설정
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vUIPos.x <= vMousePos.x && vMousePos.x <= m_vUIPos.x + vScale.x
		&& m_vUIPos.y <= vMousePos.y && vMousePos.y <= m_vUIPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}
