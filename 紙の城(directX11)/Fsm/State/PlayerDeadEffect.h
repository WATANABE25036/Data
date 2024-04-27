/*********************************************************************
 * \file   PlayerDeadEffect.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  02 \ 14
 *********************************************************************/
#pragma once

#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerDeadEffect : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerDeadEffect* Instance()
	{
		static PlayerDeadEffect p;
		return &p;
	}
private:
	PlayerDeadEffect() {}
	~PlayerDeadEffect() {}
};





