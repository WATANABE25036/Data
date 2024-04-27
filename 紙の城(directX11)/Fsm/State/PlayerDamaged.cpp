/*********************************************************************
 * \file   PlayerDamaged.cpp
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 07
 *********************************************************************/
#include "PlayerDamaged.h"
#include "PlayerAttack.h"
#include "PlayerIdle.h"
#include "..\..\input.h"

#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"
#include "..\..\GameEntity\Enemy\enemy.h"




void PlayerDamaged::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 15;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 8;
	entity->_animeFrameSpan = PLAYER_FRAME_SPAN;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;



	entity->_animeLoop = false;
	entity->_attackBox._use = false;
}



void PlayerDamaged::StayState(Player* entity)
{



	if (entity->_animePattern >= 7)
	{
		
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());

	}

	

	
}

void PlayerDamaged::ExitState(Player* entity)
{

	
}
