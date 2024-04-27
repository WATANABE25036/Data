/*********************************************************************
 * \file   PlayerTripleFirst.cpp
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
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"
#include "PlayerJump.h"
#include "PlayerMove.h"

void PlayerTripleFirst::EnterState(Player* entity)
{
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 19;
	entity->_animePattern = 9;
	entity->_animeFrameMax = 18;
	entity->_animeFrameSpan = 4;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 200;

	entity->_animeLoop = false;
	entity->_attackBox._use = false;

	entity->SetReleaseAttackKey(false);
	SetHitSpark(EFFECT::COMBAT, entity->GetPosition().x, entity->GetPosition().y, entity->GetReverse());

	_attackTrigger = false;
	_stiffnessCou = 0;
	PlaySound(entity->_SE_swing, 0);
}



void PlayerTripleFirst::StayState(Player* entity)
{
	//I—¹d’¼
	if (entity->_animePattern >= entity->_animeFrameMax - 1)
	{
		_stiffnessCou++;
		entity->_animePattern = entity->_animeFrameMax - 1;
		entity->SetHSpeed(0.0f);
		entity->_attackBox._use = false;

		//ƒWƒƒƒ“ƒv
		if (entity->GetJumpKey())
		{
			entity->GetFsm()->ChangeState(PlayerJump::Instance());
		}

		//ˆÚ“®
		if (entity->GetMoveLKey() || entity->GetMoveRKey())
		{
			entity->GetFsm()->ChangeState(PlayerMove::Instance());
		}
	}
	//I—¹
	if (_stiffnessCou > 30)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}

	if (entity->_animePattern != entity->_oldAnimePattern && entity->_animePattern == 15)
	{
		Shake(25, 10);
		PlaySound(entity->_SE_attack1, 0);
	}

	//UŒ‚”»’è
	if (entity->_animePattern >= 14 && entity->_animePattern <= 15)
	{
		entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 150, entity->GetPosition().y };
		entity->_attackBox._use = true;
		SetHitSpark(EFFECT::COMBAT2, entity->GetPosition().x + entity->GetDirection() * 150, entity->GetPosition().y, entity->GetReverse());
	}
	else
	{
		entity->_attackBox._use = false;
	}

	if (entity->GetAttackKey() && entity->GetReleaseAttackKey())
	{
		_attackTrigger = true;
	}

	if (entity->_animePattern >= 16 && _attackTrigger)
	{

			entity->_attackBox._use = false;
			entity->GetFsm()->ChangeState(PlayerTripleSecond::Instance());
	}
}

void PlayerTripleFirst::ExitState(Player* entity)
{

	entity->_attackBox._use = false;
}
