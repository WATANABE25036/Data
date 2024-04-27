/*********************************************************************
 * \file   KumoBossBackAttacked.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossBackAttacked.h"
#include "KumoBossIdle.h"

void KumoBossBackAttacked::EnterState(KumoBoss* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = 140;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 13;
	entity->_attackBox._use = false;
	entity->_stamina -= 10;

	if (entity->GetDirection() < 0) entity->SetReverse(false);
	else if (entity->GetDirection() > 0) entity->SetReverse(true);
}

void KumoBossBackAttacked::StayState(KumoBoss* entity)
{
	entity->SetHSpeed(((0 * entity->GetWalkSpeed())));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));


	if (entity->_animePattern >= 12)
	{
		entity->GetFsm()->ChangeState(KumoBossIdle::Instance());
	}
	entity->PositionHandling();
}

void KumoBossBackAttacked::ExitState(KumoBoss* entity)
{

}
