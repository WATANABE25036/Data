/*********************************************************************
 * \file   NekoCastle.cpp
 * \brief
 * \author
 * \date   2024 \ 02 \ 26
 *********************************************************************/
#include "NekoCastle.h"
#include "..\..\sprite.h"
#include "..\..\texture.h"
#include "..\..\input.h"
#include "..\..\sound.h"
#include "..\..\collision.h"
//#include "..\..\dead.h"
#include "..\..\main.h"
#include "..\..\tile.h"
#include "..\..\hit_spark.h"
#include "..\..\particle.h"
#include "..\..\item.h"
 //#include "..\..\Fsm\State\PepperIdle.h"
#include "..\EntityManager.h"
#include "..\Player\player.h"

#include "..\Enemy\enemy.h"
#include "..\Enemy\pepperEnemy.h"
#include "..\Enemy\KumoBoss.h"
//#include "..\..\Fsm\State\PepperFoundPlayer.h"

#include "..\..\Fsm\State\CastleIntact.h"

#include "..\..\Fsm\State\NekoCastleFallen.h"



 //---------------------------------------------------
 //グローバル変数
 //---------------------------------------------------
static int g_HitTexNo;




void Castle::Init()
{
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");


	char se1[] =
	{
		"data\\BGM\\GameOver.wav"
	};
	_BGM_GameOver = LoadSound(&se1[0]);

	_use = false;
	_pos.x = 0.0f;
	_pos.y = 1080 * 0.5f;
	//_vel.x = TREE_SPEED;
	//_vel.y = TREE_SPEED;
	//D3DXVec2Normalize(&_vel, &_vel);
	//_vel *= TREE_SPEED;
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_hsp = 0;
	_vsp = 0;
	_grv = 0.3f;
	//_walksp = 1.0f;
	_controller = true;
	_hascontrol = false;
	_canjump = false;
	_knockBackX = 0;
	_knockBackY = 0;
	_ground = false;
	_animeWidthPattern = 1;
	_animeHeightPattern = 1;
	_animeFrameMax = CASTLE_FRAME_MAX;
	_size = D3DXVECTOR2(CASTLE_WIDTH, CASTLE_HEIGHT);
	_move = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_reverse = false;
	_hp = 10;
	_maxHp = 10;
	_oldHp = 0;


	_hitBox._pos = { _pos.x,_pos.y};
	_hitBox._size = Vec2(500, 5000);
	_hitBox._use = true;
	/*_attackBox._use = false;
	_attackBox._pos = { _pos.x,_pos.y };
	_attackBox._size = Vec2(50, 50);*/



	_unbeatable = false;
	_unbeatableTime = CASTLE_UNBEATABLE_TEME;
	_unbeatableCou = 0;
	_jumpPower = -15;
	_oldGround = false;
	_U = 0.0f;
	_V = 0.0f;
	_UW = 1.0f / CASTLE_WIDTH_PATTERN;
	_VH = 1.0f / CASTLE_HEIGHT_PATTERN;
	_animePattern = 0;
	_use = true;

	_CastleFsm = new StateMachine<Castle>(this);
	_CastleFsm->SetCurrentState(CastleIntact ::Instance());
	_CastleFsm->ChangeState(CastleIntact::Instance());
	_hpBarInfo.hpBarFrameTexNo=LoadTexture((char*)"data/TEXTURE/waku.png");
	_hpBarInfo.fullHpTexNo= LoadTexture((char*)"data/TEXTURE/bar_g.png");
	_hpBarInfo.notFullHpTexNo = LoadTexture((char*)"data/TEXTURE/bar_r.png");
	_hpBarInfo.offset = { -50,-100 };
	_hpBarInfo.size = { 300,50 };
	_hpBar.SetTarget(this);
	_hpBar.SetHpBarInfo(_hpBarInfo);
}

void Castle::Update()
{
	if (_use)
	{
		_hitBox._pos = { _pos.x - 0,_pos.y + 700 };
		/*if (_attackBox._use == true)
		{
			_attackBox._pos = { _pos.x - 0,_pos.y - 10 };
		}*/
		GroundDetection();
		_CastleFsm->Update();
		_oldHp = _hp;
		_hpBar.Update();
	}
}

void Castle::Draw()
{
	if (_use)
	{
		SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, CASTLE_WIDTH_PATTERN, CASTLE_HEIGHT_PATTERN, CASTLE_WIDTH_PATTERN, _reverse);
		_U = uv.x;
		_V = uv.y;

		_animeSkipFrame = Counter(_animeSkipFrame, CASTLE_FRAME_SPAN);
		if (_animeSkipFrame == 0)
		{
			_animePattern = Counter(_animePattern, _animeFrameMax);
		}

		if (_textureNo > 0)
		{
			DrawSpriteColorRotateCamera(_textureNo,
				(int)_pos.x,
				(int)_pos.y - 40,
				_size.x, _size.y,	//幅、高さ
				_U, _V,		//中心UV座標
				_UW, _VH,		//テクスチャ幅、高さ
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

		_hpBar.Draw();
	}



}

void Castle::UnInit()
{
}

void Castle::Attacked()
{

	auto enemy = EntityManager::Instance()->GetEntityWithTag<Enemy>("Enemy");
	auto paperEnemy = EntityManager::Instance()->GetEntityWithTag<PepperEnemy>("PepperEnemy");
	//float enemyRadian = 0;


	if (_use)
	{
		if (enemy->_attackBox._use == true && !_unbeatable && CollisionBB(enemy->_attackBox._pos.x, enemy->_attackBox._pos.y, _hitBox._pos.x, _hitBox._pos.y, enemy->_attackBox._size.x, enemy->_attackBox._size.y, CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT))
		{
			_hp--;
		}
	
		if (paperEnemy->GetAttackBox()._use == true && !_unbeatable && CollisionBB(paperEnemy->GetAttackBox()._pos.x, paperEnemy->GetAttackBox()._pos.y, _hitBox._pos.x, _hitBox._pos.y, paperEnemy->GetAttackBox()._size.x, paperEnemy->GetAttackBox()._size.y, CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT))
		{
			_hp--;
		}
	
	
	}



	if (_hp <= 0)
	{
		//SetParticle(EFFECT::SPLATTER, _pos.x, _pos.y, 30);
		//	//PlaySound(g_SE_playerDown, 0);
		//_use = false;

	}
	//ダメージを食らった時の処理
	else if (_oldHp > _hp)
	{
		_unbeatable = true;
		//PlaySound(g_SE_playerHit, 0);

		_CastleFsm->ChangeState(NekoCastleFallen::Instance()); //ゲームオーバー
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
}

void Castle::CollisionHandling()
{
	auto p_Tile = GetMapInfo(_pos, { CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT });

	for (int j = 0; j < 9; j++)
	{
		if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			/*if (CollisionRot(_pos.x + _hsp, _pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(_pos.x + Sign(_hsp), _pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					_pos.x = _pos.x + Sign(_hsp);
				}
				_hsp = 0;
				_move = -_move;
			}*/

			//縦に壁がある場合
			if (CollisionRot(_pos.x, _pos.y + _vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(_pos.x, _pos.y + Sign(_vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					_pos.y = _pos.y + Sign(_vsp);
				}
				_vsp = 0;
			}

			/*if (j == 7)
			{
				if (p_Tile[6].attrib == MAP_ATTRIB_NONE)
				{
					_move = (1);
				}
				if (p_Tile[8].attrib == MAP_ATTRIB_NONE)
				{
					_move = (-1);
				}
			}*/
		}
	}
}

void Castle::PositionHandling()
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
	/*if (_vsp != 0)_vsp -= _knockBackY;
	_knockBackY = 0;

	if (_dir > 0) _reverse = false;//進行方向基準
	else if (_dir < 0) _reverse = true;*/

	if (_pos.y > SCREEN_HEIGHT + PLAYER_HEIGHT)
	{
		_use = false;
	}


}

void Castle::GroundDetection()
{
	auto p_Tile = GetMapInfo(_pos, { CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT });

	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		//if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
		if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 7))
		{
			//地面に触れているかの処理
			if (CollisionRot(_pos.x, _pos.y + 1, p_Tile[j].pos.x, p_Tile[j].pos.y, CASTLE_HITBOX_WIDTH, CASTLE_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
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
		//_jumpSp = -22.0f;
		//_canjump = true;
		_vsp = 0;
		_knockBackX = 0;
	}
	else
	{
		_vsp += 9.8f * (1.0f / 2);
	}
}
