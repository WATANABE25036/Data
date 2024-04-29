/*********************************************************************
 * \file   KumoBossAttack.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossAttack.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"
#include "KumoBossIdle.h"

void KumoBossAttack::EnterState(KumoBoss* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = 160;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 20;
	entity->_attackBox._use = false;

	//SetVolume(_SE_attack5, 0.5f);
	//PlaySound(_SE_attack5, 0);

}

void KumoBossAttack::StayState(KumoBoss* entity)
{
	entity->SetHSpeed(((0 * entity->GetWalkSpeed())));
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	Vec2 distance = player->GetPosition() - entity->GetPosition();


	if (entity->_animePattern>=7 && entity->_animePattern<=12)
	{
		if (entity->GetDirection() > 0)
		{
			entity->_attackBox._pos = { entity->GetPosition().x + 250,entity->GetPosition().y + 140 };
			entity->_attackBox._use = true;
		}
		else
		{
			entity->_attackBox._pos = { entity->GetPosition().x - 250,entity->GetPosition().y + 140 };
			entity->_attackBox._use = true;
		}
		Shake(30, 10);
	}
	else
	{
		entity->_attackBox._use = false;
	}

	if (entity->_animePattern >= 19)
	{
		entity->GetFsm()->ChangeState(KumoBossIdle::Instance());
	}

	if (entity->_oldAnimePattern != entity->_animePattern && entity->_animePattern == 9)
	{
		SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetParticle(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 300 + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
	

		SetVolume(entity->_SE_attack5, 0.7f);
		PlaySound(entity->_SE_attack5, 0);
	}

	entity->PositionHandling();
}

void KumoBossAttack::ExitState(KumoBoss* entity)
{
	entity->_attackDesire -= 80;
}
