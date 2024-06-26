/*********************************************************************
 * \file   PlayerDashAttack.cpp
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 01
 *********************************************************************/
#include "PlayerDashAttack.h"
#include "PlayerAttack.h"
#include "PlayerMove.h"
#include "PlayerIdle.h"
#include "PlayerLongDashAttack.h"
#include "..\..\input.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"

#include "..\..\GameEntity\Enemy\PepperEnemy.h"
#include "..\..\collision.h"



void PlayerDashAttack::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->SetWalkSpeed(PLAYER_DASH_SPEED);
	entity->SetReleaseAttackKey(false);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 17;
	entity->_animeFrameMax = 16;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_animePattern = 0;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_animeLoop = false;

	entity->_attackBox._use = false;
	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 200;
	_changeCou = 0;
	_attackTrigger = false;
	PlaySound(entity->_SE_swing, 0);
}

void PlayerDashAttack::StayState(Player* entity)
{
	//修了
	if (entity->_animePattern >= entity->_animeFrameMax - 1)
	{

	}

	//突進
	if (entity->_animePattern == 12)
	{
		entity->SetWalkSpeed(40);//移動
	}
	if (entity->_animePattern >= 12)
	{
		entity->SetMove(entity->GetDirection());//向きをセット
		entity->SetWalkSpeed(entity->GetWalkSpeed() * 0.7f);//移動
		_changeCou++;
	}

	if (_changeCou == 1)
	{
		SetHitSpark(EFFECT::COMBAT4, entity->GetPosition().x + entity->GetDirection() * 400, entity->GetPosition().y, !entity->GetReverse());
	}

	//硬直
	if (_changeCou > 10)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
		entity->_attackBox._use = false;
	}

	if (entity->_animePattern >= 0 && entity->_animePattern <= 15)
	{
		entity->_attackBox._use = true;
	}
	else
	{
		entity->_attackBox._use = false;
	}

	//音
	if (entity->_animePattern != entity->_oldAnimePattern && entity->_animePattern == 12)
	{
		Shake(15, 15);
		PlaySound(entity->_SE_attack3, 0);
	}

	entity->PositionHandling();

	//入力確認
	if (entity->GetAttackKey() && entity->GetReleaseAttackKey())
	{
		_attackTrigger = true;
	}

	//追加攻撃
	if (entity->_animePattern > 11 && _attackTrigger)
	{
		entity->GetFsm()->ChangeState(PlayerLongDashAttack::Instance());
	}

	entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 250,entity->GetPosition().y + 50};
}

void PlayerDashAttack::ExitState(Player* entity)
{
	entity->_attackBox._use = false;

}
