/*********************************************************************
 * \file   PepperIdle.cpp
 * \brief   
 * \author ¥Þ¡¡¥³¥¦¥Eå¥?
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "PepperIdle.h"
#include "..\..\collision.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "PepperFoundPlayer.h"

void PepperIdel::EnterState(PepperEnemy* entity)
{
	entity->SetMove(1);
	entity->_animeBasePattern = 7;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 2;
	entity->SetWalkSpeed(1.0f);
	entity->SetAttackUse(false);

	if (entity->GetMove() < 0)
	{
		entity->SetReverse(true);
	}
	else
	{
		entity->SetReverse(false);
	}

}

void PepperIdel::StayState(PepperEnemy* entity)
{
	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	//ˆÚ“®•ûŒü‚Æ‘¬“x
	entity->SetHSpeed((entity->GetMove() * entity->GetWalkSpeed()) + entity->GetKnockBackX());

	//d—Í
	//entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());

	entity->PositionHandling();

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	if (abs(entity->GetPosition().x - player->GetPosition().x) < 500 )
	{
		entity->GetFsm()->ChangeState(PepperFoundPlayer::Instance());
	}

	entity->Attacked();
}

void PepperIdel::ExitState(PepperEnemy* entity)
{
}
