/*********************************************************************
 * \file   CastleIntact.h
 * \brief
 * \author
 * \date   2024 \ 02 \ 26
 *********************************************************************/
#pragma once

#include "..\State.h"
 //#include "..\..\GameEntity\Enemy\PepperEnemy.h"

#include "..\..\GameEntity\MapObject\NekoCastle.h"

class CastleIntact :public State<Castle>
{
public:
	static CastleIntact* Instance()
	{
		static CastleIntact p;
		return &p;
	}
	void EnterState(Castle* entity) override;
	void StayState(Castle* entity) override;
	void ExitState(Castle* entity) override;
private:
	CastleIntact() {};
	~CastleIntact() {};
};


