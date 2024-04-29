/*********************************************************************
 * \file   PlayerDamaged.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07
 *********************************************************************/
#pragma once

#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerDamaged : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerDamaged* Instance()
	{
		static PlayerDamaged p;
		return &p;
	}
private:
	PlayerDamaged() {}
	~PlayerDamaged() {}
};





