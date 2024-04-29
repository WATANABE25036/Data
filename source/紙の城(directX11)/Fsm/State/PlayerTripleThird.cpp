/*********************************************************************
 * \file   PlayerTripleThird.cpp
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



void PlayerTripleThird::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 25;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 8;
	entity->_animeFrameSpan = 4;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_attackBox._size.x = 380;
	entity->_attackBox._size.y = 320;

	entity->SetReleaseAttackKey(false);
	entity->_animeLoop = false;
	entity->_attackBox._use = false;
	_stiffnessCou = 0;
	_counter = 0;
	//PlaySound(entity->_SE_swing, 0);
}

void PlayerTripleThird::StayState(Player* entity)
{
	_counter++;

	//終了硬直
	if (entity->_animePattern >= entity->_animeFrameMax - 1 && entity->GetGround())
	{
		_stiffnessCou++;
		entity->_animePattern = entity->_animeFrameMax - 1;
	}

	//土煙
	if (_stiffnessCou == 1)
	{
		Shake(100, 15);
		SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 100, 50, 0.5f, 30.0f, true, false, EFFECT::NONE, 155, 120, 100);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 120, false, 0.0f, 155, 155, 155);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 100, entity->GetPosition().y + 150, false, 20.0f, 155, 155, 155);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 300, entity->GetPosition().y + 180, false, 40.0f, 155, 155, 155);
		PlaySound(entity->_SE_attack2, 0);
	}

	//終了
	if (_stiffnessCou > 30)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}
	else if (_stiffnessCou < 10)
	{
		entity->SetMove(entity->GetDirection());//向きをセット
		entity->SetWalkSpeed(10);//移動
	}

	if (_counter == 24)
	{
		SetHitSpark(EFFECT::COMBAT3, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 70, entity->GetReverse());
	}

	//移動
	if (entity->_animePattern == 4)
	{
		entity->SetHSpeed(((entity->GetDirection() * 15.0f)));
		entity->SetVSpeed(-1.0f);
	}

	//音
	if (entity->_animePattern != entity->_oldAnimePattern && entity->_animePattern == 5)
	{
		PlaySound(entity->_SE_swing, 0);
	}

	//当たり判定
	entity->_attackBox._use = false;
	if (entity->_animePattern > 4)
	{
		entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 70,entity->GetPosition().y - 50 };

		if (entity->GetGround())
		{
			entity->SetMove(0);//動作停止
			entity->_attackBox._size.x = 400;
			entity->_attackBox._size.y = 150;
			entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 180,entity->GetPosition().y + 80 };
		}
		entity->_attackBox._use = true;
	}
	if (entity->_animePattern == 2)
	{
		entity->SetVSpeed(-10);//少しジャンプ
	}

	entity->SetKnockBackX(0);
	entity->SetKnockBackY(0);

	entity->PositionHandling();
}

void PlayerTripleThird::ExitState(Player* entity)
{
	entity->_attackBox._use = false;

}
