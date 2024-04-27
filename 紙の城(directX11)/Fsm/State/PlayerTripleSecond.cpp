/*********************************************************************
 * \file   PlayerTripleSecond.cpp
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 02
 *********************************************************************/
#include "PlayerAttack.h"
#include "PlayerIdle.h"
#include "..\..\input.h"
#include "PlayerTripleFirst.h"
#include "PlayerTripleSecond.h"
#include "PlayerTripleThird.h"

#include "..\..\GameEntity\Enemy\KumoBoss.h"
#include "..\..\GameEntity\EntityManager.h"


void PlayerTripleSecond::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 26;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 6;
	entity->_animeFrameSpan = 4;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 150;

	entity->_animeLoop = false;
	entity->_attackBox._use = false;

	entity->SetReleaseAttackKey(false);
	_attackTrigger = false;
	_counter = 0;
	SetHitSpark(EFFECT::COMBAT4, entity->GetPosition().x + entity->GetDirection() * 130, entity->GetPosition().y, !entity->GetReverse());
	PlaySound(entity->_SE_swing, 0);
}

void PlayerTripleSecond::StayState(Player* entity)
{
	_counter++;

	if (!entity->GetAttackKey())
	{
		entity->SetReleaseAttackKey(true);
	}

	//終了
	if (entity->_animePattern >= entity->_animeFrameMax - 1 && _counter > 40)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}

	//初動
	if (entity->_animePattern == 1)
	{

	}

	//当たり判定
	if (entity->_animePattern >= 0 && entity->_animePattern < 17)
	{
		entity->_attackBox._use = true;
	}
	else
	{
		entity->_attackBox._use = false;
	}

	entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 130,entity->GetPosition().y + 50};

	//突進
	if (entity->_animePattern == 3)
	{
		entity->SetMove(entity->GetDirection());//向きをセット
		entity->SetWalkSpeed(40);//移動
	}
	else if(entity->_animePattern == 4)
	{
		entity->SetWalkSpeed(0);//移動
	}

	//音
	if (entity->_animePattern != entity->_oldAnimePattern && entity->_animePattern == 4)
	{
		Shake(35, 10);
		PlaySound(entity->_SE_attack4, 0, 0.8f);
	}

	entity->PositionHandling();

	//入力確認
	if (entity->GetAttackKey() && entity->GetReleaseAttackKey())
	{
		_attackTrigger = true;
	}

	//追加攻撃
	if (entity->_animePattern > 3 && _attackTrigger)
	{
		entity->GetFsm()->ChangeState(PlayerTripleThird::Instance());
	}
}

void PlayerTripleSecond::ExitState(Player* entity)
{
	entity->_attackBox._use = false;

}
