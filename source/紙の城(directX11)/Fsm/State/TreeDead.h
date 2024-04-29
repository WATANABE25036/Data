/*********************************************************************
 * \file   TreeDead.h
 * \brief
 * \author
 * \date   2024 \ 02 \ 27
 *********************************************************************/
#include "..\State.h"

#include "..\..\GameEntity\MapObject\Tree.h"

class TreeDead :public State<Tree>
{
public:
	static TreeDead* Instance()
	{
		static TreeDead p;
		return &p;
	}
	void EnterState(Tree* entity) override;
	void StayState(Tree* entity) override;
	void ExitState(Tree* entity) override;
private:
	TreeDead() {};
	~TreeDead() {};
};

