/*********************************************************************
 * \file   player.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "..\..\renderer.h"
#include "..\..\Fsm\StateMachine.h"
#include "..\EntityBase.h"
#include "..\..\camera.h"
#include "..\..\hit_spark.h"
#include "..\..\particle.h"
#include "..\..\sound.h"

#include "..\..\HpBar.h"


//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PLAYER_MAX			(1)//キャラクターの数
#define PLAYER_WIDTH		(660 * 0.8f)//画像横幅
#define PLAYER_HEIGHT		(473 * 0.8f)//画像縦高さ
#define PLAYER_HITBOX_WIDTH		(PLAYER_WIDTH * 0.1f)//プレイヤーのヒットボックス横
#define PLAYER_HITBOX_HEIGHT	(PLAYER_HEIGHT - 65*2)//プレイヤーのヒットボックス縦
#define PLAYER_WIDTH_PATTERN	(9.0f)//横アニメパターン数
#define PLAYER_HEIGHT_PATTERN	(32.0f)//縦アニメパターン数
#define PLAYER_FRAME_MAX	((PLAYER_WIDTH_PATTERN * PLAYER_HEIGHT_PATTERN) -1)//フレーム数
#define PLAYER_FRAME_SPAN	(2)//アニメーションのスパン
#define PLAYER_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define PLAYER_SPEED		(4.0f)//プレイヤーの移動速度
#define PLAYER_DASH_SPEED	(14.0f)//Shiftを押して走ったときの速さ
#define PLAYER_INIT_HP		(5)//初期体力
#define PLAYER_UNBEATABLE_TEME (80)//無敵時間


//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
class Player :public EntityBase
{
public:
	Player() :EntityBase("Player") 
	{
		Init();
		
	}
	~Player() override 
	{ 
		UnInit();
		delete _playerFsm;
	}
	

	bool _animeLoop;
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	void Reset();
	void Jump(bool keyJump);
	void TripleJump(bool Jumpkey);
	void Attacked();
	void PositionHandling();
	StateMachine<Player>* GetFsm()const { return _playerFsm; }
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;

	HitBox _attackBox;

	bool GetMoveRKey() const;
	bool GetMoveLKey() const;
	bool GetDashKey() const;
	bool GetAttackKey() const;
	bool GetJumpKey() const;
	bool GetSpecialKey() const;
	bool GetDownKey() const;

	bool GetReleaseAttackKey() const { return _releaseAttackKey; }
	void SetReleaseAttackKey(bool judge) { _releaseAttackKey = judge; }

	//音
	int _SE_move1;
	int _SE_move2;
	int _SE_damage;
	int _SE_playerDown;
	int _SE_attack1;
	int _SE_attack2;
	int _SE_attack3;
	int _SE_attack4;
	int _SE_itemGet;
	int _SE_landing;
	int _SE_jump;
	int _SE_attack5;
	int _SE_swing;
	int _BGM_GameOver;

private:
	void GroundDetection();
	void CollisionHandling();
	StateMachine<Player>* _playerFsm;

	//入力関係
	bool _moveLKey;
	bool _moveRKey;
	bool _dashKey;
	bool _attackKey;
	bool _jumpKey;
	bool _specialKey;
	bool _downKey;

	//攻撃ボタンを離したか判定
	bool _releaseAttackKey;
};

void SetPlayerGunKick(float power, float radian);
void SetPlayerKnockBack(float power, float radian);
void SetPlayer(float posX, float posY);
void SetPlayerScore(int add);
