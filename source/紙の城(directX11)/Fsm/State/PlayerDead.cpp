/*********************************************************************
 * \file   PlayerDead.cpp
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 13
 *********************************************************************/
#include "PlayerDead.h"
#include "PlayerDeadEffect.h"
#include "PlayerAttack.h"
#include "PlayerIdle.h"
//#include "..\..\input.h"

#include "..\..\GameEntity\EntityManager.h"
//#include "..\..\GameEntity\Enemy\KumoBoss.h"
//#include "..\..\GameEntity\Enemy\enemy.h"




void PlayerDead::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 28;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 16;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;



	entity->_animeLoop = false;
	entity->_attackBox._use = false;

	StopSoundAll();
	PlaySound(entity->_BGM_GameOver, -1, 0.7f);

}



void PlayerDead::StayState(Player* entity)
{



	if (entity->_animePattern >= 4)
	{
		SetPlayerKnockBack(100, -100.0f);
		entity->GetFsm()->ChangeState(PlayerDeadEffect::Instance());

	}




}

void PlayerDead::ExitState(Player* entity)
{


}