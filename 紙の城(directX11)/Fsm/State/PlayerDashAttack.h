
/*********************************************************************
 * \file   PlayerDashAttack.h
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 01
 *********************************************************************/
#pragma once

#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerDashAttack : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerDashAttack* Instance()
	{
		static PlayerDashAttack p;
		return &p;
	}
private:
	PlayerDashAttack() {}
	~PlayerDashAttack() {}
	int _changeCou;
	bool _attackTrigger;
};