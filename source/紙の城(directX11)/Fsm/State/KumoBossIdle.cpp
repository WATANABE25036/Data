/*********************************************************************
 * \file   KumoBossIdle.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossIdle.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "kumoBossAttack.h"
#include "KumoBossAttacked.h"
#include "kumoBossJumpAttack.h"
#include "KumoBossBackAttacked.h"
#include "KumoBossFallDown.h"
#include "KumoBossWeaponAttack.h"
#include <random>

static int g_time;
static bool g_find;
void KumoBossIdle::EnterState(KumoBoss* entity)
{
	g_time = 0;
	entity->_animeBasePattern = 0;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 21;
	entity->_attackBox._use = false;
	g_find = true;
	entity->SetWalkSpeed(2.0f);
}

void KumoBossIdle::StayState(KumoBoss* entity)
{
	g_time++;
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	Vec2 distance = player->GetPosition() - entity->GetPosition();
	if (entity->_jumpAtkCD > 0)
	{
		entity->_jumpAtkCD-=1000.0f/60.0f/1000.0f;
	}
	else
	{
		entity->_jumpAtkCD = 0;
		entity->_canJumpAtk = true;
	}

	if (g_time > 100)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(30, 50);
		int randomNumber = distrib(gen);

		if (abs(player->GetPosition().x > entity->GetPosition().x) < 3500)
		{
			randomNumber *= 1.5;
		}
		entity->_attackDesire += randomNumber;
		g_time = 0;
	}

	if (abs(player->GetPosition().y - entity->GetPosition().y) < 2500)
	{
		g_find =true;
	}
	else
	{
		g_find = false;
	}

	
	if (player->GetPosition().x > entity->GetPosition().x&& g_find)
	{
		entity->SetDirection(1);
		entity->SetMove(1);
	}
	else if((player->GetPosition().x < entity->GetPosition().x && g_find))
	{
		entity->SetDirection(-1);
		entity->SetMove(-1);
	}
	
	if (abs(player->GetPosition().x - entity->GetPosition().x) < 250)
	{
		entity->SetMove(0);
	}

	entity->SetHSpeed(((entity->GetMove() * entity->GetWalkSpeed())));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));

	if (entity->_attackDesire > entity->_attackDesireMax)
	{
		entity->SetWalkSpeed(5.0f);
		std::random_device atkrd;
		std::mt19937 r(atkrd());
		std::uniform_int_distribution<> atk(0, 10);
		int randomNumber = atk(r);
		if (D3DXVec2Length(&distance) < 800)
		{
			if (randomNumber < 4)
			{
				entity->GetFsm()->ChangeState(KumoBossAttack::Instance());
			}
			if(randomNumber >=4&& randomNumber < 8)
			{
				entity->GetFsm()->ChangeState(KumoBossWeaponAttack::Instance());
			}

			if (randomNumber >= 8&& entity->_canJumpAtk)
			{
				entity->GetFsm()->ChangeState(KumoBossJumpAttack::Instance());
			}
		}
	
		if (D3DXVec2Length(&distance) >= 800&& entity->_canJumpAtk)
		{
			entity->GetFsm()->ChangeState(KumoBossJumpAttack::Instance());
		}
	}
	else if (entity->GetHp() < entity->GetOldHp())
	{
		if (entity->GetDirection() * (player->GetPosition().x - entity->GetPosition().x) > 0)
		{
			entity->GetFsm()->ChangeState(KumoBossAttacked::Instance());
		}
		else
		{
			entity->GetFsm()->ChangeState(KumoBossBackAttacked::Instance());
		}
	}

	if (entity->_stamina <= entity->_staminaMin)
	{
		entity->GetFsm()->ChangeState(KumoBossFallDown::Instance());
	}
	
	entity->PositionHandling();
}

void KumoBossIdle::ExitState(KumoBoss* entity)
{
}