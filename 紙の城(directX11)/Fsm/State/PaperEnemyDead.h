/*********************************************************************
 * \file   PaperEnemyDead.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  03 \ 02
 *********************************************************************/
#pragma once
#include "..\state.h"
#include "..\..\GameEntity\Enemy\PepperEnemy.h"


class PaperEnemyDead :public State<PepperEnemy>
{
	PaperEnemyDead() {}
	~PaperEnemyDead() { ; }
public:
	static PaperEnemyDead* Instance()
	{
		static PaperEnemyDead p;
		return &p;
	}
	void EnterState(PepperEnemy* entity) override;
	void StayState(PepperEnemy* entity) override;
	void ExitState(PepperEnemy* entity) override;
};
