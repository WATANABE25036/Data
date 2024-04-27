/*********************************************************************
 * \file   KumoBossAttacked.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossAttacked.h"
#include "KumoBossIdle.h"

void KumoBossAttacked::EnterState(KumoBoss* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = 130;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 9;
	entity->_attackBox._use = false;
	entity->_stamina -= 10;
}

void KumoBossAttacked::StayState(KumoBoss* entity)
{
	entity->SetHSpeed(((0 * entity->GetWalkSpeed())));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));

	


	if (entity->_animePattern >= 7)
	{
		entity->GetFsm()->ChangeState(KumoBossIdle::Instance());
	}
	entity->PositionHandling();
}

void KumoBossAttacked::ExitState(KumoBoss* entity)
{

}
