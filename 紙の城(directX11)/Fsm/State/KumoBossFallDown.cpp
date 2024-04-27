/*********************************************************************
 * \file   KumoBossFallDown.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBossFallDown.h"
#include "KumoBossGetUp.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "kumoBossIdle.h"
#include <random>

static double g_time;
void KumoBossFallDown::EnterState(KumoBoss* entity)
{
	g_time = 0;
	entity->_animeBasePattern = 100;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 19;

	entity->_UW = 1.0f / BOSS_WIDTH_PATTERN;
	entity->_VH = 1.0f / BOSS_HEIGHT_PATTERN;

}

void KumoBossFallDown::StayState(KumoBoss* entity)
{
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()));
	entity->SetHSpeed(0.0f);

	if (entity->_animePattern == 20)
	{
		entity->_animeLoop = false;
	}
	g_time += ((1000.0f / 60.0f) / 1000.0f);//–ˆframe‚Ì•b”
	if (g_time > 10.0f)//ðŒ10•bŒã‚ÅIdleó‘Ô‚É–ß‚µ‚Ü‚·
	{
		entity->GetFsm()->ChangeState(KumoBossGetUp::Instance());
	}

	if (entity->_oldAnimePattern != entity->_animePattern && entity->_animePattern == 10)
	{
		Shake(150, 15);
		SetParticle(EFFECT::BALL, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetParticle(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 180, entity->GetPosition().y + 300 + BOSS_X * 50, 100, 0.5f, 20.0f, true, false, EFFECT::NONE, 30, 30, 30);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * 100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -100, entity->GetPosition().y + 300 + BOSS_X * 50, false, 0.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -200, entity->GetPosition().y + 300 + BOSS_X * 50, false, 20.0f, 55, 55, 55);
		SetHitSpark(EFFECT::SPLATTER, entity->GetPosition().x + entity->GetDirection() * -300, entity->GetPosition().y + 300 + BOSS_X * 50, false, 40.0f, 55, 55, 55);
	}

	entity->PositionHandling();
}

void KumoBossFallDown::ExitState(KumoBoss* entity)
{
	entity->_stamina = 100;
	entity->_animeLoop = true;
}
