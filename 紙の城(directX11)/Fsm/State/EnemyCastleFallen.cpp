/*********************************************************************
 * \file   EnemyCastleFallen.cpp
 * \brief
 * \author
 * \date   2024 \ 03 \ 03
 *********************************************************************/


#include "EnemyCastleFallen.h"
#include "..\..\GameEntity\MapObject\EnemyCastle.h"
#include "..\..\collision.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
 //#include "..\..\GameEntity\Enemy\enemy.h"

  //#include "PepperFoundPlayer.h"

void EnemyCastleFallen::EnterState(EnemyCastle* entity)
{
	//entity->SetMove(1);
	entity->_animeBasePattern = 0;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 1;
	//entity->SetWalkSpeed(1.0f);
	//entity->SetAttackUse(false);

	/*if (entity->GetMove() < 0)
	{
		entity->SetReverse(true);
	}
	else
	{
		entity->SetReverse(false);
	}*/



}

void EnemyCastleFallen::StayState(EnemyCastle* entity)
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

	/*auto enemy = EntityManager::Instance()->GetEntityWithTag<Enemy>("Enemy");
	if (abs(entity->GetPosition().x - enemy->GetPosition().x) < 500)
	{
		entity->GetFsm()->ChangeState(PepperFoundPlayer::Instance());
	}*/

	entity->Attacked();
}

void EnemyCastleFallen::ExitState(EnemyCastle* entity)
{

}
