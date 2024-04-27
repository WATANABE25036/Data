/*********************************************************************
 * \file   PlayerJumpAttack.cpp
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 14
 *********************************************************************/
#include "PlayerAttack.h"
#include "PlayerJumpAttack.h"
#include "PlayerIdle.h"
#include "..\..\input.h"

#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"




void PlayerJumpAttack::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 23;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 16;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 100;

	entity->_animeLoop = false;
	entity->_attackBox._use = false;

	_changeCou = 0;
	PlaySound(entity->_SE_swing, 0);
}



void PlayerJumpAttack::StayState(Player* entity)
{
	entity->SetVSpeed(20);

	entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection(),entity->GetPosition().y + 200 };

	if (entity->_animePattern >= 0 && entity->_animePattern <= 5)
	{
		entity->_attackBox._use = true;
	}
	else
	{
		entity->_attackBox._use = false;
	}

	//C—¹
	if (entity->GetGround() == TRUE)
	{
		entity->SetMove(0);//“®ì’â~
		if (_changeCou < 3)
		{
			entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection(),entity->GetPosition().y + 50};
			entity->_attackBox._size.x = 500;
			entity->_attackBox._size.y = 200;
			entity->_attackBox._use = true;

			Shake(100, 15);
			SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection(), entity->GetPosition().y + 100, 30, 0.5f, 25.0f, true, false, EFFECT::NONE, 155, 120, 100);
			SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 0, entity->GetPosition().y + 180, false, 0.0f, 155, 155, 155);
			SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -80, entity->GetPosition().y + 150, false, 20.0f, 155, 155, 155);
			SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 80, entity->GetPosition().y + 150, false, 40.0f, 155, 155, 155);
			PlaySound(entity->_SE_attack5, 0, 0.4f);
		}
		_changeCou++;
	}

	if (_changeCou > 30)entity->GetFsm()->ChangeState(PlayerIdle::Instance());

	entity->PositionHandling();
}

void PlayerJumpAttack::ExitState(Player* entity)
{

	entity->_attackBox._use = false;
}
