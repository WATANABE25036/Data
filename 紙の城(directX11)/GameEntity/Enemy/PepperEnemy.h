/*********************************************************************
 * \file   PepperEnemy.h
 * \brief   
 * \author マ　コウリュウ
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#pragma once
//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PEPPER_MAX			(1)//キャラクターの数
#define PEPPER_WIDTH		(DEFAULT_TILE_SIZE*0.6)//画像横幅
#define PEPPER_HEIGHT		(DEFAULT_TILE_SIZE*0.6)//画像縦高さ
#define PEPPER_HITBOX_WIDTH		(PEPPER_WIDTH * 0.5f)//プレイヤーのヒットボックス横
#define PEPPER_HITBOX_HEIGHT	(PEPPER_HEIGHT)//プレイヤーのヒットボックス縦
#define PEPPER_WIDTH_PATTERN	(7)//横アニメパターン数
#define PEPPER_HEIGHT_PATTERN	(2)//縦アニメパターン数
#define PEPPER_FRAME_MAX	((PEPPER_WIDTH_PATTERN * PEPPER_HEIGHT_PATTERN) -1)//フレーム数
#define PEPPER_FRAME_SPAN	(8)//アニメーションのスパン
#define PEPPER_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define PEPPER_SPEED		(8.0f)//プレイヤーの移動速度
#define PEPPER_INIT_HP		(3)//初期体力
#define PEPPER_UNBEATABLE_TEME (80)//無敵時間



class PepperEnemy :public EntityBase
{
	StateMachine<PepperEnemy>*		_pepperEnemyFsm;
	void CollisionHandling();

public:
	PepperEnemy(int TexNo):EntityBase("PepperEnemy") 
	{ 
		_textureNo = TexNo;
		Init();
	}
	~PepperEnemy() 
	{ 
		UnInit(); 
		delete _pepperEnemyFsm;
	}

	
	StateMachine<PepperEnemy>* GetFsm() const { return _pepperEnemyFsm; }

	void Attacked();
	void PositionHandling();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	//音
	Vec2 offset;
	float g_time;
	int _SE_hit;
};

