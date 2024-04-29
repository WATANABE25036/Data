/*********************************************************************
 * \file   PlayerTripleThird.h
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 02
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"

class PlayerTripleThird : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerTripleThird* Instance()
	{
		static PlayerTripleThird p;
		return &p;
	}
private:
	PlayerTripleThird() {}
	~PlayerTripleThird() {}
	int _stiffnessCou;
	int _counter;
};
