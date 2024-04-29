/*********************************************************************
 * \file   PlayerDash.cpp
 * \brief  
 * 
 * \author WATANABE
 * \date   2024 \  02 \ 29 
 *********************************************************************/
#include "PlayerDash.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerAttack.h"
#include "..\..\input.h"
#include "PlayerDashAttack.h""

void PlayerMove::EnterState(Player* entity)
{
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 8;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 25;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;
}

void PlayerMove::StayState(Player* entity)
{
	Vec2 oldPos = entity->GetPosition();

	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	//移動
	if (entity->GetMoveLKey())
	{
		entity->SetDirection(-1);
	}
	if (entity->GetMoveRKey())
	{
		entity->SetDirection(1);
	}

	entity->SetHSpeed(((entity->GetDirection() * entity->GetWalkSpeed()) + entity->GetKnockBackX()));
	entity->SetVSpeed((entity->GetVSpeed()+entity->GetGravity())+entity->GetKnockBackY());

	entity->PositionHandling();
	entity->Attacked();

	//走り
	if (entity->GetDashKey())
	{
		entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 12;
		entity->_animeFrameMax = 25;
		entity->SetWalkSpeed(PLAYER_DASH_SPEED);

		//ダッシュ攻撃
		if (entity->GetAttackKey())
		{
			//entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 17;
			//entity->_animeFrameMax = 16;
			entity->GetFsm()->ChangeState(PlayerDashAttack::Instance());

			/*if (entity->_animePattern >= 15)
			{
				entity->GetFsm()->ChangeState(PlayerMove::Instance());
			}*/
		}
	}
	else
	{
		entity->SetWalkSpeed(PLAYER_SPEED);
		entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 8;
		entity->_animeFrameMax = 31;
	}

	//ジャンプ
	if (entity->GetJumpKey())
	{
		entity->GetFsm()->ChangeState(PlayerJump::Instance());
	}

	//動いていないときアイドル状態
	if (!entity->GetMoveRKey() && !entity->GetMoveLKey())
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}

}

void PlayerMove::ExitState(Player* entity)
{
}
