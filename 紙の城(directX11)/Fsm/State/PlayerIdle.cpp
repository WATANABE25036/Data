/*********************************************************************
 * \file   PlayerIdle.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "PlayerIdle.h"
#include "..\..\input.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "PlayerAttack.h"
#include "PlayerSpecial.h"

#include "PlayerTripleFirst.h"
#include "PlayerTripleSecond.h"
#include "PlayerTripleThird.h"

void PlayerIdle::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = 0;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 25;
	entity->_animeFrameSpan = 4;
	entity->_attackBox._use = false;
	entity->_UW = 1/ PLAYER_WIDTH_PATTERN;
	entity->_VH = 1/ PLAYER_HEIGHT_PATTERN;
	entity->_animeLoop = true;
}

void PlayerIdle::StayState(Player* entity)
{
	entity->_attackBox._use = false;

	//ƒmƒbƒNƒoƒbƒN
	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	entity->SetHSpeed(((0 * entity->GetWalkSpeed()) + entity->GetKnockBackX()));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());

	//ƒWƒƒƒ“ƒv
	if (entity->GetJumpKey())
	{
		entity->GetFsm()->ChangeState(PlayerJump::Instance());
	}
	//UŒ‚
	if (entity->GetAttackKey() && entity->GetReleaseAttackKey())
	{
		if (entity->GetGround() == TRUE)
		{
			entity->GetFsm()->ChangeState(PlayerTripleFirst::Instance());
		}
	}
	//•KŽE‹Z
	//if (entity->GetSpecialKey())
	//{
	//	entity->GetFsm()->ChangeState(PlayerSpecial::Instance());
	//}
	//ˆÚ“®
	if (entity->GetMoveLKey() || entity->GetMoveRKey())
	{
		entity->GetFsm()->ChangeState(PlayerMove::Instance());
	}

	entity->PositionHandling();
	entity->Attacked();
}

void PlayerIdle::ExitState(Player* entity)
{

}
