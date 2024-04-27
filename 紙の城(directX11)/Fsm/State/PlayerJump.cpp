/*********************************************************************
 * \file   PlayerJump.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "PlayerJump.h"
#include "PlayerIdle.h"
#include "..\..\input.h"
#include "..\State.h"
#include "PlayerJumpAttack.h"
#include "PlayerTripleThird.h"

void PlayerJump::EnterState(Player* entity)
{
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 3;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 11;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;
	entity->_animeLoop = false;
	//エフェクト生成
	if (entity->GetTileData()[4].attrib == MAP_ATTRIB_NATURE)
	{
		SetParticle(EFFECT::LEAF, entity->GetPosition().x, entity->GetPosition().y + 50.0f, 20, 0.1f, 15.0f, true, entity->_animePattern % 2);
	}
	PlaySound(entity->_SE_jump, 0);
}

void PlayerJump::StayState(Player* entity)
{
	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	//落下中の処理
	if (entity->GetVsp() > 0)
	{
		entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 5;
		entity->_animeFrameMax = 5;
	}

	entity->Jump(true);


	if (entity->_animePattern <= 9)
	{
		//下突き
		if (entity->GetAttackKey() && entity->GetDownKey())
		{
			entity->SetGround(false);
			entity->GetFsm()->ChangeState(PlayerJumpAttack::Instance());
		}
		//横攻撃
		else if (entity->GetAttackKey())
		{
			entity->SetGround(false);
			entity->GetFsm()->ChangeState(PlayerTripleThird::Instance());
		}

	}

	entity->SetHSpeed(((entity->GetDirection() * entity->GetWalkSpeed()) + entity->GetKnockBackX()));

	entity->PositionHandling();
	if (entity->GetGround() == true)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}

	if (entity->_animePattern >= entity->_animeFrameMax)
	{
		entity->_animePattern = entity->_animeFrameMax;
	}
}

void PlayerJump::ExitState(Player* entity)
{

}
