/*********************************************************************
 * \file   player.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "player.h"

#include "..\..\texture.h"
#include "..\..\sprite.h"
#include "..\..\input.h"
#include "..\..\sound.h"
#include "..\..\collision.h"
#include "..\..\main.h"
#include "..\..\tile.h"
#include "..\Enemy\enemy.h"
#include "..\Enemy\SpiderBullet.h"


#include "..\..\particle.h"
#include "..\..\text_create.h"
#include "..\..\score.h"

#include "..\..\item.h"
#include "..\EntityManager.h"
#include "..\..\Fsm\State\PlayerIdle.h"
#include "..\..\Fsm\State\PlayerDead.h"

#include "..\..\Fsm\State\PlayerDamaged.h"
#include "..\Enemy\KumoBoss.h"
#include "..\Enemy\PepperEnemy.h"
#include "../../fade.h"
//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static D3DXVECTOR2 g_LastGroundPos;
static int g_DropRevivalTime;
static int g_DropRevivalCou;
static int g_HitTexNo;

void SetPlayerKnockBack(float power, float radian)
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player->GetUse())
		{
			// ラジアンを度に変換
			double degrees = radian * 180.0f / 3.14159f;

			//上にのみ跳ぶようにする(上半円が右を0°とし0～-180、下半円が左を180°とし180～0)
			if (abs(degrees) < 90.0f) degrees = 45;
			if (abs(degrees) > 90.0f) degrees = 135;

			float radianA = degrees * 3.14159f / 180.0f;

			D3DXVECTOR2 vector = CalculateVector(-power, radianA);

			if (player->GetUse())
			{
				player->SetKnockBackX(vector.x);
				player->SetKnockBackY(vector.y);
			}
		}
	}
}

//---------------------------------------------------
// 反動を設定
//---------------------------------------------------
void SetPlayerGunKick(float power, float radian)
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (player->GetUse())
		{
			player->SetKnockBackX(vector.x);
			player->SetKnockBackY(vector.y);
		}
	}
}


//---------------------------------------------------
// スコアを設定
//---------------------------------------------------
void SetPlayerScore(int add)
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player->score += add;
	}
}

void Player::Init()
{
	_textureNo = LoadTexture((char*)"data/TEXTURE/Player.png");
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");
	//効果音作成
	char se1[] =
	{
		"data\\SE\\move1.wav"
	};
	_SE_move1 = LoadSound(&se1[0]);
	SetVolume(_SE_move1, 0.3f);

	char se2[] =
	{
		"data\\SE\\move2.wav"
	};
	_SE_move2 = LoadSound(&se2[0]);
	SetVolume(_SE_move2, 0.3f);

	char se3[] =
	{
		"data\\SE\\damage.wav"
	};
	_SE_damage = LoadSound(&se3[0]);
	SetVolume(_SE_damage, 0.3f);

	char se4[] =
	{
		"data\\SE\\playerDown.wav"
	};
	_SE_playerDown = LoadSound(&se4[0]);
	SetVolume(_SE_playerDown, 0.3f);

	char se5[] =
	{
		"data\\SE\\attack1.wav"
	};
	_SE_attack1 = LoadSound(&se5[0]);
	SetVolume(_SE_attack1, 0.3f);

	char se6[] =
	{
		"data\\SE\\attack2.wav"
	};
	_SE_attack2 = LoadSound(&se6[0]);
	SetVolume(_SE_attack2, 0.3f);

	char se7[] =
	{
		"data\\SE\\attack3.wav"
	};
	_SE_attack3 = LoadSound(&se7[0]);
	SetVolume(_SE_attack3, 0.3f);

	char se8[] =
	{
		"data\\SE\\attack4.wav"
	};
	_SE_attack4 = LoadSound(&se8[0]);
	SetVolume(_SE_attack4, 0.3f);

	char se9[] =
	{
		"data\\SE\\itemGet.wav"
	};
	_SE_itemGet = LoadSound(&se9[0]);
	SetVolume(_SE_itemGet, 0.3f);

	char se10[] =
	{
		"data\\SE\\landing.wav"
	};
	_SE_landing = LoadSound(&se10[0]);
	SetVolume(_SE_landing, 0.3f);

	char se11[] =
	{
		"data\\SE\\jump.wav"
	};
	_SE_jump = LoadSound(&se11[0]);
	SetVolume(_SE_jump, 0.3f);

	char se12[] =
	{
		"data\\SE\\attack5.wav"
	};
	_SE_attack5 = LoadSound(&se12[0]);
	SetVolume(_SE_attack5, 0.3f);

	char se13[] =
	{
		"data\\SE\\swing.wav"
	};
	_SE_swing = LoadSound(&se13[0]);
	SetVolume(_SE_swing, 0.3f);

	char se14[] =
	{
		"data\\BGM\\GameOver.wav"
	};
	_BGM_GameOver = LoadSound(&se14[0]);
	SetVolume(_BGM_GameOver, 0.3f);


	_pos.x = SCREEN_WIDTH;
	_pos.y = SCREEN_HEIGHT * 1.5f;
	notLoopPos.x = 0;
	notLoopPos.y = 0;
	_vel.x = PLAYER_SPEED;
	_vel.y = PLAYER_SPEED;
	//ベクトルの正規化
	D3DXVec2Normalize(&_vel, &_vel);
	_vel *= PLAYER_SPEED;//目的のスピードにするためにスピードを乗算する
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_hsp = 0;
	_vsp = 0;
	_grv = 0.8;
	_dir = 1.0f;
	_walksp = PLAYER_SPEED;
	_controller = true;
	_hascontrol = false;
	_canjump = 0;
	_jumpSp = -1;
	_knockBackX = 0;
	_knockBackY = 0;
	_ground = false;
	_animeLoop = true;
	_size = D3DXVECTOR2(PLAYER_WIDTH, PLAYER_HEIGHT);
	_hp = PLAYER_INIT_HP;
	_maxHp = PLAYER_INIT_HP;
	_oldHp = PLAYER_INIT_HP;


	_reverse = false;
	_unbeatable = false;
	_unbeatableCou = 0;
	_unbeatableTime = PLAYER_UNBEATABLE_TEME;
	notLoopPos = D3DXVECTOR2(0, 0);
	loopTrigger = 0;
	_use = true;

	_hitBox._pos = { _pos.x, _pos.y + 100.0f };
	_hitBox._size = Vec2(80, 160);
	_hitBox._use = true;


	_attackBox._use = false;
	_attackBox._size = Vec2(200, 100);
	_attackBox._pos = { _pos.x + 100, _pos.y + 50 };

	_animeFrameMax = 0;
	_animePattern = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_animeFrameSpan = PLAYER_FRAME_SPAN;
	_U = 0;
	_V = 0;
	_UW = 1;
	_VH = 1;

	_playerFsm = new StateMachine<Player>(this);
	_playerFsm->SetCurrentState(PlayerIdle::Instance());
	_playerFsm->ChangeState(PlayerIdle::Instance());

	_hpBarInfo.hpBarFrameTexNo = LoadTexture((char*)"data/TEXTURE/waku.png");
	_hpBarInfo.fullHpTexNo = LoadTexture((char*)"data/TEXTURE/bar_g.png");
	_hpBarInfo.notFullHpTexNo = LoadTexture((char*)"data/TEXTURE/bar_r.png");
	_hpBarInfo.size = { 100 * 6, 18 * 5 };
	_hpBar.SetTarget(this);
	_hpBar.SetHpBarInfo(_hpBarInfo);


	_moveLKey = false;
	_moveRKey = false;
	_dashKey = false;
	_attackKey = false;
	_jumpKey = false;
	_specialKey = false;
	_downKey = false;
}

void Player::Update()
{
	if (_use)
	{
		//入力ボタン設定
		_moveLKey = GetKeyboardPress(DIK_A) || IsButtonPressed(0, BUTTON_LEFT) || IsButtonPressed(0, BUTTON_LEFTX);
		_moveRKey = GetKeyboardPress(DIK_D) || IsButtonPressed(0, BUTTON_RIGHT) || IsButtonPressed(0, BUTTON_RIGHTPX);
		_dashKey = GetKeyboardPress(DIK_LSHIFT) || (IsStickX() > 800) || (IsStickX() < -800);//端まで倒すと1000
		_attackKey = GetKeyboardPress(DIK_J) || IsButtonPressed(0, BUTTON_B);
		_specialKey = GetKeyboardPress(DIK_V) || IsButtonPressed(0, BUTTON_Y);
		_jumpKey = GetKeyboardPress(DIK_SPACE) || IsButtonPressed(0, BUTTON_X) || IsButtonPressed(0, BUTTON_A);
		_downKey = GetKeyboardPress(DIK_S) || (IsStickY() > 800) || IsButtonPressed(0, BUTTON_DOWNX);

		if(_moveRKey - _moveLKey != 0) _dir = _moveRKey - _moveLKey;
		_move = _moveRKey - _moveLKey;

		if (!_attackKey)_releaseAttackKey = true;

		_playerFsm->Update();
		_hitBox._pos = { _pos.x, _pos.y + 50.0f };
		_oldGround = _ground;
		_oldHp = _hp;
		_hpBar.Update();
		//アイテム数表示
		SetDrawTextCreate(std::to_string(_itemCount), 350, 215, 3.0f, 2.0f);
	}
	Reset();
}

void Player::PositionHandling()
{
	//移動方向と速度
	_hsp = (_move * _walksp) + _knockBackX;

	//重力
	_vsp = (_vsp + _grv) + _knockBackY;

	//ジャンプ
	_canjump -= 1;

	//壁の衝突判定
	CollisionHandling();

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

	//ノックバックが加算されていくのを回避
	if (_vsp != 0)_vsp -= _knockBackY;
	_knockBackY = 0;

	//横移動
	_pos.x += _hsp;
	//縦移動
	_pos.y += _vsp;

	//地面判定更新
	GroundDetection();

	//絵の表示向き用
	if (_dir > 0) _reverse = false;//進行方向基準
	else if (_dir < 0) _reverse = true;

	//落下時の処理
	//if (_pos.y > SCREEN_HEIGHT + PLAYER_HEIGHT)
	//{
	//	g_DropRevivalCou = Counter(g_DropRevivalCou, g_DropRevivalTime);
	//	if (g_DropRevivalCou == g_DropRevivalTime - 1) _hp--;
	//	if (g_DropRevivalCou == 0) _pos = g_LastGroundPos;
		//Init();

	//}


}

void Player::Reset()
{
	if (_hp <= 0)
	{
		//bool keyRespawn = GetKeyboardTrigger(DIK_R);

		////ゲームオーバー時の処理
		//SetDrawTextCreate("RESPAWN", SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 80, 10, 3);
		//SetDrawTextCreate("R", SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 80, 10, 3);

		//if (keyRespawn)
		//{
		//	Init();
		//}
				//指定シーンに移行
		Init();
	}
}

void Player::Jump(bool Jumpkey)
{
	//ジャンプ
	if ((_canjump > 0) && _jumpKey)
	{
		_vsp = -20;
		_canjump = 0;
	}
}

void Player::TripleJump(bool Jumpkey)
{
	if (_canjump == true && Jumpkey)
	{
		_jumpSp += (9.8f * (1.0f / 2));
		_vsp = _jumpSp;
	}
}


void Player::GroundDetection()
{
	_Tile = GetMapInfo(_pos, { PLAYER_HITBOX_WIDTH,PLAYER_HITBOX_HEIGHT });

	//下が地面の場合
	for (int j = 0; j < 9; j++)
	{
		if ((_Tile[j].attrib == MAP_ATTRIB_STOP) && ( j == 6 || j == 7 || j == 8))
		{
			//地面に触れているかの処理
			if (CollisionRot(_pos.x, _pos.y + 1, _Tile[j].pos.x, _Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				_ground = true;

				if (_oldGround != _ground)
				{
					PlaySound(_SE_landing, 0);
				}

				break;
			}

		}
		else
		{
			_ground = false;
		}
	}

	if (_ground)
	{
		_jumpSp = -22.0f;
		_canjump = 10;
		_knockBackX = 0;
		g_LastGroundPos = _pos;

		//着地時の処理
		if (_oldGround != _ground)
		{
			//エフェクト生成
			Shake(10, 20);
			if (_Tile[4].attrib == MAP_ATTRIB_NATURE)
			{
				SetParticle(EFFECT::LEAF, _pos.x, _pos.y + 50.0f, 20, 0.1f, 15.0f, true, _animePattern % 2);
			}
		}
	}


}

void Player::Attacked()
{

	auto p_Enemy = EntityManager::Instance()->GetEntitysWithTag<Enemy>("Enemy");
	float enemyRadian = 0;
	for (auto x : p_Enemy)
	{
		if (!x->GetUse() || OffScreenJudge(x->GetPosition().x, x->GetPosition().y, ENEMY_HITBOX_WIDTH, ENEMY_HITBOX_HEIGHT))
		{
			continue;
		}
		if (!_unbeatable && CollisionRot(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
		{
			_hp--;
			enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
			_playerFsm->ChangeState(PlayerDamaged::Instance());
			SetPlayerKnockBack(25, enemyRadian);
			break;
		}
	}

	auto p_EnemyBullet = EntityManager::Instance()->GetEntitysWithTag<SpiderBullet>("Bullet");

	for (auto x : p_EnemyBullet)
	{
		if (x->GetAttackBox()._use == true&& x->GetUse()==true)
		{
			/*if (OffScreenJudge(x->GetPosition().x, x->GetPosition().y, x->GetHitBox()._size.x, x->GetHitBox()._size.y))
			{
				continue;
			}*/
			if (!_unbeatable && CollisionBB(x->GetAttackBox()._pos.x, x->GetAttackBox()._pos.y,
				_hitBox._pos.x, _hitBox._pos.y, x->GetAttackBox()._size.x, x->GetAttackBox()._size.y,
				PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT))
			{
				_hp--;
				x->SetUse(false);
				x->SetAttackUse(false);
				_playerFsm->ChangeState(PlayerDamaged::Instance());
				enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
				SetPlayerKnockBack(25, enemyRadian);
				break;
			}
		}
	}




	auto p_Pepper = EntityManager::Instance()->GetEntitysWithTag<PepperEnemy>("PepperEnemy");
	for (auto x : p_Pepper)
	{
		if (!x->GetUse() || OffScreenJudge(x->GetPosition().x, x->GetPosition().y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT))
		{
			continue;
		}
		if (!_unbeatable && CollisionRot(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y, PEPPER_HITBOX_WIDTH, PEPPER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
		{
			_hp--;
			enemyRadian = PointDirectionRadian(_pos.x, _pos.y, x->GetPosition().x, x->GetPosition().y);
			_playerFsm->ChangeState(PlayerDamaged::Instance());
			SetPlayerKnockBack(25, enemyRadian);
			break;
		}
	}

	auto pBoss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");
	if (pBoss->_attackBox._use == true)
	{
		if (!_unbeatable && CollisionRot(pBoss->_attackBox._pos.x, pBoss->_attackBox._pos.y, _pos.x, _pos.y, pBoss->_attackBox._size.x, pBoss->_attackBox._size.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, 0.0f))
		{
			_hp--;
			enemyRadian = PointDirectionRadian(_pos.x, _pos.y, pBoss->GetPosition().x, pBoss->GetPosition().y);
			_playerFsm->ChangeState(PlayerDamaged::Instance());
			SetPlayerKnockBack(50, enemyRadian);

		}
	}

	if (_hp <= 0)
	{
		SetParticle(EFFECT::SPLATTER, _pos.x, _pos.y, 30);
		PlaySound(_SE_playerDown, 0);
		_playerFsm->ChangeState(PlayerDead::Instance());
		//_use = false;

	}
	//ダメージを食らった時の処理
	else if (_oldHp > _hp)
	{
		_unbeatable = true;
		Shake(30, 5);
		PlaySound(_SE_damage, 0);
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


void Player::CollisionHandling()
{
	auto p_Tile = GetMapInfo(_pos, {PLAYER_HITBOX_WIDTH,PLAYER_HITBOX_HEIGHT});
	for (int j = 0; j < 9; j++)
	{
		if (p_Tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(_pos.x + _hsp, _pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(_pos.x + Sign(_hsp), _pos.y, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					
					_pos.x = _pos.x + Sign(_hsp);
				}
				_hsp = 0;
			}

			//縦に壁がある場合
			if (CollisionRot(_pos.x, _pos.y + _vsp, p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				//壁に当たるまで１ピクセル壁に近づける
				while (!CollisionRot(_pos.x, _pos.y + Sign(_vsp), p_Tile[j].pos.x, p_Tile[j].pos.y, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
				{
					
					_pos.y = _pos.y + Sign(_vsp);
				}
				_vsp = 0;
			}
		}
		//壁の中にいるとき(スタック回避)
		if (p_Tile[4].attrib == MAP_ATTRIB_STOP)
		{
			if (p_Tile[3].attrib != MAP_ATTRIB_STOP)_pos.x--;
			if (p_Tile[5].attrib != MAP_ATTRIB_STOP)_pos.x++;
			if (p_Tile[1].attrib != MAP_ATTRIB_STOP)_pos.y--;
		}
	}

}

void Player::Draw()
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	if (_use)
	{
		_oldAnimePattern = _animePattern;

		//アニメーション切り替え時フレームが上限を超えるのを防止
		if (_animePattern >= _animeFrameMax)
		{
			if (_animeLoop)_animePattern = (_animeFrameMax - 1);
			if (!_animeLoop)_animePattern = 0;
		}

		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, PLAYER_WIDTH_PATTERN, PLAYER_HEIGHT_PATTERN, PLAYER_WIDTH_PATTERN, _reverse);

		_U = uv.x;
		_V = uv.y;

		if(_animeLoop || (!_animeLoop && _animePattern != (_animeFrameMax - 1)))//ループしない場合とめる
		{
			_animeSkipFrame = Counter(_animeSkipFrame, _animeFrameSpan);

			if (_animeSkipFrame == 0)
			{
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
	}

	_hpBar.PlayerDraw();

#ifdef _DEBUG
	if (_hitBox._use == true)
	{
		DrawSpriteColorRotateCamera(g_HitTexNo,
			(int)_hitBox._pos.x,
			(int)_hitBox._pos.y,
			_hitBox._size.x, _hitBox._size.y,	//幅、高さ
			0, 0,		//中心UV座標
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
			0, 0,		//中心UV座標
			1, 1,		//テクスチャ幅、高さ
			0, 0.2f, 0.2f, 0.5f,
			0
		);
	}
#endif // DEBUG && 
}

void Player::UnInit()
{
}

bool Player::GetMoveRKey() const
{
	return _moveRKey;
}

bool Player::GetMoveLKey() const
{
	return _moveLKey;
}

bool Player::GetDashKey() const
{
	return _dashKey;
}

bool Player::GetAttackKey() const
{
	return _attackKey;
}

bool Player::GetJumpKey() const
{
	return _jumpKey;
}

bool Player::GetSpecialKey() const
{
	return _specialKey;
}

bool Player::GetDownKey() const
{
	return _downKey;
}
