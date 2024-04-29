/*********************************************************************
 * \file   PlayerLongDashAttack.h
 * \brief
 *
 * \author WATANABE
 * \date   2024 \  02 \ 02
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerLongDashAttack : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerLongDashAttack* Instance()
	{
		static PlayerLongDashAttack p;
		return &p;
	}
private:
	PlayerLongDashAttack() {}
	~PlayerLongDashAttack() {}
	bool _attackTrigger;
	int _counter;
};
