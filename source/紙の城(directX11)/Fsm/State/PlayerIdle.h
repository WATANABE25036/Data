/*********************************************************************
 * \file   PlayerIdle.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerIdle : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerIdle* Instance()
	{
		static PlayerIdle p;
		return &p;
	}
private:
	PlayerIdle() {}
	~PlayerIdle() {}
};
