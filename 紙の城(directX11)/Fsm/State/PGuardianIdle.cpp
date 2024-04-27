/*********************************************************************
 * \file   PGuardianIdle.cpp
 * \brief
 * \author 
 * \date   2024 \ 02 \ 21
 *********************************************************************/


#include "PGuardianIdle.h"
#include "..\..\collision.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "PGuardianFoundPlayer.h"

void PGuardianIdle::EnterState(PaperGuardian* entity)
{
	entity->SetMove(1);
	entity->_animeBasePattern = 1;
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

void PGuardianIdle::StayState(PaperGuardian* entity)
{
	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	//ˆÚ“®•ûŒü‚Æ‘¬“x
	entity->SetHSpeed((entity->GetMove() * entity->GetWalkSpeed()) + entity->GetKnockBackX());

	//d—Í
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());

	entity->PositionHandling();

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	if (abs(entity->GetPosition().x - player->GetPosition().x) < 500)
	{
		entity->GetFsm()->ChangeState(PGuardianFoundPlayer::Instance());


	}

	entity->Attacked();
}

void PGuardianIdle::ExitState(PaperGuardian* entity)
{
}
