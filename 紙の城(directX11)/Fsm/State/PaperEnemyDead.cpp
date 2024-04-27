/*********************************************************************
 * \file   PaperEnemyDead.cpp
 * \brief
 *
 * \author 
 * \date   2024 \  03 \ 02
 *********************************************************************/
#include "PaperEnemyDead.h"
#include "..\..\item.h"


void PaperEnemyDead::EnterState(PepperEnemy* entity)
{

}

void PaperEnemyDead::StayState(PepperEnemy* entity)
{
	if (entity->GetHp() <= 0)
	{
		entity->SetUse(false);
		int itemRan = RandomPercent(15);
		switch (itemRan)
		{
		case 1:
			SetItem(entity->GetPosition().x, entity->GetPosition().y, ITEM_TYPE_PAPER2);
			break;

		default:
			break;
		}
	}
}

void PaperEnemyDead::ExitState(PepperEnemy* entity)
{
}
