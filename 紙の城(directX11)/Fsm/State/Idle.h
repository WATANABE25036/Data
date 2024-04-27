/*********************************************************************
 * \file   Idle.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Enemy\enemy.h"
class Idle:public State<Enemy>
{
	Idle() { ; }
	~Idle()override { ; }
public:
	static Idle* Instance()
	{
		static Idle p;
		return &p;
	}
	void EnterState(Enemy* entity) override;
	void StayState(Enemy* entity) override;
	void ExitState(Enemy* entity) override;
};
