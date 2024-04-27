/*********************************************************************
 * \file   TreeAlive.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "..\State.h"
//#include "..\..\GameEntity\Enemy\PepperEnemy.h"

#include "..\..\GameEntity\MapObject\Tree.h"

class TreeAlive :public State<Tree>
{
public:
	static TreeAlive* Instance()
	{
		static TreeAlive p;
		return &p;
	}
	void EnterState(Tree* entity) override;
	void StayState(Tree* entity) override;
	void ExitState(Tree* entity) override;
private:
	TreeAlive() {};
	~TreeAlive() {};
};

