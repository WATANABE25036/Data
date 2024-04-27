/*********************************************************************
 * \file   PlayerSpecial.cpp
 * \brief  
 * 
 * \author WATANABE
 * \date   2024 \  02 \ 27 
 *********************************************************************/
#include "PlayerSpecial.h"
#include "PlayerIdle.h"
#include "..\..\input.h"
#include "..\..\GameEntity\EntityManager.h"
#include "PlayerTripleFirst.h"
#include "..\..\GameEntity\Enemy\KumoBoss.h"
#include "..\..\range_select.h"

void PlayerSpecial::EnterState(Player* entity)
{
	entity->SetHSpeed(0);
	entity->_animeBasePattern = PLAYER_WIDTH_PATTERN * 25;
	entity->_animePattern = 0;
	entity->_animeFrameMax = 8;
	entity->_animeFrameSpan = 4;
	entity->_UW = 1 / PLAYER_WIDTH_PATTERN;
	entity->_VH = 1 / PLAYER_HEIGHT_PATTERN;

	entity->_animeLoop = false;
	entity->_attackBox._use = false;
	entity->_attackBox._size.x = 200;
	entity->_attackBox._size.y = 100;

	_releaseAttackKey = false;
	_coolTimeCou = 0;
	_coolTime = 120;
}

void PlayerSpecial::StayState(Player* entity)
{
	if(entity->GetSpecialKey())
	{
		if (entity->GetDirection() > 0)
		{
			SetRangeSelect(D3DXVECTOR2(entity->GetPosition().x + MAPCHIP_SIZE, entity->GetPosition().y), entity->GetDirection());
		}
		else if (entity->GetDirection() < 0)
		{
			SetRangeSelect(D3DXVECTOR2(entity->GetPosition().x - MAPCHIP_SIZE, entity->GetPosition().y), entity->GetDirection());
		}

		if (entity->_animePattern > 4)
		{
			entity->_animePattern = 4;
		}
	}

	//ƒL[‚ð—£‚µ‚½‚ç
	if(!entity->GetSpecialKey())
	{
		_releaseAttackKey = true;
		DecisionRangeSelect();
	}

	if (_releaseAttackKey)
	{
		_coolTimeCou++;
	}

	if (_coolTimeCou > _coolTime)
	{
		entity->GetFsm()->ChangeState(PlayerIdle::Instance());
	}
}

void PlayerSpecial::ExitState(Player* entity)
{
	entity->_attackBox._use = false;
}
