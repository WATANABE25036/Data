/*********************************************************************
 * \file   paperGuardian.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 21
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#pragma once
 //---------------------------------------------------
 //マクロ定義
 //---------------------------------------------------
#define PGUARDIAN_MAX			(1)//キャラクターの数
#define PGUARDIAN_WIDTH		(DEFAULT_TILE_SIZE*0.6)//画像横幅
#define PGUARDIAN_HEIGHT		(DEFAULT_TILE_SIZE*0.6)//画像縦高さ
#define PGUARDIAN_HITBOX_WIDTH		(PGUARDIAN_WIDTH * 0.5f)//プレイヤーのヒットボックス横
#define PGUARDIAN_HITBOX_HEIGHT	(PGUARDIAN_HEIGHT)//プレイヤーのヒットボックス縦
#define PGUARDIAN_WIDTH_PATTERN	(7)//横アニメパターン数
#define PGUARDIAN_HEIGHT_PATTERN	(2)//縦アニメパターン数
#define PGUARDIAN_FRAME_MAX	((PGUARDIAN_WIDTH_PATTERN * PGUARDIAN_HEIGHT_PATTERN) -1)//フレーム数
#define PGUARDIAN_FRAME_SPAN	(8)//アニメーションのスパン
#define PGUARDIAN_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define PGUARDIAN_SPEED		(8.0f)//プレイヤーの移動速度
#define PGUARDIAN_INIT_HP		(3)//初期体力
#define PGUARDIAN_UNBEATABLE_TIME (80)//無敵時間





class PaperGuardian :public EntityBase
{
	StateMachine<PaperGuardian>* _paperGuardianFsm;
	void CollisionHandling();

public:
	PaperGuardian(int TexNo) :EntityBase("PaperGuardian")
	{
		_textureNo = TexNo;
		Init();
	}
	~PaperGuardian()
	{
		UnInit();
		delete _paperGuardianFsm;
	}

	//int texPaperGuardian = LoadTexture((char*)"data/TEXTURE/paperGuardian.png");
	StateMachine<PaperGuardian>* GetFsm() const { return _paperGuardianFsm; }


	Vec2 offset;
	void Attacked();
	void PositionHandling();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

