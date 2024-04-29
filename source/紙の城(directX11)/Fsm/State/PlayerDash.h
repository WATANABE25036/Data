/*********************************************************************
 * \file   PlayerDash.h
 * \brief  
 * 
 * \author WATANABE
 * \date   2024 \  02 \ 29 
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"
class PlayerMove : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerMove* Instance()
	{
		static PlayerMove p;
		return &p;
	}
private:
	PlayerMove() {}
	~PlayerMove() {}
};
