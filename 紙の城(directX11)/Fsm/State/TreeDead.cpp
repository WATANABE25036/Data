/*********************************************************************
 * \file   TreeDead.cpp
 * \brief
 * \author
 * \date   2024 \ 02 \ 27
 *********************************************************************/
#include "TreeDead.h"
#include "TreeAlive.h"
#include "..\..\collision.h"
#include "..\..\input.h"
#include "..\..\text_create.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\Enemy\enemy.h"
#include "..\..\GameEntity\Enemy\EnemySpawn.h"
#include "..\..\GameEntity\Enemy\PepperEnemy.h"


 //#include "PepperFoundPlayer.h"

void TreeDead::EnterState(Tree* entity)
{
	//entity->SetMove(1);
	entity->_animeBasePattern = TREE_WIDTH_PATTERN;
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

	entity->SetHitBoxUse(true);
	//entity->SetUnbeatable(true);

}

void TreeDead::StayState(Tree* entity)
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

	//entity->Attacked();

	/*if (entity->GetHp() <= 0)
	{
		entity->GetFsm()->ChangeState(TreeDead::Instance());

	}*/

	if (entity->GetSpawnCounter() == 0)
	{

		Spawner::Instance()->SetFor<PepperEnemy>({ entity->GetPosition().x, entity->GetPosition().y }, entity->texPepper, 1.0);

	}
		

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	//if (abs(entity->GetHitBox()._pos.x - player->GetHitBox()._pos.x) < 100)
	if (CollisionBB(player->GetHitBox()._pos.x, player->GetHitBox()._pos.y, entity->GetHitBox()._pos.x, entity->GetHitBox()._pos.y, player->GetHitBox()._size.x, player->GetHitBox()._size.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT))
	{

		bool treeRegenerate = GetKeyboardTrigger(DIK_I);
		
		SetDrawTextCreate("REGENERATE", entity->GetPosition().x, entity->GetPosition().y, 10, 3, 20, 10, 30);
		SetDrawTextCreate("I", entity->GetPosition().x, entity->GetPosition().y, 10, 3);

		if(player->GetItemCount() >= 3)
		{
			if (treeRegenerate)
			{
				player->SetItemCount(player->GetItemCount() - 3);
				entity->SetHp(10);
				entity->GetFsm()->ChangeState(TreeAlive::Instance());
			}
		}

	}


}

void TreeDead::ExitState(Tree* entity)
{
	entity->SetEnemySpawn(false);
}
