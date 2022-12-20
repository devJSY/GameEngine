#include "global.h"
#include "CDeadState.h"

CDeadState::CDeadState()
	: CState(MON_STATE::DEAD)
{
}

CDeadState::~CDeadState()
{
}

void CDeadState::update()
{
}

void CDeadState::Enter()
{
}

void CDeadState::Exit()
{
}
