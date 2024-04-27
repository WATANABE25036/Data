/*********************************************************************
 * \file   PlayerTripleSecond.h
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 02
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerTripleSecond : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerTripleSecond* Instance()
	{
		static PlayerTripleSecond p;
		return &p;
	}
private:
	PlayerTripleSecond() {}
	~PlayerTripleSecond() {}
	bool _attackTrigger;
	int _counter;
};
