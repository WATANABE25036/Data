/*********************************************************************
 * \file   Enemy.h
 * \brief
 *
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "..\..\renderer.h"
#include "..\EntityBase.h"
#include "EnemybulletSpawn.h"
#include "..\..\Fsm\StateMachine.h"
#include "..\..\HpBar.h"
#include <string>

 //---------------------------------------------------
 //マクロ定義
 //---------------------------------------------------
#define BOSS_MAX			(1)//キャラクターの数
#define BOSS_X			(5)
#define BOSS_WIDTH		(256 * BOSS_X)//画像横幅
#define BOSS_HEIGHT		(240 * BOSS_X)//画像縦高さ

#define BOSS_HITBOX_WIDTH	(BOSS_WIDTH * 0.2f)//プレイヤーのヒットボックス横
#define BOSS_HITBOX_HEIGHT	(BOSS_HEIGHT * 0.5f)
#define BOSS_WIDTH_PATTERN	(10)//横アニメパターン数
#define BOSS_HEIGHT_PATTERN	(21)//縦アニメパターン数
#define BOSS_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//フレーム数
#define BOSS_FRAME_SPAN	(8)//アニメーションのスパン
#define BOSS_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define BOSS_SPEED		(10.0f)//エネミーの移動速度
#define BOSS_UNBEATABLE_TEME (20)//無敵時間


//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
class KumoBoss :public EntityBase
{
	bool _jump;
	StateMachine<KumoBoss>* _pFsm;
	void GroundDetection();
	void CollisionHandling();
public:
	KumoBoss() :EntityBase("KumoBoss")
	{
		Init();
	};
	~KumoBoss() override
	{
		UnInit();
		delete _pFsm;
	}

	HitBox _attackBox;
	HitBox _attackBox2;
	bool _animeLoop;
	int _attackDesire;
	const int _attackDesireMax=100;
	int _stamina;
	float _jumpAtkCD;
	bool _canJumpAtk;
	const int _staminaMin=0;
	bool _sleep;
	// ﾍｨｹ� EntityBase ｼﾌｳﾐ
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	StateMachine<KumoBoss>* GetFsm() const { return _pFsm; }
	const bool GetJump()const { return _jump; }
	void PositionHandling();
	void Attacked();

	//音
	int _SE_hit;
	int _BGM_Boss;
	int _BGM_Clear;
	int _SE_attack5;
	int _SE_attack4;
	int _SE_landing;

	//HPバー
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;

	int ResultCount = 0;
};
