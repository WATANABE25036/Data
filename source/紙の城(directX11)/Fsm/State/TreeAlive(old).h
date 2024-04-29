/*********************************************************************
 * \file   TreeAlive.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\MapObject\Tree.h"

class TreeAlive : public State<Tree>
{
public:
	void EnterState(Tree* entity) override;
	void StayState(Tree* entity) override;
	void ExitState(Tree* entity) override;

	static TreeAlive* Instance()
	{
		static TreeAlive p;
		return &p;
	}
private:
	TreeAlive() {}
	~TreeAlive() {}
};
