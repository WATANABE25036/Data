/*********************************************************************
 * \file   EnemyCastle.h
 * \brief
 * \author
 * \date   2024 \ 03 \ 03
 *********************************************************************/
#pragma once

#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#include "..\..\HpBar.h"

 //---------------------------------------------------
 //マクロ定義
 //---------------------------------------------------
#define ENEMY_CASTLE_MAX			(1)//キャラクターの数
#define ENEMY_CASTLE_WIDTH			(DEFAULT_TILE_SIZE*10)//画像横幅
#define ENEMY_CASTLE_HEIGHT			(DEFAULT_TILE_SIZE*8)//画像縦高さ
#define ENEMY_CASTLE_HITBOX_WIDTH		(ENEMY_CASTLE_WIDTH * 0.8f)//プレイヤーのヒットボックス横
#define ENEMY_CASTLE_HITBOX_HEIGHT	(ENEMY_CASTLE_HEIGHT)//プレイヤーのヒットボックス縦
#define ENEMY_CASTLE_WIDTH_PATTERN	(1)//横アニメパターン数
#define ENEMY_CASTLE_HEIGHT_PATTERN		(1)//縦アニメパターン数
#define ENEMY_CASTLE_FRAME_MAX		((ENEMY_CASTLE_WIDTH_PATTERN * ENEMY_CASTLE_HEIGHT_PATTERN) -1)//フレーム数
#define ENEMY_CASTLE_FRAME_SPAN	(8)//アニメーションのスパン
#define ENEMY_CASTLE_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
//#define TREE_SPEED		(0.0f)//プレイヤーの移動速度
#define ENEMY_CASTLE_INIT_HP		(3000)//初期体力
#define ENEMY_CASTLE_UNBEATABLE_TEME (80)//無敵時間



class EnemyCastle :public EntityBase
{
	StateMachine<EnemyCastle>* _EnemyCastleFsm;
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;
	void CollisionHandling();
public:
	EnemyCastle() :EntityBase("EnemyCastle")
	{
		Init();
	}
	EnemyCastle(int TexNo) :EntityBase("EnemyCastle")
	{
		_textureNo = TexNo;
		Init();
	}
	~EnemyCastle()
	{
		UnInit();
		delete _EnemyCastleFsm;
	}

	StateMachine<EnemyCastle>* GetFsm() const { return _EnemyCastleFsm; }

	void Attacked();
	void PositionHandling();
	void GroundDetection();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;


	int _BGM_Clear;
};

