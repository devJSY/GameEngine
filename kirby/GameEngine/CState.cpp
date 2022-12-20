#include "global.h"
#include "CState.h"
#include "CMonster.h"
#include "AI.h"

CState::CState(MON_STATE _eState)
	: m_pAI(nullptr),
	m_eState(_eState)
{
}

CState::~CState()
{
}

CMonster* CState::GetMonster()
{
	return m_pAI->GetOwner();
}
