/*********************************************************************
 * \file   KumoBossSleep.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossSleep.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "kumoBossGetup.h"
#include <random>

static int g_time;
void KumoBossSleep::EnterState(KumoBoss* entity)
{
	//spritePattern’²®
	entity->_animeBasePattern = 30;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 1;
	entity->_animeLoop = false;
	entity->_sleep = true;
}

void KumoBossSleep::StayState(KumoBoss* entity)
{
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	//idleó‘Ô‚É“ü‚é
	if (abs(player->GetPosition().x-entity->GetPosition().x)<500)
	{
		entity->GetFsm()->ChangeState(KumoBossGetUp::Instance());
	}

	entity->PositionHandling();
}

void KumoBossSleep::ExitState(KumoBoss* entity)
{
	entity->_animeLoop = true;
	entity->_sleep = false;
}
