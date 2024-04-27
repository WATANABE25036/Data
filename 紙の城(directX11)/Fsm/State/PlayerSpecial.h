/*********************************************************************
 * \file   PlayerSpecial.h
 * \brief  
 * 
 * \author WATANABE
 * \date   2024 \  02 \ 27 
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"
class PlayerSpecial : public State<Player>
{
public:
	void EnterState(Player* entity) override;
	void StayState(Player* entity) override;
	void ExitState(Player* entity) override;

	static PlayerSpecial* Instance()
	{
		static PlayerSpecial p;
		return &p;
	}
private:
	PlayerSpecial() {}
	~PlayerSpecial() {}
	bool _releaseAttackKey;
	int _coolTimeCou;
	int _coolTime;
};
