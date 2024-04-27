/*********************************************************************
 * \file   TreeAlive.cpp
 * \brief
 * \author 
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "TreeAlive.h"
#include "TreeDead.h"

#include "..\..\collision.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\Player\PaperGuardian.h"

#include "..\..\GameEntity\Enemy\enemy.h"
#include "../../GameEntity/Enemy/EnemySpawn.h"
#include "..\..\GameEntity\Enemy\EnemySpawn.h"


//#include "PepperFoundPlayer.h"

void TreeAlive::EnterState(Tree* entity)
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

void TreeAlive::StayState(Tree* entity)
{
	//if (entity->GetKnockBackX() != 0)
	//{
	//	if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
	//	if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	//}

	////ˆÚ“®•ûŒü‚Æ‘¬“x
	//entity->SetHSpeed((entity->GetMove() * entity->GetWalkSpeed()) + entity->GetKnockBackX());

	////d—Í
	//entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());

	entity->PositionHandling();

	/*auto enemy = EntityManager::Instance()->GetEntityWithTag<Enemy>("Enemy");
	if (abs(entity->GetPosition().x - enemy->GetPosition().x) < 500)
	{
		entity->GetFsm()->ChangeState(PepperFoundPlayer::Instance());
	}*/

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	int length = abs(player->GetPosition().x - entity->GetPosition().x);
	if (entity->GetSpawnCounter() == 0&& length<500)
	{

		Spawner::Instance()->SetFor<PaperGuardian>({ entity->GetPosition().x, entity->GetPosition().y },entity->texPaperGuardian, 1.0);

	}

	entity->Attacked();

	/*if (entity->GetHp() <= 0)
	{
		entity->GetFsm()->ChangeState(TreeDead::Instance());

	}*/

}

void TreeAlive::ExitState(Tree* entity)
{
}
