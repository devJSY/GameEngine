#include "global.h"
#include "CBtnUI.h"

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
