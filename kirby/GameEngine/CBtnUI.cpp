#include "global.h"
#include "CBtnUI.h"

CBtnUI::CBtnUI()
	: CUI(false)
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
	ChangeScene(SCENE_TYPE::Animation_Tool);
}
