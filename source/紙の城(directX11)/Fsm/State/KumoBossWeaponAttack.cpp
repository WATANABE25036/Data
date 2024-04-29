/*********************************************************************
 * \file   KumoBossWeaponAttack.cpp
 * \brief   
 * \author ¥Þ¡¡¥³¥¦¥Eå¥?
 * \date   2024 \ 02 \ 08
 *********************************************************************/


#include "KumoBossWeaponAttack.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "KumoBossIdle.h"

void KumoBossWeaponAttack::EnterState(KumoBoss* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = 190;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 19;
	entity->_attackBox._use = false;

}


void KumoBossWeaponAttack::StayState(KumoBoss* entity)
{
	entity->SetHSpeed(((0 * entity->GetWalkSpeed())));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	Vec2 distance = player->GetPosition() - entity->GetPosition();


	if (entity->_animePattern>=11&& entity->_animePattern<=13)
	{
		if (entity->GetDirection() > 0)
		{
			entity->_attackBox._pos = { entity->GetPosition().x + 350,entity->GetPosition().y + 240 };
			entity->_attackBox._use = true;
		}
		else
		{
			entity->_attackBox._pos = { entity->GetPosition().x - 350,entity->GetPosition().y + 240 };
			entity->_attackBox._use = true;
		}
		Shake(30, 10);
	}
	else
	{
		entity->_attackBox._use = false;
	}

	if (entity->_animePattern >= 18)
	{
		entity->GetFsm()->ChangeState(KumoBossIdle::Instance());
	}

	if (entity->_oldAnimePattern != entity->_animePattern && entity->_animePattern == 11)
	{
		SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetParticle(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 300 + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
	
		SetVolume(entity->_SE_attack4, 0.8f);
		PlaySound(entity->_SE_attack4, 0);
	}

	entity->PositionHandling();
}

void KumoBossWeaponAttack::ExitState(KumoBoss* entity)
{
	entity->_attackDesire -= 80;
}
