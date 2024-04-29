/*********************************************************************
 * \file   TreeDead.cpp
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 07
 *********************************************************************/
#include "..\..\GameEntity\MapObject\Tree.h"
#include "TreeDead.h"
 //#include "..\..\input.h"
 //#include "PlayerMove.h"
 //#include "PlayerJump.h"
 //#include "PlayerAttack.h"


void TreeDead::EnterState(Tree* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = 0;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 1;
	//entity->_attackBox._use = false;
	entity->_UW = 1 / TREE_WIDTH_PATTERN;
	entity->_VH = 1 / TREE_HEIGHT_PATTERN;
}

void TreeDead::StayState(Tree* entity)
{

	/*if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	entity->SetHSpeed(((0 * entity->GetWalkSpeed()) + entity->GetKnockBackX()));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());

	if (GetKeyboardPress(DIK_SPACE))
	{
		entity->GetFsm()->ChangeState(PlayerJump::Instance());
	}

	if (GetKeyboardTrigger(DIK_J))
	{
		entity->GetFsm()->ChangeState(PlayerAttack::Instance());
	}

	if (GetKeyboardPress(DIK_A) || GetKeyboardPress(DIK_D))
	{
		entity->GetFsm()->ChangeState(PlayerMove::Instance());
	}*/

	//entity->PositionHandling();
	entity->Attacked();

}

void TreeDead::ExitState(Tree* entity)
{

}
