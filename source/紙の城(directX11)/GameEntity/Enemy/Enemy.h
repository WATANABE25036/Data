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
#include "..\..\sound.h"
#include <string>


//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define ENEMY_MAX			(50)//キャラクターの数
#define ENEMY_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//画像横幅
#define ENEMY_HEIGHT		(DEFAULT_TILE_SIZE * 0.5f)//画像縦高さ
#define ENEMY_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//エネミーのヒットボックス横
#define ENEMY_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.5f)//エネミーのヒットボックス縦
#define ENEMY_WIDTH_PATTERN	(4)//横アニメパターン数
#define ENEMY_HEIGHT_PATTERN	(5)//縦アニメパターン数
#define ENEMY_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//フレーム数
#define ENEMY_FRAME_SPAN	(8)//アニメーションのスパン
#define ENEMY_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define ENEMY_SPEED		(4.0f)//エネミーの移動速度
#define ENEMY_UNBEATABLE_TEME (20)//無敵時間
#define ENEMY_INIT_HP (1)


//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
class Enemy:public EntityBase
{
	bool _jump;
	StateMachine<Enemy>* _enemyFsm;
	void GroundDetection();
	

public:
	void Attack(D3DXVECTOR2 targetPos)
	{
		EnemyBulletSpawn::Instance()->SetBullet(_pos, targetPos, 150, 0.8f);
	}
	const bool GetJump()const { return _jump; }
	
	Enemy(int TexNo) :EntityBase("Enemy")
	{
		_textureNo = TexNo;
		Init();
	};
	~Enemy() override
	{ 
		UnInit();
		delete _enemyFsm;
	}

	HitBox _attackBox;

	StateMachine<Enemy>* GetFsm() const { return _enemyFsm; }
	void Attacked();
	// ﾍｨｹ� EntityBase ｼﾌｳﾐ
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	//音
	int _SE_hit;
	int _SE_enemyDown;
	int g_shotTime;
};

