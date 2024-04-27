/*********************************************************************
 * \file   KumoBossGetUp.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossGetUp.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "kumoBossIdle.h"
#include <random>

static int g_time;
void KumoBossGetUp::EnterState(KumoBoss* entity)
{
	//spritePattern’²®
	entity->_animeBasePattern = 30;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 34;
	StopSoundAll();
	PlaySound(entity->_BGM_Boss, -1, 0.7f);
}

void KumoBossGetUp::StayState(KumoBoss* entity)
{
	//idleó‘Ô‚É“ü‚é
	if (entity->_animePattern >= 33)
	{
		entity->GetFsm()->ChangeState(KumoBossIdle::Instance());
	}

	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));
	entity->PositionHandling();
}

void KumoBossGetUp::ExitState(KumoBoss* entity)
{
}
