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

class PlayerTripleFirst : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerTripleFirst* Instance()
	{
		static PlayerTripleFirst p;
		return &p;
	}
private:
	PlayerTripleFirst() {}
	~PlayerTripleFirst() {}
	bool _attackTrigger;
	int _stiffnessCou;
};
