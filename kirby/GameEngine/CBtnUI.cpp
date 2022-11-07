#include "global.h"
#include "CBtnUI.h"

#include "SelectGDI.h"

CBtnUI::CBtnUI()
	: CUI(false)
	, m_SceneType(-1)
{
}

CBtnUI::~CBtnUI()
{
}


void CBtnUI::start()
{
}

void CBtnUI::render(HDC _dc)
{
	Vec2 vUIPos = GetUIPos();
	Vec2 vUIScale = GetScale();


	if (IsLbtnDown())
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc
			, int(vUIPos.x)
			, int(vUIPos.y)
			, int(vUIPos.x + vUIScale.x)
			, int(vUIPos.y + vUIScale.y));
	}
	else
	{
		if (m_SceneType == (UINT)SCENE_TYPE::Animation_Tool)
		{
			SelectGDI select(_dc, PEN_TYPE::PINK);

			Rectangle(_dc
				, int(vUIPos.x)
				, int(vUIPos.y)
				, int(vUIPos.x + vUIScale.x)
				, int(vUIPos.y + vUIScale.y));
		}
		else if (m_SceneType == (UINT)SCENE_TYPE::Scene_Tool)
		{
			SelectGDI select(_dc, PEN_TYPE::BLUE);

			Rectangle(_dc
				, int(vUIPos.x)
				, int(vUIPos.y)
				, int(vUIPos.x + vUIScale.x)
				, int(vUIPos.y + vUIScale.y));
		}
		else if (m_SceneType == (UINT)SCENE_TYPE::STAGE_01)
		{
			SelectGDI select(_dc, PEN_TYPE::RED);

			Rectangle(_dc
				, int(vUIPos.x)
				, int(vUIPos.y)
				, int(vUIPos.x + vUIScale.x)
				, int(vUIPos.y + vUIScale.y));
		}
	}
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	if (-1 != m_SceneType)
	{
		ChangeScene(SCENE_TYPE(m_SceneType));
	}	
	else
	{
		assert(nullptr); // 설정된 SceneType가 없다면 에러
	}
}
