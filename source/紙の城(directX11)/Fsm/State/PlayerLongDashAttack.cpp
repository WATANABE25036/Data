/*********************************************************************
 * \file   PlayerLongDashAttack.cpp
 * \brief
 *
 * \author WATANABE
 * \date   2024 \  02 \ 02
 *********************************************************************/
#include "PlayerAttack.h"
#include "PlayerIdle.h"
#include "..\..\input.h"
#include "PlayerLongDashAttack.h"
#include "PlayerTripleThird.h"
#include "PlayerJump.h"

void PlayerLongDashAttack::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 27;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 8;
	entity->_animeFrameSpan = 4;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 150;

	entity->_animeLoop = true;
	entity->_attackBox._use = false;

	entity->SetReleaseAttackKey(false);
	_attackTrigger = false;
	_counter = 0;
	PlaySound(entity->_SE_swing, 0);
}

void PlayerLongDashAttack::StayState(Player* entity)
{
	_counter++;
	SetHitSpark(EFFECT::COMBAT4, entity->GetPosition().x + entity->GetDirection() * -130, entity->GetPosition().y, entity->GetReverse());
	SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * -180, entity->GetPosition().y - 30, 1, 0.5f, 10.0f, true, false, EFFECT::HIT_SPARK, 155, 120, 100);
	if (!entity->GetAttackKey())
	{
		entity->SetReleaseAttackKey(true);
	}

	//音
	if (entity->_animePattern != entity->_oldAnimePattern)
	{
		Shake(15, 5);
		PlaySound(entity->_SE_attack2, 0, 0.5f);
	}

	//終了
	if (_counter > 80)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}

	//初動
	if (entity->_animePattern == 1)
	{
		entity->SetWalkSpeed(15.0f);//移動
	}

	//当たり判定
	if (entity->_animePattern >= 0 && entity->_animePattern < 17)
	{
		if (entity->GetDirection() > 0)
		{
			entity->_attackBox._use = true;
		}
		else
		{
			entity->_attackBox._use = true;
		}
	}
	else
	{
		entity->_attackBox._use = false;
	}

	entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 130,entity->GetPosition().y + 50};

	//突進
	entity->SetMove(entity->GetDirection());//向きをセット
	entity->SetWalkSpeed(entity->GetWalkSpeed() + 0.08f);//移動

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

	//ジャンプ
	if (entity->GetJumpKey())
	{
		entity->GetFsm()->ChangeState(PlayerJump::Instance());
	}
}

void PlayerLongDashAttack::ExitState(Player* entity)
{
	entity->_attackBox._use = false;

}
