/*********************************************************************
 * \file   PepperFoundPlayer.cpp
 * \brief   
 * \author •ﬁ°°•≥•¶•ÅEÂ•?
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "PepperFoundPlayer.h"
#include "PeppeAttack.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\EntityManager.h"
#include <random>

static double g_time;
static Vec2 LeftPoint;
static Vec2 rightPoint;
static Vec2* TargetPoint;
static int randomNumber;
void PepperFoundPlayer::EnterState(PepperEnemy* entity)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-100, 100);
	randomNumber = distrib(gen);
	entity->offset.x = (float)randomNumber;
	randomNumber = distrib(gen);
	entity->offset.y = (float)randomNumber;

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	entity->SetMove(0);
	entity->_animeBasePattern = 7;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 2;
	g_time = 0;
	LeftPoint = { player->GetPosition().x - 450 + entity->offset.x, player->GetPosition().y - 150 + entity->offset.y };
	rightPoint = { player->GetPosition().x + 450 + entity->offset.x, player->GetPosition().y - 150 + entity->offset.y };

	if (entity->GetPosition().x > player->GetPosition().x)
	{
		TargetPoint = &rightPoint;
	}
	else
	{
		TargetPoint = &LeftPoint;
	}
}

void PepperFoundPlayer::StayState(PepperEnemy* entity)
{

	auto pepper = EntityManager::Instance()->GetEntitysWithTag<PepperEnemy>("PepperEnemy");
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	LeftPoint = { player->GetPosition().x - 450 + entity->offset.x, player->GetPosition().y - 150 + entity->offset.y };
	rightPoint = { player->GetPosition().x + 450 + entity->offset.x, player->GetPosition().y - 150 + entity->offset.y };
	

	Vec2 vel = *TargetPoint - entity->GetPosition();
	D3DXVec2Normalize(&vel, &vel);
	Vec2 length = *TargetPoint - entity->GetPosition();
	if (D3DXVec2Length(&length) < 25)
	{
		vel = { 0,0 };
		entity->SetPosition(*TargetPoint);
		for (auto x : pepper)
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
		{
			g_time += 60.0f / 1000.0f ;
			if (g_time > 3.5)
			{
				entity->GetFsm()->ChangeState(PepperAttack::Instance());
				g_time = 0.0f;
			}
		}
	}
	entity->SetPosition(entity->GetPosition() + vel * 20);


	entity->Attacked();
}

void PepperFoundPlayer::ExitState(PepperEnemy* entity)
{
}
