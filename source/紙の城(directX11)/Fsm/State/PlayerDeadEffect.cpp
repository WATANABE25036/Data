/*********************************************************************
 * \file   PlayerDeadEffect.cpp
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 14
 *********************************************************************/
#include "PlayerDead.h"
#include "PlayerAttack.h"
#include "PlayerIdle.h"
#include "PlayerDeadEffect.h"
 //#include "..\..\input.h"

#include "..\..\GameEntity\EntityManager.h"
//#include "..\..\GameEntity\Enemy\KumoBoss.h"
//#include "..\..\GameEntity\Enemy\enemy.h"




void PlayerDeadEffect::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 30;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 15;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;



	entity->_animeLoop = false;
	entity->_attackBox._use = false;
}



void PlayerDeadEffect::StayState(Player* entity)
{



	/*if (entity->_animePattern >= 4)
	{
		SetPlayerKnockBack(100, -100.0f);


	}*/




}

void PlayerDeadEffect::ExitState(Player* entity)
{


}