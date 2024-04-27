/*********************************************************************
 * \file   PlayerTripleFirst.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  02 \ 02
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"
class PlayerAttack : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerAttack* Instance()
	{
		static PlayerAttack p;
		return &p;
	}
private:
	PlayerAttack() {}
	~PlayerAttack() {}
};
