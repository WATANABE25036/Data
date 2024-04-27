/*********************************************************************
 * \file   Tree.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include "../../texture.h"
#include <string>
#pragma once
 //---------------------------------------------------
 //マクロ定義
 //---------------------------------------------------
#define TREE_MAX			(1)//キャラクターの数
#define TREE_WIDTH			(500 * 5)//画像横幅
#define TREE_HEIGHT		(300 * 5)//画像縦高さ
#define TREE_HITBOX_WIDTH		(TREE_WIDTH * 0.1f)//プレイヤーのヒットボックス横
#define TREE_HITBOX_HEIGHT		(TREE_HEIGHT - 1)//プレイヤーのヒットボックス縦(なんか1ピクセル浮くので-1)
#define TREE_WIDTH_PATTERN		(4)//横アニメパターン数
#define TREE_HEIGHT_PATTERN		(5)//縦アニメパターン数
#define TREE_FRAME_MAX		((TREE_WIDTH_PATTERN * TREE_HEIGHT_PATTERN) -1)//フレーム数
#define TREE_FRAME_SPAN	(8)//アニメーションのスパン
#define TREE_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
//#define TREE_SPEED		(0.0f)//プレイヤーの移動速度
#define TREE_INIT_HP		(5)//初期体力
#define TREE_UNBEATABLE_TEME (80)//無敵時間



class Tree :public EntityBase
{
	StateMachine<Tree>* _TreeFsm;
	void CollisionHandling();
public:
	Tree(int TexNo) :EntityBase("Tree")
	{
		_textureNo = TexNo;
		texPaperGuardian = LoadTexture((char*)"data/TEXTURE/paperGuardian.png");
		texPepper = LoadTexture((char*)"data/TEXTURE/paperenemy.png");
		Init();
	}
	~Tree()
	{
		UnInit();
		delete _TreeFsm;
	}

	StateMachine<Tree>* GetFsm() const { return _TreeFsm; }

	int texPaperGuardian ;
	int texPepper;
	void Attacked();
	void PositionHandling();
	void GroundDetection();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

