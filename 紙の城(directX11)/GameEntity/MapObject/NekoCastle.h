/*********************************************************************
 * \file   NekoCastle.h
 * \brief
 * \author
 * \date   2024 \ 02 \ 26
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#include "..\..\HpBar.h"
#pragma once
 //---------------------------------------------------
 //マクロ定義
 //---------------------------------------------------
#define CASTLE_MAX			(1)//キャラクターの数
#define CASTLE_WIDTH			(DEFAULT_TILE_SIZE*10)//画像横幅
#define CASTLE_HEIGHT			(DEFAULT_TILE_SIZE*8)//画像縦高さ
#define CASTLE_HITBOX_WIDTH		(CASTLE_WIDTH * 0.8f)//プレイヤーのヒットボックス横
#define CASTLE_HITBOX_HEIGHT	(CASTLE_HEIGHT)//プレイヤーのヒットボックス縦
#define CASTLE_WIDTH_PATTERN	(1)//横アニメパターン数
#define CASTLE_HEIGHT_PATTERN		(1)//縦アニメパターン数
#define CASTLE_FRAME_MAX		((CASTLE_WIDTH_PATTERN * CASTLE_HEIGHT_PATTERN) -1)//フレーム数
#define CASTLE_FRAME_SPAN	(8)//アニメーションのスパン
#define CASTLE_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
//#define TREE_SPEED		(0.0f)//プレイヤーの移動速度
#define CASTLE_INIT_HP		(30)//初期体力
#define CASTLE_UNBEATABLE_TEME (80)//無敵時間



class Castle :public EntityBase
{
	StateMachine<Castle>*	_CastleFsm;
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;
	void CollisionHandling();
public:
	Castle() :EntityBase("Castle")
	{
		Init();
	}
	Castle(int TexNo) :EntityBase("Castle")
	{
		_textureNo = TexNo;
		Init();
	}
	~Castle()
	{
		UnInit();
		delete _CastleFsm;
	}

	StateMachine<Castle>* GetFsm() const { return _CastleFsm; }

	void Attacked();
	void PositionHandling();
	void GroundDetection();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	int _BGM_GameOver;

};

