/*********************************************************************
 * \file   PlayerJump.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\Fsm\StateMachine.h"
#include "..\..\GameEntity\Player\player.h"

#include "..\..\GameEntity\EntityBase.h"

class PlayerJump : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerJump* Instance()
	{
		static PlayerJump p;
		return &p;
	}
private:
	PlayerJump() {}
	~PlayerJump() {}
};
