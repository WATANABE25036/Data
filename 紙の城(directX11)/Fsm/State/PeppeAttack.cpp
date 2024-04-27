/*********************************************************************
 * \file   PeppeAttack.cpp
 * \brief   
 * \author マ　コウリュウ
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "PeppeAttack.h"
#include "PepperFoundPlayer.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"

Vec2 startPoint;
Vec2 centerPoint;
Vec2 endPoint;
void PepperAttack::EnterState(PepperEnemy* entity)
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	entity->SetMove(0);
	entity->_animeBasePattern = 0;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 7;
	entity->g_time = 0;
	Vec2 length= player->GetPosition() - entity->GetPosition();
	//D3DXVec2Normalize(&length, &length);
	startPoint = entity->GetPosition();
	centerPoint = {player->GetPosition().x+(length.x), player->GetPosition().y + 250};
	endPoint = { centerPoint.x + (centerPoint.x - startPoint.x), startPoint.y };
}

void PepperAttack::StayState(PepperEnemy* entity)
{

	entity->g_time += 60.0f / 1000.0f/10;
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	//P = (1−t)2P1 + 2(1−t)tP2 + t2P3
	Vec2 point = (pow(1 - entity->g_time, 2) * startPoint) + (2 * (1 - entity->g_time) * entity->g_time * centerPoint) + (pow(entity->g_time, 2) * endPoint);
	entity->SetPosition(point);

	if (entity->_animePattern >= 0 && entity->_animePattern <= 5)
	{
		if (entity->GetDirection() > 0)
		{

			entity->SetAttackUse(true);
		}
		else
		{

			entity->SetAttackUse(true);
		}


	}
	else
	{
		entity->SetAttackUse(false);
	}

	if (entity->g_time >= 1.0f)
	{
		entity->g_time = 1.0f;
		entity->GetFsm()->ChangeState(PepperFoundPlayer::Instance());
	}

	entity->Attacked();
}

void PepperAttack::ExitState(PepperEnemy* entity)
{
	entity->SetAttackUse(false);

}
