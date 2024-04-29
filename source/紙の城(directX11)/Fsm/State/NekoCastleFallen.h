/*********************************************************************
 * \file   NekoCastleFallen.h
 * \brief
 * \author
 * \date   2024 \ 03 \ 03
 *********************************************************************/
#pragma once

#include "..\State.h"
 #include "..\..\GameEntity\MapObject\NekoCastle.h"


class NekoCastleFallen :public State<Castle>
{
public:
	static NekoCastleFallen* Instance()
	{
		static NekoCastleFallen p;
		return &p;
	}
	void EnterState(Castle* entity) override;
	void StayState(Castle* entity) override;
	void ExitState(Castle* entity) override;
private:
	NekoCastleFallen() {};
	~NekoCastleFallen() {};
};



