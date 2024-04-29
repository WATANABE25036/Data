/*********************************************************************
 * \file   Tree.cpp
 * \brief
 * \author 
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "Tree.h"
#include "..\..\sprite.h"
#include "..\..\texture.h"
#include "..\..\input.h"
#include "..\..\sound.h"
#include "..\..\collision.h"
#include "..\..\dead.h"
#include "..\..\main.h"
#include "..\..\tile.h"
#include "..\..\hit_spark.h"
#include "..\..\particle.h"
#include "..\..\item.h"
//#include "..\..\Fsm\State\PepperIdle.h"
#include "..\EntityManager.h"
#include "..\Player\player.h"
#include "..\Player\PaperGuardian.h"

#include "..\Enemy\enemy.h"
//#include "..\Enemy\EnemySpawn.h"
#include "..\Enemy\PepperEnemy.h"
#include "..\Enemy\KumoBoss.h"
//#include "..\..\Fsm\State\PepperFoundPlayer.h"

#include "..\..\Fsm\State\TreeAlive.h"
#include "..\..\Fsm\State\TreeDead.h"


 //---------------------------------------------------
 //グローバル変数
 //---------------------------------------------------
static int g_HitTexNo;




void Tree::Init()
{
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");

	_use = false;
	_pos.x = 1000.0f;
	_pos.y = 700.0f;
	//_vel.x = TREE_SPEED;
	//_vel.y = TREE_SPEED;
	//D3DXVec2Normalize(&_vel, &_vel);
	//_vel *= TREE_SPEED;
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_hsp = 0;
	_vsp = 0;
	_grv = 5.0f;
	_walksp = 1.0f;
	_controller = true;
	_hascontrol = false;
	_canjump = false;
	_knockBackX = 0;
	_knockBackY = 0;
	_ground = false;
	_animeWidthPattern = 5;
	_animeHeightPattern = 4;
	_animeFrameMax = TREE_FRAME_MAX;
	_size = D3DXVECTOR2(TREE_WIDTH, TREE_HEIGHT);
	_move = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_reverse = false;
	_hp = 5;
	_oldHp = 0;


	_hitBox._pos = { _pos.x,_pos.y + 100 };
	_hitBox._size = Vec2(200, 300);
	_hitBox._use = true;
	/*_attackBox._use = false;
	_attackBox._pos = { _pos.x,_pos.y };
	_attackBox._size = Vec2(50, 50);*/



	_unbeatable = false;
	_unbeatableTime = TREE_UNBEATABLE_TEME;

	_canEnemySpawn = false;		//敵生成フラグ
	_canAllySpawn = false;		//味方生成フラグ
	_spawnCounter = 0;			//ユニット生成カウンター

	_unbeatableCou = 0;
	_jumpPower = 0;
	_oldGround = false;
	_U = 0.0f;
	_V = 0.0f;
	_UW = 1.0f / TREE_WIDTH_PATTERN;
	_VH = 1.0f / TREE_HEIGHT_PATTERN;
	_animePattern = 0;
	_use = true;

	_TreeFsm = new StateMachine<Tree>(this);
	_TreeFsm->SetCurrentState(TreeAlive::Instance());
	_TreeFsm->ChangeState(TreeAlive::Instance());
}

void Tree::Update()
{
	_spawnCounter = Counter(_spawnCounter, 300);

	if (_use)
	{
		_hitBox._pos = { _pos.x - 0,_pos.y + 100};

		_TreeFsm->Update();


	}
}

void Tree::PositionHandling()
{
	//重力
	_vsp = _vsp + _grv;

	//壁の衝突判定
	_ground = false;
	CollisionHandling();

	//縦移動
	_pos.y += _vsp;
}

void Tree::Draw()
{
	if (_use)
	{
		SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, TREE_WIDTH_PATTERN, TREE_HEIGHT_PATTERN, TREE_WIDTH_PATTERN, _reverse);
		_U = uv.x;
		_V = uv.y;

		_animeSkipFrame = Counter(_animeSkipFrame, TREE_FRAME_SPAN);
		if (_animeSkipFrame == 0)
		{
			_animePattern = Counter(_animePattern, _animeFrameMax);
		}

		DrawSpriteColorRotateCamera(_textureNo,
			(int)_pos.x,
			(int)_pos.y,
			_size.x, _size.y,	//幅、高さ
			_U, _V,		//中心UV座標
			_UW, _VH,		//テクスチャ幅、高さ
			_color.r, _color.g, _color.b, _color.a,
			0.0f
		);

#ifdef _DEBUG
		if (_hitBox._use == true)
		{
			DrawSpriteColorRotateCamera(g_HitTexNo,
				(int)_hitBox._pos.x,
				(int)_hitBox._pos.y,
				_hitBox._size.x, _hitBox._size.y,	//幅、高さ
				0.5, 0.5,		//中心UV座標
				1, 1,		//テクスチャ幅、高さ
				1, 0.2, 0.2, 0.5f,
				0
			);
		}

		/*if (_attackBox._use == true)
		{
			DrawSpriteColorRotateCamera(g_HitTexNo,
				(int)_attackBox._pos.x,
				(int)_attackBox._pos.y,
				_attackBox._size.x, _attackBox._size.y,
				0.5, 0.5,		//中心UV座標
				1, 1,		//テクスチャ幅、高さ
				0, 0.2f, 0.2f, 0.5f,
				0
			);
		}*/
#endif


	}



}

void Tree::UnInit()
{
}

void Tree::Attacked()
{

	auto enemy = EntityManager::Instance()->GetEntityWithTag<Enemy>("Enemy");
	auto enemyBullet = EntityManager::Instance()->GetEntityWithTag<SpiderBullet>("Bullet");

	auto paperEnemy = EntityManager::Instance()->GetEntityWithTag<PepperEnemy>("PepperEnemy");
	auto kumoBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");

	if (_use)
	{
		if (enemy->GetAttackBox()._use == true)
		{
			if (CollisionBB(enemy->_attackBox._pos.x, enemy->_attackBox._pos.y, _hitBox._pos.x, 
				_hitBox._pos.y, enemy->_attackBox._size.x, enemy->_attackBox._size.y, 
				TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT))
			{
				_hp--;
			}

			if (!_unbeatable && CollisionRot(_pos.x, _pos.y, enemy->GetPosition().x, enemy->GetPosition().y, ENEMY_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				_hp--;
			
				//break;
			}
		}

		if (enemyBullet->GetAttackBox()._use == true)
		{
			if (CollisionBB(enemyBullet->GetAttackBox()._pos.x, enemyBullet->GetAttackBox()._pos.y,
				_hitBox._pos.x, _hitBox._pos.y, enemyBullet->GetAttackBox()._size.x, enemyBullet->GetAttackBox()._size.y,
				TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT))
			{
				_hp--;
			}
		}

		if (paperEnemy->GetAttackBox()._use == true)
		{
			if (CollisionBB(paperEnemy->GetAttackBox()._pos.x, paperEnemy->GetAttackBox()._pos.y, _hitBox._pos.x, _hitBox._pos.y, paperEnemy->GetAttackBox()._size.x, paperEnemy->GetAttackBox()._size.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT))
			{
				_hp--;
			}
		}

		if (kumoBoss->GetAttackBox()._use == true)
		{
			if (CollisionBB(kumoBoss->GetAttackBox()._pos.x, kumoBoss->GetAttackBox()._pos.y, _hitBox._pos.x, _hitBox._pos.y, kumoBoss->GetAttackBox()._size.x, kumoBoss->GetAttackBox()._size.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT))
			{
				_hp--;
			}
		}

	}




	if (_hp <= 0)
	{
		//SetParticle(EFFECT::SPLATTER, _pos.x, _pos.y, 30, 0, 0, 0);
		//	//PlaySound(g_SE_playerDown, 0);
		//_use = false;

		_TreeFsm->ChangeState(TreeDead::Instance());
		//_unbeatable = true;
		_canEnemySpawn = true;

	}
	

	//無敵中の処理
	if (_unbeatable)
	{
			_unbeatableCou = Counter(_unbeatableCou, _unbeatableTime);
			if (_unbeatableCou % 10 < 5)
			{
				_color.a = 0.5f;
			}
		else
		{
			_color.a = 0.8f;
		}

		if (_unbeatableCou == 0)
		{
			_unbeatable = false;
			_color.a = 1.0f;
		}
	}
	else
	{
		if (_color.a == 0)_color.a = 1;
	}


	/*if (_canEnemySpawn)
	{
		if (_spawnCounter % 6000 == 0)
		{
			Spawner::Instance()->SetEnemy({ _pos.x, _pos.y });
		}
	}
	else
	{
		if (_spawnCounter % 6000 == 0)
		{
			
			Spawner::Instance()->SetFor<PaperGuardian>({ _pos.x, _pos.y }, paperGuardian.texPaperGuardian, 1.0);
			
		}
	}*/


}

void Tree::CollisionHandling()
{
	auto p_Tile = GetMapInfo(_pos, { TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT });

	if (p_Tile[7].attrib == MAP_ATTRIB_STOP)
	{
		//縦に壁がある場合
		if (CollisionRot(_pos.x, _pos.y + _vsp, p_Tile[7].pos.x, p_Tile[7].pos.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
		{
			//壁に当たるまで１ピクセル壁に近づける
			while (!CollisionRot(_pos.x, _pos.y + Sign(_vsp), p_Tile[7].pos.x, p_Tile[7].pos.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				_pos.y = _pos.y + Sign(_vsp);
			}
			_vsp = 0;
			_ground = true;
		}
	}
}

void Tree::GroundDetection()
{
	auto p_Tile = GetMapInfo(_pos, { TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT });

	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 7))
		{
			//地面に触れているかの処理
			if (CollisionRot(_pos.x, _pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				_ground = true;

				if (_oldGround != _ground)
				{
					//PlaySound(g_SE_landing, 0);
				}

				break;
			}
			else
			{
				_ground = false;
			}
		}
	}

	if (_ground)
	{
		_knockBackX = 0;
	}
}
