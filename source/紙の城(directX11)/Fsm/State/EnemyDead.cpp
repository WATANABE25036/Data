/*********************************************************************
 * \file   EnemyDead.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "EnemyDead.h"
#include "..\..\item.h"
#include "../../particle.h"

void EnemyDead::EnterState(Enemy* entity)
{
	if (entity->GetHp() <= 0)
	{
		entity->SetUse(false);
		PlaySound(entity->_SE_enemyDown, 0);
		int itemRan = RandomPercent(5);
		switch (itemRan)
		{
		case 1:
			//SetItem(entity->GetPosition().x, entity->GetPosition().y, ITEM_TYPE_PAPER);
			SetItem(entity->GetPosition().x, entity->GetPosition().y, ITEM_TYPE_PAPER2);
			break;

		//case 2:
		//	SetItem(entity->GetPosition().x, entity->GetPosition().y, ITEM_TYPE_PAPER2);
		//	break;

		//case 3:
		//	SetItem(entity->GetPosition().x, entity->GetPosition().y, ITEM_TYPE_PAPER3);
		//	break;
		default:
			break;
		}
		SetParticle(EFFECT::BALL, entity->GetPosition(), 30, 0.5f, 15.0f, false, false, EFFECT::HIT_SPARK, 30.0f, 30.0f, 30.0f);
	}
}

void EnemyDead::StayState(Enemy* entity)
{

}

void EnemyDead::ExitState(Enemy* entity)
{

}
