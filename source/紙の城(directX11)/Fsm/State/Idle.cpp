/*********************************************************************
 * \file   Idle.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "Idle.h"
#include"..\..\Fsm\StateMachine.h"
#include "..\..\tile.h"
#include "..\..\collision.h"
#include "..\..\GameEntity\EntityManager.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\Fsm\State\FoundPlayer.h"


void Idle::EnterState(Enemy* entity)
{
	entity->SetMove(-1);
	entity->_animeFrameMax = 4;
	entity->_animeBasePattern = 12;
	entity->_animeWidthPattern = 4;
	entity->SetWalkSpeed(2.0f);
	entity->SetAttackUse(false);

	if (entity->GetMove() < 0)
	{
		entity->SetReverse(true);
	}
	else
	{
		entity->SetReverse(false);
	}
}

void Idle::StayState(Enemy* entity)
{
	if (entity->GetKnockBackX() != 0)
	{
		if (entity->GetKnockBackX() > 0) entity->SetKnockBackX(entity->GetKnockBackX() - 1.0f);
		if (entity->GetKnockBackX() < 0) entity->SetKnockBackX(entity->GetKnockBackX() + 1.0f);
	}

	//移動方向と速度
	entity->SetHSpeed((entity->GetMove() * entity->GetWalkSpeed()) + entity->GetKnockBackX());

	//重力
	entity->SetVSpeed((entity->GetVSpeed() + entity->GetGravity()) + entity->GetKnockBackY());

	//ジャンプ
	entity->SetCanJump(entity->GetCanJump() - 1);
	if (((entity->GetCanJump() > 0) && entity->GetJump()) || entity->GetGravity() == 0)
	{
		entity->SetVSpeed(entity->GetJumpPower());
		entity->SetCanJump(0);
	}

	//壁の衝突判定

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
				entity->SetReverse(true);
				entity->SetMove(entity->GetMove() * -1);
				
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

			if (j == 7)
			{
				if (tile[6].attrib == MAP_ATTRIB_NONE)
				{
					entity->SetMove(1);
					entity->SetReverse(false);
				}
				if (tile[8].attrib == MAP_ATTRIB_NONE)
				{
					entity->SetMove(-1);
					entity->SetReverse(true);
				}
			}
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
	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		if ((tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
		{
			//地面に触れているかの処理
			if (CollisionRot(entity->GetPosition().x, entity->GetPosition().y + 1, tile[j].pos.x, tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				entity->SetGround(true);
				if (entity->GetOldGround() != entity->GetGround())
				{
					//sound

				}
				break;
			}
			else
			{
				entity->SetGround(false);
			}

		}
	}

	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	if (abs( entity->GetPosition().x-player->GetPosition().x) < 800 && abs(entity->GetPosition().y - player->GetPosition().y) < 100)
	{
		entity->GetFsm()->ChangeState(FoundPlayer::Instance());
	}

	entity->Attacked();


}

void Idle::ExitState(Enemy* entity)
{

}
