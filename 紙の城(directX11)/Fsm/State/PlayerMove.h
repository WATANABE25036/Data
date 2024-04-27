/*********************************************************************
 * \file   PlayerMove.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
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
	int _counter;
	bool _dash;
	bool _walk;
};
