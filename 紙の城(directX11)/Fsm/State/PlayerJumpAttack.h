/*********************************************************************
 * \file   PlayerJumpAttack.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  02 \ 14
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerJumpAttack : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerJumpAttack* Instance()
	{
		static PlayerJumpAttack p;
		return &p;
	}
private:
	PlayerJumpAttack() {}
	~PlayerJumpAttack() {}
	int _changeCou;
};
