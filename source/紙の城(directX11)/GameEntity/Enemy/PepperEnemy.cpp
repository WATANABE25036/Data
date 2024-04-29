/*********************************************************************
 * \file   PepperEnemy.cpp
 * \brief   
 * \author マ　コウリュウ
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "PepperEnemy.h"
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
#include "..\..\particle.h"
#include "..\..\Fsm\State\PepperIdle.h"
#include "..\EntityManager.h"
#include "..\Player\player.h"
#include "..\Player\paperGuardian.h"

#include "..\..\Fsm\State\PepperFoundPlayer.h"

#include "..\..\Fsm\State\PaperEnemyDead.h"

 //---------------------------------------------------
 //グローバル変数
 //---------------------------------------------------
static int g_HitTexNo;




void PepperEnemy::Init()
{
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");

	char se1[] =
	{
		"data\\SE\\hit.wav"
	};
	_SE_hit = LoadSound(&se1[0]);

	_use = false;
	_pos.x = SCREEN_WIDTH / 2;
	_pos.y = SCREEN_HEIGHT / 4;
	_vel.x = PEPPER_SPEED;
	_vel.y = PEPPER_SPEED;
	D3DXVec2Normalize(&_vel, &_vel);
	_vel *= PEPPER_SPEED;
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
	_animeWidthPattern = 7;
	_animeHeightPattern = 2;
	_animeFrameMax = 0;
	_size = D3DXVECTOR2(PEPPER_WIDTH, PEPPER_HEIGHT);
	_move = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_reverse = true;
	_hp = 10;
	_oldHp = 0;


	_hitBox._pos = { _pos.x,_pos.y };
	_hitBox._size = Vec2(100, 100);
	_hitBox._use = true;
	_attackBox._use = false;
	_attackBox._pos = { _pos.x,_pos.y };
	_attackBox._size = Vec2(50, 50);
	


	_unbeatable = false;
	_unbeatableTime = PEPPER_UNBEATABLE_TEME;
	_unbeatableCou = 0;
	_jumpPower = -15;
	_oldGround = false;
	_U = 0.0f;
	_V = 0.0f;
	_UW = 1.0f / PEPPER_WIDTH_PATTERN;
	_VH = 1.0f / PEPPER_HEIGHT_PATTERN;
	_animePattern = 0;
	_use = true;

	_pepperEnemyFsm = new StateMachine<PepperEnemy>(this);
	_pepperEnemyFsm->SetCurrentState(PepperIdel::Instance());
	_pepperEnemyFsm->ChangeState(PepperIdel::Instance());
}

void PepperEnemy::Update()
{
	if (_use)
	{
		_hitBox._pos = { _pos.x - 0,_pos.y - 10 };
		if (_attackBox._use == true)
		{
			_attackBox._pos = { _pos.x - 0,_pos.y - 10 };
		}
		_pepperEnemyFsm->Update();
		
		
	}
}

void PepperEnemy::Draw()
{
	if (_use)
	{
		SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, PEPPER_WIDTH_PATTERN, PEPPER_HEIGHT_PATTERN, PEPPER_WIDTH_PATTERN, _reverse);
		_U = uv.x;
		_V = uv.y;

		_animeSkipFrame = Counter(_animeSkipFrame, PEPPER_FRAME_SPAN);
		if (_animeSkipFrame == 0)
		{
			SetParticle(EFFECT::LIGHT, _pos, 1, 0.1f, 1.5f, false, false, EFFECT::LIGHT, 30,30,30);//黒い光
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

		if (_attackBox._use == true)
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
		}
#endif


	}



}

void PepperEnemy::UnInit()
{
}

void PepperEnemy::Attacked()
{

	auto player=EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	auto pGuardian = EntityManager::Instance()->GetEntitysWithTag<PaperGuardian>("PaperGuardian");
	//float enemyRadian = 0;


	if (_use)
	{
		if (CollisionBB(player->_attackBox._pos.x, player->_attackBox._pos.y, _hitBox._pos.x, _hitBox._pos.y, player->_attackBox._size.x, player->_attackBox._size.y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT))
		{
			SetKnockBackX(-50);
			_hp--;
			_pepperEnemyFsm->ChangeState(PepperFoundPlayer::Instance());
			PlaySound(_SE_hit, 0);

		}

		for(auto p: pGuardian)
		{
			if (p != nullptr && p->GetAttackBox()._use == true&&p->GetUse()==true)
			{
				if (!_unbeatable && CollisionRot(p->GetAttackBox()._pos.x, p->GetAttackBox()._pos.y, _hitBox._pos.x, _hitBox._pos.y, p->GetAttackBox()._size.x, p->GetAttackBox()._size.y, _hitBox._size.x, _hitBox._size.y, 0.0f) && _use)
				{
					_hp--;
					//enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
					//SetPlayerKnockBack(-50, enemyRadian);
					SetKnockBackX(-50);

					if (_hp <= 0)
					{
						p->SetUse(false);
						p->SetAttackUse(false);
					}
					//this->GetFsm()->ChangeState(KumoBossAttacked::Instance());
					PlaySound(_SE_hit, 0);
				}
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





		if (_hp <= 0)
		{
			SetParticle(EFFECT::LIGHT, _pos.x, _pos.y, 30, 0.5f, 15.0f, false, false, EFFECT::LIGHT, 0, 0, 0);
			//	//PlaySound(g_SE_playerDown, 0);
			//_use = false;

			_pepperEnemyFsm->ChangeState(PaperEnemyDead::Instance());

		}
	}

	////ダメージを食らった時の処理
	//else if (_oldHp > _hp)
	//{
	//	_unbeatable = true;
	//	//PlaySound(g_SE_playerHit, 0);
	//}

	////無敵中の処理
	//if (_unbeatable)
	//{
	//	_unbeatableCou = Counter(_unbeatableCou, _unbeatableTime);
	//	if (_unbeatableCou % 10 < 5)
	//	{
	//		_color.a = 0.5f;
	//	}
	//	else
	//	{
	//		_color.a = 0.8f;
	//	}

	//	if (_unbeatableCou == 0)
	//	{
	//		_unbeatable = false;
	//		_color.a = 1.0f;
	//	}
	//}
	//else
	//{
	//	if (_color.a == 0)_color.a = 1;
	//}
}

void PepperEnemy::CollisionHandling()
{
	auto p_Tile = GetMapInfo(_pos, { PEPPER_HITBOX_WIDTH,PEPPER_HITBOX_HEIGHT });

	for (int j = 0; j < 9; j++)
	{
		if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(_pos.x + _hsp, _pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(_pos.x + Sign(_hsp), _pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					_pos.x = _pos.x + Sign(_hsp);
				}
				_hsp = 0;
				_move = -_move;
			}

			//縦に壁がある場合
			if (CollisionRot(_pos.x, _pos.y + _vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(_pos.x, _pos.y + Sign(_vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					_pos.y = _pos.y + Sign(_vsp);
				}
				_vsp = 0;
			}

			if (j == 7)
			{
				if (p_Tile[6].attrib == MAP_ATTRIB_NONE)
				{
					_move = (1);
				}
				if (p_Tile[8].attrib == MAP_ATTRIB_NONE)
				{
					_move=(-1);
				}
			}
		}
	}
}

void PepperEnemy::PositionHandling()
{

	//壁の衝突判定
	CollisionHandling();

	//横移動
	_pos.x += _hsp;

	// ステージループ処理
	loopTrigger = 0;
	notLoopPos.x += _pos.x - oldPos.x;

	if (_pos.x > STAGE_SIZE)
	{
		_pos.x -= STAGE_SIZE;
		loopTrigger = 1;
	}
	else if (_pos.x < 0)
	{
		_pos.x += STAGE_SIZE;
		loopTrigger = -3;
	}

	//縦移動
	_pos.y += _vsp;
	notLoopPos.y = _pos.y;

	//ノックバックが加算されていくのを回避
	if (_vsp != 0)_vsp -= _knockBackY;
	_knockBackY = 0;

	if (_dir > 0) _reverse = false;//進行方向基準
	else if (_dir < 0) _reverse = true;

}