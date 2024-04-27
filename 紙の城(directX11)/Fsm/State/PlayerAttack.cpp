/*********************************************************************
 * \file   PlayerAttack.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "PlayerAttack.h"
#include "PlayerIdle.h"
#include "..\..\input.h"
#include "..\..\GameEntity\EntityManager.h"
#include "PlayerTripleFirst.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"

void PlayerAttack::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 16;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 6;
	entity->_animeFrameSpan = 4;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_animeLoop = false;
	entity->_attackBox._use = false;
	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 100;

	entity->SetReleaseAttackKey(false);
}

void PlayerAttack::StayState(Player* entity)
{
	entity->SetHSpeed(((2 * entity->GetWalkSpeed())));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));


	//auto kumoBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");
	//Vec2 distance = kumoBoss->GetPosition() - entity->GetPosition();


	if (entity->_animePattern >= 5)
	{
		entity->_attackBox._use = false;
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());

	}


	if (entity->_animePattern >= 0 && entity->_animePattern <= 5)
	{
		if (entity->GetDirection() != 0)
		{
			
			entity->_attackBox._use = true;
		}
	}
	else
	{
		entity->_attackBox._use = false;
	}
	
	entity->_attackBox._pos = { entity->GetPosition().x + entity->GetDirection() * 100,entity->GetPosition().y + 100 };

	//˜AŒ‚
	if (entity->_animePattern < entity->_animeFrameMax && entity->GetReleaseAttackKey())
	{
		if (entity->GetAttackKey())
		{

			entity->GetFsm()->ChangeState(PlayerTripleFirst::Instance());

		}

	}

	if(entity->_animePattern > entity->_animeFrameMax)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}
	
	
}

void PlayerAttack::ExitState(Player* entity)
{
	
	entity->_attackBox._use = false;
}
