/*********************************************************************
 * \file   FoundPlayer.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "FoundPlayer.h"
#include "..\..\Fsm\StateMachine.h"
#include "..\..\tile.h"
#include "..\..\collision.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\Fsm\State\Idle.h"

float g_StateTimes;
bool g_shotState;
float oldmove;

void FoundPlayer::EnterState(Enemy* Entity)
{
	Entity->g_shotTime = 0;
	g_shotState = false;
	g_StateTimes = 0;
	oldmove = 0;
	Entity->_animeFrameMax = 4;
	Entity->_animeBasePattern = 12;
	Entity->_animeWidthPattern = 4;
	Entity->SetWalkSpeed(6.0f);
}

void FoundPlayer::StayState(Enemy* entity)
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
#pragma region Move
	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}



	if ((entity->GetPosition().x - player->GetPosition().x) > 0)
	{
		entity->SetMove(-1);
		entity->SetReverse(true);
	}
	else
	{
		entity->SetMove(1);
		entity->SetReverse(false);
	}

	if (abs(player->GetPosition().x - entity->GetPosition().x) < 55)
	{
		entity->SetMove(0);
	}

	if (g_shotState == true)
	{
		g_StateTimes++;
		entity->SetMove(0);
		if (g_StateTimes > 50)
		{
			g_shotState = false;
			entity->_animeFrameMax = 4;
			entity->SetMove(oldmove);
			g_StateTimes = 0;
		}
	}

	//移動方向と速度
	entity->SetHSpeed((entity->GetMove() * entity->GetWalkSpeed()) + entity->GetKnockBackX() * 0.8);

	//重力
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());


	//ジャンプ
	entity->SetCanJump(entity->GetCanJump()-1);
	if (((entity->GetCanJump() > 0) && entity->GetJump()) || entity->GetGravity() == 0)
	{
		entity->SetVSpeed(entity->GetJumpPower());
		entity->SetCanJump (0);
	}

	//壁の衝突判定
	//entity->SetTileData(GetMapInfo(entity->GetPosition()));

	auto tile = GetMapInfo(entity->GetPosition(), { ENEMY_HITBOX_WIDTH ,ENEMY_HITBOX_HEIGHT });
	for (int j = 0; j < 9; j++)
	{
		if (tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(entity->GetPosition().x + entity->GetHSpeed(), entity->GetPosition().y, tile[j].pos.x, tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(entity->GetPosition().x + Sign(entity->GetHSpeed()), entity->GetPosition().y, tile[j].pos.x, tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					entity->SetPositionX(entity->GetPosition().x + Sign(entity->GetHSpeed()));
				}
				entity->SetHSpeed(0);
			}

			//縦に壁がある場合
			if (CollisionRot(entity->GetPosition().x, entity->GetPosition().y + entity->GetVSpeed(), tile[j].pos.x, tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(entity->GetPosition().x, entity->GetPosition().y + Sign(entity->GetVSpeed()), tile[j].pos.x, tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					entity->SetPositionY(entity->GetPosition().y + Sign(entity->GetVSpeed()));
				}
				entity->SetVSpeed(0);
			}
		}

	}



	
	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		if ((tile[j].attrib == MAP_ATTRIB_STOP) && (j==4 || j==5 || j == 6 || j == 7 || j == 8))
		{
			//地面に触れているかの処理
			if (CollisionRot(entity->GetHitBox()._pos.x, entity->GetHitBox()._pos.y + 1, tile[j].pos.x, tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				entity->SetGround(true);
				//entity->SetVSpeed(-2.5);
				if (entity->GetOldGround() != entity->GetGround())
				{
					//sound

				}
				break;
			}
		}
		else
		{
			entity->SetGround(false);
		}
	}
#pragma endregion

	entity->g_shotTime++;
	if (abs(entity->GetPosition().x - player->GetPosition().x) <700 && g_shotState == false)
	{
 		if (entity->g_shotTime > 200)
		{
			if (entity->GetReverse() == false)
			{
				entity->Attack({ entity->GetPosition().x + 350, entity->GetPosition().y });
			}
			else
			{
				entity->Attack({ entity->GetPosition().x - 350, entity->GetPosition().y });
			}

			g_shotState = true;
			entity->_animeFrameMax = 1;
			oldmove = entity->GetMove();
			entity->g_shotTime = 0;
		}
	}



	//横移動
	entity->SetPositionX(entity->GetPosition().x + entity->GetHSpeed());

	// ステージループ処理
	if (entity->GetPosition().x > STAGE_SIZE)
	{
		entity->SetPositionX(entity->GetPosition().x - STAGE_SIZE);
	}
	else if (entity->GetPosition().x < 0)
	{
		entity->SetPositionX(entity->GetPosition().x + STAGE_SIZE);
	}
	//縦移動
	entity->SetPositionY(entity->GetPosition().y + entity->GetVSpeed());

	if (entity->GetVSpeed() != 0)entity->SetVSpeed(entity->GetVSpeed() - entity->GetKnockBackY());
	entity->SetKnockBackY(entity->GetKnockBackY() * 0.5f);
	if (entity->GetKnockBackY() < 0.9f)entity->SetKnockBackY(0);
	entity->SetTileData(GetMapInfo(entity->GetPosition()));



	if (entity->GetGround())
	{
		entity->_jumpSp = -22.0f;
		entity->SetCanJump(true);
		entity->SetVSpeed(-2.5);
		entity->SetKnockBackX(0);
	}

	entity->Attacked();

	//if (abs(entity->GetPosition().x - player->GetPosition().x) >= 650 || (entity->GetTileData()[6].attrib == MAP_ATTRIB_NONE || entity->GetTileData()[8].attrib == MAP_ATTRIB_NONE))
	if (abs(entity->GetPosition().x - player->GetPosition().x) >= 650 || (tile[6].attrib == MAP_ATTRIB_NONE || tile[8].attrib == MAP_ATTRIB_NONE))
	{
		entity->SetReverse(true);
		entity->GetFsm()->ChangeState(Idle::Instance());
	}
}

void FoundPlayer::ExitState(Enemy* Entity)
{
	if (Entity->GetMove() < 0)
	{
		Entity->SetReverse(true);
	}
	else
	{
		Entity->SetReverse(false);
	}
}
