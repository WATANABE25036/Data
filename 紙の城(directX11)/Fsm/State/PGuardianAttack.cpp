/*********************************************************************
 * \file   PGuardianAttack.cpp
 * \brief
 * \author 
 * \date   2024 \ 02 \ 25
 *********************************************************************/
#include "PGuardianAttack.h"
#include "PGuardianFoundPlayer.h"
#include "PGuardianIdle.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\Enemy\enemy.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"

Vec2 pstartPoint;
Vec2 pcenterPoint;
Vec2 pendPoint;

Vec2 p2startPoint;
Vec2 p2centerPoint;
Vec2 p2endPoint;

Vec2 p3startPoint;
Vec2 p3centerPoint;
Vec2 p3endPoint;



static float g_time;
Enemy* enemy;
PepperEnemy* paperEnemy;
void PGuardianAttack::EnterState(PaperGuardian* entity)
{
	//auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	auto enemyArray = EntityManager::Instance()->GetEntitysWithTag<Enemy>("Enemy");
	auto paperEnemyArray = EntityManager::Instance()->GetEntitysWithTag<PepperEnemy>("PepperEnemy");
	auto kumoBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");

	for (auto x : enemyArray)
	{
		if (abs(entity->GetPosition().x - x->GetPosition().x) < 600&&x->GetUse()==true)
		{
			enemy = x;
			break;
		}
	}

	for (auto x : paperEnemyArray)
	{
		if (abs(entity->GetPosition().x - x->GetPosition().x) < 600 && x->GetUse() == true)
		{
			paperEnemy = x;
			break;
		}
	}

	entity->SetMove(0);
	entity->_animeBasePattern = 0;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 7;
	g_time = 0;
	if (enemy != nullptr)
	{
		pstartPoint = entity->GetPosition();
		pcenterPoint = { enemy->GetPosition().x, enemy->GetPosition().y + 300 };
		pendPoint = { pcenterPoint.x + (pcenterPoint.x - pstartPoint.x), pstartPoint.y };
	}


	if (paperEnemy != nullptr)
	{
		p2startPoint = entity->GetPosition();
		p2centerPoint = { paperEnemy->GetPosition().x, paperEnemy->GetPosition().y };
		p2endPoint = { p2centerPoint.x + (p2centerPoint.x - p2startPoint.x), p2startPoint.y };

	}
	
	p3startPoint = entity->GetPosition();
	p3centerPoint = { kumoBoss->GetPosition().x, kumoBoss->GetPosition().y };
	p3endPoint = { p3centerPoint.x + (p3centerPoint.x - p3startPoint.x), p3startPoint.y };

}

void PGuardianAttack::StayState(PaperGuardian* entity)
{


	g_time += 60.0f / 1000.0f / 10;
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	auto enemyArray = EntityManager::Instance()->GetEntitysWithTag<Enemy>("Enemy");
	auto paperEnemyArray = EntityManager::Instance()->GetEntitysWithTag<PepperEnemy>("PepperEnemy");
	auto kumoBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");
	for (auto x : enemyArray)
	{
		if (abs(entity->GetPosition().x - x->GetPosition().x) < 600 && x->GetUse() == true)
		{
			enemy = x;
			break;
		}
		else
		{
			enemy = nullptr;
		}
	}

	for (auto x : paperEnemyArray)
	{
		if (abs(entity->GetPosition().x - x->GetPosition().x) < 600 && x->GetUse() == true)
		{
			paperEnemy = x;
			break;
		}
		else
		{
			paperEnemy = nullptr;
		}
	}

	//P = (1?t)2P1 + 2(1?t)tP2 + t2P3
	Vec2 point = (pow(1 - g_time, 2) * pstartPoint) + (2 * (1 - g_time) * g_time * pcenterPoint) + (pow(g_time, 2) * pendPoint);
	Vec2 point2 = (pow(1 - g_time, 2) * p2startPoint) + (2 * (1 - g_time) * g_time * p2centerPoint) + (pow(g_time, 2) * p2endPoint);
	Vec2 point3 = (pow(1 - g_time, 2) * p3startPoint) + (2 * (1 - g_time) * g_time * p3centerPoint) + (pow(g_time, 2) * p3endPoint);


	if (enemy!=nullptr)
	{
		entity->SetPosition(point);
	}
	else if (paperEnemy!=nullptr)
	{
		entity->SetPosition(point2);
	}
	else if (abs(entity->GetPosition().x - kumoBoss->GetPosition().x) < 300)
	{
		entity->SetPosition(point3);
	}
	else
	{
		point = player->GetPosition();
		point2 = player->GetPosition();
		entity->SetPosition(point);
	}

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

	if (g_time >= 1.0f)
	{
		g_time = 1.0f;

		if (enemy==nullptr || paperEnemy==nullptr || abs(entity->GetPosition().x - kumoBoss->GetPosition().x) > 600 )
		{
			entity->GetFsm()->ChangeState(PGuardianFoundPlayer::Instance());
		}
		else if (abs(entity->GetPosition().x - player->GetPosition().x) < 500)
		{
			entity->GetFsm()->ChangeState(PGuardianFoundPlayer::Instance());
		}
		else if (abs(entity->GetPosition().x - player->GetPosition().x) > 500)
		{
			entity->GetFsm()->ChangeState(PGuardianIdle::Instance());
		}


	}

	entity->Attacked();
}

void PGuardianAttack::ExitState(PaperGuardian* entity)
{
	entity->SetAttackUse(false);

}
