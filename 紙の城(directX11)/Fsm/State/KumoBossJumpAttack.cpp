/*********************************************************************
 * \file   KumoBossJumpAttack.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossJumpAttack.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "KumoBossIdle.h"

float weight;
static double g_time;
void KumoBossJumpAttack::EnterState(KumoBoss* entity)
{
	g_time = 0.0f;
	entity->_animeBasePattern = 70;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 29;
	entity->_canJumpAtk = false;
	entity->_jumpAtkCD = 20.0f;
}

void KumoBossJumpAttack::StayState(KumoBoss* entity)
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	g_time += (double)((1000.0f / 60.0f)/1000.0f);
	if (g_time < 3.0f)
	{
		if (entity->_animePattern >= 8 && entity->GetPosition().y > -330.0f)
		{
			entity->SetPositionY(entity->GetPosition().y - 15);
			entity->SetGround(false);
		}

		if (entity->_animePattern == 14)
		{
			entity->_animeLoop = false;
		}
	}

	if (g_time>3.0f&&g_time<3.2f)
	{
		entity->SetPositionX(player->GetPosition().x);
	}

	if (g_time > 3.5f && g_time < 3.55f)
	{
		entity->_animeLoop = true;
	}

	if (entity->_animePattern >= 13 && entity->_animePattern <= 18)
	{
		

		if (entity->GetDirection() > 0)
		{
			entity->_attackBox._pos = { entity->GetPosition().x + 50, entity->GetPosition().y + 140 };
			entity->_attackBox._use = true;
		}
		else
		{
			entity->_attackBox._pos = { entity->GetPosition().x - 50, entity->GetPosition().y + 140 };
			entity->_attackBox._use = true;
		}


	}
	else
	{
		entity->_attackBox._use = false;
	}

	if (entity->_oldAnimePattern != entity->_animePattern && entity->_animePattern == 6)
	{
		Shake(180, 20);
		SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetParticle(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 300 + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
	}

	if (entity->_oldAnimePattern != entity->_animePattern && entity->_animePattern == 21)
	{
		Shake(256, 15);
		SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetParticle(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 300 + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
	
		SetVolume(entity->_SE_landing, 0.7f);
		PlaySound(entity->_SE_landing, 0);

		SetVolume(entity->_SE_attack4, 0.8f);
		PlaySound(entity->_SE_attack4, 0);
	}

	if (g_time > 3.55f)
	{
		entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));
		entity->PositionHandling();
		if (entity->_animePattern == 18)
		{
			entity->_animeLoop = false;
		}
	

		if (entity->GetGround()==true)
		{
			entity->_animeLoop = true;
			
		}

		if (g_time < 4.0f)
		{
			
			entity->_animePattern = 19;
		}

	}

	
	

	if (entity->_animePattern>=28)
	{
		
		entity->GetFsm()->ChangeState(KumoBossIdle::Instance());
	}
}

void KumoBossJumpAttack::ExitState(KumoBoss* entity)
{
	entity->_attackDesire -= 60;
}
