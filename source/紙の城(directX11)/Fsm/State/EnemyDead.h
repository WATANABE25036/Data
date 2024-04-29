/*********************************************************************
 * \file   EnemyDead.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\state.h"
#include "..\..\GameEntity\Enemy\enemy.h"


class EnemyDead:public State<Enemy>
{
	EnemyDead() {}
	~EnemyDead() { ; }
public:
	static EnemyDead* Instance()
	{
		static EnemyDead p;
		return &p;
	}
	void EnterState(Enemy* entity) override;
	void StayState(Enemy* entity) override;
	void ExitState(Enemy* entity) override;
};
