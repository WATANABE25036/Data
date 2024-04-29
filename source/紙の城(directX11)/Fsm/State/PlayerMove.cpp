/*********************************************************************
 * \file   PlayerMove.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"
#include "PlayerAttack.h"
#include "..\..\input.h"
#include "PlayerDashAttack.h"


void PlayerMove::EnterState(Player* entity)
{
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 8;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 31;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;
	entity->_animeLoop = true;
	_dash = false;
	_walk = false;
	_counter = 0;
}

void PlayerMove::StayState(Player* entity)
{
	Vec2 oldPos = entity->GetPosition();
	_counter++;

	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	//移動
	entity->SetHSpeed(((entity->GetDirection() * entity->GetWalkSpeed()) + entity->GetKnockBackX()));
	entity->SetVSpeed((entity->GetVSpeed()+entity->GetGravity())+entity->GetKnockBackY());

	entity->PositionHandling();
	entity->Attacked();

	//走り
	if (entity->GetDashKey())
	{
		_dash = true;

		//切り替わり時実行
		if (_walk == _dash)
		{
			_counter = 0;
			_walk = false;
			Shake(15, 15);
		}

		entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 12;
		entity->_animeFrameMax = 25;
		entity->SetWalkSpeed(PLAYER_DASH_SPEED);
		Shake(5, 1);
		if (entity->GetTileData()[4].attrib == MAP_ATTRIB_NATURE)
		{
			SetParticle(EFFECT::LEAF, entity->GetPosition().x, entity->GetPosition().y + 50.0f, 1, 0.1f, 10.0f, true, entity->_animePattern % 2);
		}

		//音
		if (_counter == 22)
		{
			PlaySound(entity->_SE_move1, 0);
		}
		if (_counter >= 44)
		{
			PlaySound(entity->_SE_move2, 0);
			_counter = 0;
		}

		//ダッシュ攻撃
		if (entity->GetAttackKey() && entity->GetReleaseAttackKey())
		{
			entity->GetFsm()->ChangeState(PlayerDashAttack::Instance());
		}
	}
	else
	{
		_walk = true;

		//切り替わり時実行
		if (_walk == _dash)
		{
			_counter = 0;
			_dash = false;
		}

		entity->SetWalkSpeed(PLAYER_SPEED);
		entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 8;
		entity->_animeFrameMax = 31;

		//音
		if (_counter == 31)
		{
			PlaySound(entity->_SE_move1, 0);
		}
		if (_counter > 62)
		{
			PlaySound(entity->_SE_move2, 0);
			_counter = 0;
		}
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
