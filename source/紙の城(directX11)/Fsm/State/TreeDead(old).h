/*********************************************************************
 * \file   TreeDead.h
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 07
 *********************************************************************/
#pragma once
#include "..\State.h"
#include "..\StateMachine.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\MapObject\Tree.h"

class TreeDead : public State<Tree>
{
public:
	void EnterState(Tree* entity) override;
	void StayState(Tree* entity) override;
	void ExitState(Tree* entity) override;

	static TreeDead* Instance()
	{
		static TreeDead p;
		return &p;
	}
private:
	TreeDead() {}
	~TreeDead() {}
};

