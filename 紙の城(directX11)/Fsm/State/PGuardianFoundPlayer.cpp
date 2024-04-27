/*********************************************************************
 * \file   PGuardianFoundPlayer.cpp
 * \brief
 * \author 
 * \date   2024 \ 02 \ 21
 *********************************************************************/
#include "PGuardianFoundPlayer.h"
#include "PGuardianIdle.h"
#include "PGuardianAttack.h"
#include "..\..\GameEntity\Player\player.h"

#include "..\..\GameEntity\Enemy\enemy.h"
#include "..\..\GameEntity\Enemy\kumoboss.h"
#include "..\..\GameEntity\EntityManager.h"
#include <cmath>
#include <random>
static double g_time;
Vec2 LeftPoint;
Vec2 rightPoint;
Vec2 *TargetPoint;
int randomNumber;
void PGuardianFoundPlayer::EnterState(PaperGuardian* entity)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-100, 100);
	randomNumber = distrib(gen);
	entity->offset.x =(float) randomNumber;
	randomNumber = distrib(gen);
	entity->offset.y = (float)randomNumber;

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	entity->SetMove(0);
	entity->_animeBasePattern = 7;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 2;
	g_time = 0;
	LeftPoint = { player->GetPosition().x + 150+ entity->offset.x, player->GetPosition().y - 100+ entity->offset.y };
	rightPoint = { player->GetPosition().x - 150+ entity->offset.x, player->GetPosition().y - 100+ entity->offset.y };

	if (entity->GetPosition().x > player->GetPosition().x)
	{
		TargetPoint = &rightPoint;
	}
	else
	{
		TargetPoint = &LeftPoint;
	}

	
}

void PGuardianFoundPlayer::StayState(PaperGuardian* entity)
{

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	auto guardian = EntityManager::Instance()->GetEntitysWithTag<PaperGuardian>("PaperGuardian");

	LeftPoint = { player->GetPosition().x + 150+ entity->offset.x, player->GetPosition().y - 200+entity->offset.y };
	rightPoint = { player->GetPosition().x - 150+ entity->offset.x, player->GetPosition().y - 200+ entity->offset.y };


	Vec2 vel = *TargetPoint - entity->GetPosition();
	D3DXVec2Normalize(&vel, &vel);
	Vec2 length = *TargetPoint - entity->GetPosition();
	if (D3DXVec2Length(&length) < 10)
	{
		vel = { 0,0 };
		for (auto x : guardian)
		{
			if (x != entity)
			{
				if (abs(entity->offset.x - x->offset.x) < 50)
				{
					if ((entity->offset.x - x->offset.x) < 0)
					{
						entity->offset.x -= 50;
					}
					else
					{
						entity->offset.x += 50;
					}
					break;
				}
			}
		}
	}
	entity->SetPosition(entity->GetPosition() + vel * 8);


	auto enemyArray = EntityManager::Instance()->GetEntitysWithTag<Enemy>("Enemy");
	Enemy* enemy;
	for (auto x : enemyArray)
	{
		if (abs(entity->GetPosition().x - x->GetPosition().x) < 400 && x->GetUse() == true)
		{
			enemy = x;
			break;
		}
		else
		{
			enemy = nullptr;
		}
	}

	if (enemy!=nullptr)
	{
		g_time += 1000.0f / 60.0f / 1000.0f;
		if (g_time > entity->_attackTime)
		{
			entity->GetFsm()->ChangeState(PGuardianAttack::Instance());
		}
	}

	auto paperEnemyArray = EntityManager::Instance()->GetEntitysWithTag<PepperEnemy>("PepperEnemy");
	PepperEnemy* paperEnemy;
	for (auto x : paperEnemyArray)
	{
		if (abs(entity->GetPosition().x - x->GetPosition().x) < 400 && x->GetUse() == true)
		{
			paperEnemy = x;
			break;
		}
		else
		{
			paperEnemy = nullptr;
		}
	}
	if (paperEnemy!=nullptr)
	{
		g_time += 1000.0f / 60.0f / 1000.0f;
		if (g_time > entity->_attackTime)
		{
			entity->GetFsm()->ChangeState(PGuardianAttack::Instance());
		}
	}

	auto kumoBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");
	Vec2 distance = kumoBoss->GetPosition() - entity->GetPosition();
	if (D3DXVec2Length(&distance) < 400)
	{
		g_time += 1000.0f / 60.0f / 1000.0f;
		if (g_time > entity->_attackTime)
		{
			entity->GetFsm()->ChangeState(PGuardianAttack::Instance());
		}
	}

	entity->Attacked();


}

void PGuardianFoundPlayer::ExitState(PaperGuardian* entity)
{


}
