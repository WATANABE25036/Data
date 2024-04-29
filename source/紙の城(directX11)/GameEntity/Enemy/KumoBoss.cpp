/*********************************************************************
 * \file   KumoBoss.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#include "KumoBoss.h"
#include "..\..\texture.h"
#include "..\..\sprite.h"
#include "..\..\input.h"
#include "..\..\sound.h"
#include "..\..\collision.h"
#include "..\..\main.h"
#include "..\..\tile.h"
#include "..\..\particle.h"
#include "..\..\text_create.h"
#include "..\..\score.h"
#include "..\..\item.h"
#include "..\EntityManager.h"
#include "..\Player\player.h"
#include "..\Player\paperGuardian.h"
#include "..\..\Fsm\State\KumoBossSleep.h"
#include "..\..\Fsm\State\KumoBossAttacked.h"
#include "..\MapObject\EnemyCastle.h"

#include "..\..\Fsm\State\EnemyCastleFallen.h"
#include "../../fade.h"


static int g_HitTexNo;
void KumoBoss::Init()
{
	_textureNo = LoadTexture((char*)"data/TEXTURE/kumoboss_revised.png");
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");

	char se1[] =
	{
		"data\\SE\\hit.wav"
	};
	_SE_hit = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\BGM\\Boss.wav"
	};
	_BGM_Boss = LoadSound(&se2[0]);
	//SetVolume(_BGM_Boss, 0.02f);

	char se3[] =
	{
		"data\\BGM\\Clear.wav"
	};
	_BGM_Clear = LoadSound(&se3[0]);

	char se4[] =
	{
		"data\\SE\\attack5.wav"
	};
	_SE_attack5 = LoadSound(&se4[0]);

	char se5[] =
	{
		"data\\SE\\attack4.wav"
	};
	_SE_attack4 = LoadSound(&se5[0]);

	char se6[] =
	{
		"data\\SE\\se_landing.wav"
	};
	_SE_landing = LoadSound(&se6[0]);


	_pos.x = 10000;
	_pos.x = GetMapSize().x - 2000;
	_pos.y = 1000;
	notLoopPos.x = 0;
	notLoopPos.y = 0;
	_vel.x = BOSS_SPEED;
	_vel.y = BOSS_SPEED;
	//ベクトルの正規化
	D3DXVec2Normalize(&_vel, &_vel);
	_vel *= BOSS_SPEED;//目的のスピードにするためにスピードを乗算する
	_color = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	_hsp = 0;
	_vsp = 0;
	_grv = 5.0f;
	_dir = 1.0f;

	_stamina = 100;
	_attackDesire = 20;

	_walksp = BOSS_SPEED;
	_canjump = true;
	_jumpAtkCD = 15;
	_canJumpAtk = true;
	_jumpSp = -1;
	_ground = false;
	_animeLoop = true;
	_size = D3DXVECTOR2(BOSS_WIDTH, BOSS_HEIGHT);
	_maxHp = _oldHp = _hp = 100;
	_reverse = false;
	_unbeatable = false;
	_unbeatableCou = 0;
	_unbeatableTime = BOSS_UNBEATABLE_TEME;
	notLoopPos = D3DXVECTOR2(0, 0);
	loopTrigger = 0;
	_move = 0;
	_jumpPower = 0;

	_hitBox._pos = { _pos.x,_pos.y + 60 /** BOSS_X*/ };
	_hitBox._size = Vec2(BOSS_HITBOX_WIDTH, BOSS_HITBOX_HEIGHT);
	_hitBox._use = true;
	_attackBox._use = false;
	_attackBox._size = Vec2(800, 800);
	_attackBox._pos = { _pos.x - 300,_pos.y + 200};
	_use = true;
	/*_attackBox2._use = false;
	_attackBox2._size = Vec2(180, 180);
	_attackBox2._pos = { _pos.x + 300,_pos.y + 700 };*/

	_animeFrameMax = 0;
	_animePattern = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_U = 0;
	_V = 0;
	_UW = 1.0f / 10.0f;
	_VH = 1.0f / 21.0f;
	_pFsm = new StateMachine<KumoBoss>(this);
	_pFsm->SetCurrentState(KumoBossSleep::Instance());
	_pFsm->ChangeState(KumoBossSleep::Instance());
	_hpBarInfo.hpBarFrameTexNo = LoadTexture((char*)"data/TEXTURE/waku.png");
	_hpBarInfo.fullHpTexNo = LoadTexture((char*)"data/TEXTURE/bar_g.png");
	_hpBarInfo.notFullHpTexNo = LoadTexture((char*)"data/TEXTURE/bar_r.png");
	_hpBarInfo.offset = { 0,-100 };
	_hpBarInfo.size = { 100 * 15, 18 * 5 };
	_hpBar.SetTarget(this);
	_hpBar.SetHpBarInfo(_hpBarInfo);
}

void KumoBoss::Update()
{
	if (_use)
	{
		_oldGround = _ground;
		_oldHp = _hp;
		_hitBox._pos = { _pos.x,_pos.y + 60 * BOSS_X };
		Attacked();
		_pFsm->Update();
		_hpBar.Update();
	}
	else
	{
		ResultCount++;
		if (ResultCount > 180)
		{
			//指定シーンに移行
			SetFadeColor(1.0f, 1.0f, 1.0f);
			SetFade(FADE_STATE_OUT);//フェードアウト開始リクエスト
			SceneTransition(SCENE_RESULT);
		}
	}
}

void KumoBoss::Draw()
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	if (_use)
	{
		_oldAnimePattern = _animePattern;

		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, BOSS_WIDTH_PATTERN, BOSS_HEIGHT_PATTERN, BOSS_WIDTH_PATTERN, _reverse);

		_U = uv.x;
		_V = uv.y;

		if (_animeLoop || (!_animeLoop && _animePattern != (_animeFrameMax - 1)))//ループしない場合とめる
		{
			_animeSkipFrame = Counter(_animeSkipFrame, BOSS_FRAME_SPAN);

			if (_animeSkipFrame == 0)
			{
				SetHitSpark(EFFECT::LIGHT, _pos.x, _pos.y, false, 0.0f, 150, 55, 55);
				_animePattern = Counter(_animePattern, _animeFrameMax);
			}
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

		if(!_sleep) _hpBar.BossDraw();
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
		/*DrawSpriteColorRotateCamera(g_HitTexNo,
			(int)_attackBox2._pos.x,
			(int)_attackBox2._pos.y,
			_attackBox._size.x, _attackBox._size.y,
			0.0f, 0.0f,		//中心UV座標
			1, 1,		//テクスチャ幅、高さ
			0, 0.2f, 0.2f, 0.5f,
			0
		);

	}*/
#endif // DEBUG && 
}

void KumoBoss::UnInit()
{
}

void KumoBoss::GroundDetection()
{
	auto p_Tile = GetMapInfo(_hitBox._pos, _hitBox._size);

	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		//if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 6 || j == 7 || j == 8))
		if ((p_Tile[j].attrib == MAP_ATTRIB_STOP) && (j == 7))
		{
			//地面に触れているかの処理
			if (CollisionRot(_hitBox._pos.x, _hitBox._pos.y + 5, p_Tile[j].pos.x, p_Tile[j].pos.y, _hitBox._size.x, _hitBox._size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
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
		_vsp = 0;
		_knockBackX = 0;
	}
}

void KumoBoss::CollisionHandling()
{
	auto p_Tile = GetMapInfo(_hitBox._pos,_hitBox._size);

	for (int j = 0; j < 9; j++)
	{
		if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(_hitBox._pos.x + _hsp, _hitBox._pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, _hitBox._size.x, _hitBox._size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				_hsp = 0;
				if (p_Tile[j].pos.x >= _hitBox._pos.x)
				{
					_pos.x = _pos.x - _hsp;
				}
				else
				{
					_pos.x = _pos.x + _hsp;
				}
			}

			if (CollisionRot(_hitBox._pos.x, _hitBox._pos.y + _vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, _hitBox._size.x, _hitBox._size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				_vsp = 0;
				_pos.y = _pos.y - _vsp;
				
			}

		}
	}
}

void KumoBoss::PositionHandling()
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

	GroundDetection();

	if (_dir < 0) _reverse = false;//進行方向基準
	else if (_dir > 0) _reverse = true;
}






void KumoBoss::Attacked()
{

	auto player = EntityManager::Instance()->GetEntitysWithTag<Player>("Player");
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
				PlaySound(_SE_hit, 0);
				x->SetOldHp(x->GetHp());
				_hp--;
				_attackDesire += 15;
				x->_attackBox._use = false;
				SetKnockBackX(50);
			}


			if (!_unbeatable && CollisionRot(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y, BOSS_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				PlaySound(_SE_hit, 0);
				_hp--;
				enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
				SetPlayerKnockBack(50, enemyRadian);
				break;
			}
		}

	}

	auto pGuardian = EntityManager::Instance()->GetEntitysWithTag<PaperGuardian>("PaperGuardian");
	for (auto p : pGuardian)
	{
		/*if (!x->GetUse() || OffScreenJudge(x->GetPosition().x, x->GetPosition().y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT))
		{
			continue;
		}*/

		if (p->GetAttackBox()._use == true && p->GetUse() == true)
		{
			if (!_unbeatable && CollisionRot(p->GetAttackBox()._pos.x, p->GetAttackBox()._pos.y, _hitBox._pos.x, _hitBox._pos.y, p->GetAttackBox()._size.x, p->GetAttackBox()._size.y, _hitBox._size.x, _hitBox._size.y, 0.0f)&&_use)
			{
				_hp--;
				//enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
				//SetPlayerKnockBack(-50, enemyRadian);
				//this->GetFsm()->ChangeState(KumoBossAttacked::Instance());
				SetKnockBackX(50);
				p->SetUse(false);
				p->SetAttackUse(false);
				//this->GetFsm()->ChangeState(KumoBossAttacked::Instance());
			}

		}
	}


	if (_hp <= 0)
	{
		SetParticle(EFFECT::HIT_SPARK, _pos.x, _pos.y, 100, 0.5f, 35.0f, false, false, EFFECT::NONE, 0.0f, 0.0f, 0.0f);
		SetParticle(EFFECT::SPLATTER, _pos.x, _pos.y, 100, 0.5f, 35.0f, false, false, EFFECT::NONE, 15.0f, 15.0f, 15.0f);
		SetParticle(EFFECT::BALL, _pos.x, _pos.y, 100, 0.5f, 35.0f, false, false, EFFECT::HIT_SPARK, 30.0f, 30.0f, 30.0f);
		//PlaySound(g_SE_playerDown, 0);

		/*auto enemyCastle = EntityManager::Instance()->GetEntityWithTag<EnemyCastle>("EnemyCastle");
		if (enemyCastle->GetUse() == true)
		{
			enemyCastle->GetFsm()->ChangeState(EnemyCastleFallen::Instance());
		}*/

		StopSoundAll();
		PlaySound(_BGM_Clear, -1, 0.4f);


		_use = false;
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
