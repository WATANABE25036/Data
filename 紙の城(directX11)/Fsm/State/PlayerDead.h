
/*********************************************************************
 * \file   PlayerDead.h
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 13
 *********************************************************************/
#pragma once

#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerDead : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerDead* Instance()
	{
		static PlayerDead p;
		return &p;
	}
private:
	PlayerDead() {}
	~PlayerDead() {}
};





