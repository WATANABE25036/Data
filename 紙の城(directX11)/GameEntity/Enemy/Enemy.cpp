/*********************************************************************
 * \file   enemy.cpp
 * \brief   
 * \author マ　コウリュウ
 * \date   2024 \ 01 \ 17
 *********************************************************************/
#include "enemy.h"
#include "..\..\texture.h"
#include "..\..\sprite.h"
#include "..\..\input.h"
#include "..\..\sound.h"
#include "..\..\collision.h"
#include "..\..\dead.h"
#include "..\..\main.h"
#include "..\..\tile.h"
#include "..\..\hit_spark.h"
#include "..\..\bullet.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\GameEntity\Player\paperGuardian.h"

#include "..\..\Fsm\State\Idle.h"
#include "..\..\particle.h"
#include "..\..\item.h"
#include "EnemySpawn.h"
#include "..\..\Fsm\State\EnemyDead.h"
#include "..\..\Fsm\State\FoundPlayer.h"



static int g_HitTexNo;


void Enemy::Init()
{
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");

	char se1[] =
	{
		"data\\SE\\hit.wav"
	};
	_SE_hit = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\se_enemyDown.wav"
	};
	_SE_enemyDown = LoadSound(&se2[0]);

	SetVolume(_SE_hit, 0.5f);
	SetVolume(_SE_enemyDown, 0.5f);

	_use = false;
	//_pos.x = SCREEN_WIDTH / 2;
	_pos.x = 300;
	//_pos.y = 100;
	_pos.y = SCREEN_HEIGHT / 4;
	_vel.x = ENEMY_SPEED;
	_vel.y = ENEMY_SPEED;
	D3DXVec2Normalize(&_vel, &_vel);
	_vel *= ENEMY_SPEED;
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_hsp = 0;
	_vsp = 0;
	_grv = 0.3f;
	_walksp = 1.0f;
	_controller = true;
	_hascontrol = false;
	_canjump = false;
	_knockBackX = 0;
	_knockBackY = 0;
	_ground = false;
	_animeWidthPattern = 4;
	_animeHeightPattern = 5;
	_animeFrameMax = 0;
	_size = D3DXVECTOR2(ENEMY_WIDTH, ENEMY_HEIGHT);
	_jump = false;
	_move = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_reverse = true;
	_hp = ENEMY_INIT_HP;
	_oldHp = 0;
	_unbeatable = false;
	_unbeatableTime = ENEMY_UNBEATABLE_TEME;
	_unbeatableCou = 0;
	_jumpPower = -15;
	_oldGround = false;
	_U = 0.0f;
	_V = 0.0f;
	_UW = 1.0f / ENEMY_WIDTH_PATTERN;
	_VH = 1.0f / ENEMY_HEIGHT_PATTERN;
	_animePattern = 0;


	_attackBox._use = false;
	_attackBox._size = Vec2(100, 100);
	_attackBox._pos = { _pos.x,_pos.y };

	_hitBox._pos = { _pos.x - 10,_pos.y };
	_hitBox._size = Vec2(100, 100);
	_hitBox._use = true;


	_enemyFsm = new StateMachine<Enemy>(this);
	_enemyFsm->SetCurrentState(Idle::Instance());
	_enemyFsm->ChangeState(Idle::Instance());

	
}

void Enemy::Update()
{
	if (_use)
	{
		_oldGround = _ground;
		_oldHp = _hp;
		
		_hitBox._pos = _pos; 
		_attackBox._pos = _pos;
		
		_enemyFsm->Update();


	}

	
}

void Enemy::Draw()
{
	if (_use)
	{
		SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//僥僋僗僠儍偺僼傿儖僞乕傪OFF
		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, ENEMY_WIDTH_PATTERN, ENEMY_HEIGHT_PATTERN, _animeWidthPattern, _reverse);
		_U = uv.x;
		_V = uv.y;

		_animeSkipFrame = Counter(_animeSkipFrame, ENEMY_FRAME_SPAN / _walksp);
		if (_animeSkipFrame == 0)
		{
			_animePattern = Counter(_animePattern, _animeFrameMax);
		}

		DrawSpriteColorRotateCamera(_textureNo,
			(int)_pos.x,
			(int)_pos.y,
			_size.x, _size.y,	//暆丄崅偝
			_U, _V,		//拞怱UV嵗昗
			_UW, _VH,		//僥僋僗僠儍暆丄崅偝
			_color.r, _color.g, _color.b, _color.a,
			0.0f
		);
	}

#ifdef _DEBUG
	if (_hitBox._use == true)
	{
		DrawSpriteColorRotateCamera(g_HitTexNo,
			(int)_hitBox._pos.x,
			(int)_hitBox._pos.y,
			_hitBox._size.x, _hitBox._size.y,
			0, 0,		//中心UV座標
			1, 1,		//テクスチャ幅、高さ
			1, 0, 0, 0.5f,
			0
		);
	}
	if (_attackBox._use == true)
	{
		DrawSpriteColorRotateCamera(g_HitTexNo,
			(int)_attackBox._pos.x,
			(int)_attackBox._pos.y,
			_attackBox._size.x, _attackBox._size.y,
			0, 0,		//中心UV座標
			1, 1,		//テクスチャ幅、高さ
			0, 0.2f, 0.2f, 0.5f,
			0
		);
	}

#endif // DEBUG && 


}

void Enemy::GroundDetection()
{
	auto p_Tile = GetMapInfo(_pos, { ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT });

	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
		{
			//地面に触れているかの処理
			if (CollisionRot(_pos.x, _pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
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
		_jumpSp = -22.0f;
		_canjump = true;
		_vsp = -2;
		_knockBackX = 0;
	}
}

void Enemy::Attacked()
{

	auto player = EntityManager::Instance()->GetEntitysWithTag<Player>("Player");
	auto pGuardian = EntityManager::Instance()->GetEntitysWithTag<PaperGuardian>("PaperGuardian");
	float enemyRadian = 0;
	for (auto x : player)
	{
		/*if (!x->GetUse() || OffScreenJudge(x->GetPosition().x, x->GetPosition().y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT))
		{
			continue;
		}*/

		if (x->_attackBox._use == true)
		{
			if (!_unbeatable && CollisionRot(x->_attackBox._pos.x, x->_attackBox._pos.y, _hitBox._pos.x, _hitBox._pos.y, x->_attackBox._size.x, x->_attackBox._size.y, _hitBox._size.x, _hitBox._size.y, 0.0f))
			{
				_hp--;
				//enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
				//SetPlayerKnockBack(-50, enemyRadian);
				SetKnockBackX(50);
				_enemyFsm->ChangeState(FoundPlayer::Instance());
				PlaySound(_SE_hit, 0);
				//this->GetFsm()->ChangeState(KumoBossAttacked::Instance());
			}

		}


		/*if (!_unbeatable && CollisionRot(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y, ENEMY_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
		{
			_hp--;
			//enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
			SetKnockBackX(50);
			_enemyFsm->ChangeState(FoundPlayer::Instance());

			break;
		}*/

	}

	for (auto p : pGuardian)
	{
		/*if (!x->GetUse() || OffScreenJudge(x->GetPosition().x, x->GetPosition().y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT))
		{
			continue;
		}*/

		if (p->GetAttackBox()._use == true && p->GetUse() == true)
		{
			if (!_unbeatable && CollisionRot(p->GetAttackBox()._pos.x, p->GetAttackBox()._pos.y, _hitBox._pos.x, _hitBox._pos.y, p->GetAttackBox()._size.x, p->GetAttackBox()._size.y, _hitBox._size.x, _hitBox._size.y, 0.0f) && _use)
			{
				_hp--;
				//enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
				//SetPlayerKnockBack(-50, enemyRadian);
				SetKnockBackX(50);
				_enemyFsm->ChangeState(FoundPlayer::Instance());
				if (_hp <= 0)
				{
					p->SetUse(false);
					p->SetAttackUse(false);
				}
				//this->GetFsm()->ChangeState(KumoBossAttacked::Instance());
			}

		}


		/*if (!_unbeatable && CollisionRot(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y, ENEMY_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
		{
			_hp--;
			//enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
			SetKnockBackX(50);
			_enemyFsm->ChangeState(FoundPlayer::Instance());

			break;
		}*/

	}


	/*auto pBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");
	if (pBoss->_attackBox._use == true)
	{
		if (!_unbeatable && CollisionRot(pBoss->_attackBox._pos.x, pBoss->_attackBox._pos.y, _pos.x, _pos.y, pBoss->_attackBox._size.x, pBoss->_attackBox._size.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, 0.0f))
		{
			_hp--;
			enemyRadian = PointDirectionRadian(_pos.x, _pos.y, pBoss->GetPosition().x, pBoss->GetPosition().y);
			SetPlayerKnockBack(50, enemyRadian);
		}
	}*/

	if (_hp <= 0)
	{
		_enemyFsm->ChangeState(EnemyDead::Instance());
		//_enemyFsm->Update();
		//PlaySound(g_SE_playerDown, 0);
		_use = false;
		_attackBox._use = false;
		_hitBox._use = false;

	}
	//ダメージを食らった時の処理
	else if (_oldHp > _hp)
	{
		_unbeatable = true;
		//PlaySound(g_SE_playerHit, 0);
	}

	//無敵中の処理
	if (_unbeatable)
	{
		_unbeatableCou = Counter(_unbeatableCou, _unbeatableTime);
		/*if (_unbeatableCou % 10 < 5)
		{
			_color.a = 0.5f;
		}
		else
		{
			_color.a = 0.8f;
		}*/

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
}




void Enemy::UnInit()
{
	
}
