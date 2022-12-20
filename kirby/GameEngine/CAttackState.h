#pragma once
#include "CState.h"

class CAttackState :
    public CState
{
public:
	virtual void update();
	virtual void Enter();
	virtual void Exit();

public:
	CAttackState();
	~CAttackState();

};

