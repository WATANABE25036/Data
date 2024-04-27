/*********************************************************************
 * \file   Tree.h
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 07
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "..\..\renderer.h"
#include "..\EntityBase.h"
//#include "EnemybulletSpawn.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>



 //---------------------------------------------------
 //マクロ定義
 //---------------------------------------------------
#define TREE_MAX			(2)//キャラクターの数
#define TREE_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//画像横幅
#define TREE_HEIGHT		(DEFAULT_TILE_SIZE)//画像縦高さ
#define TREE_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//エネミーのヒットボックス横
#define TREE_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE)//エネミーのヒットボックス縦
#define TREE_WIDTH_PATTERN	(1)//横アニメパターン数
#define TREE_HEIGHT_PATTERN	(2)//縦アニメパターン数
#define TREE_FRAME_MAX	((TREE_WIDTH_PATTERN * TREE_HEIGHT_PATTERN) -1)//フレーム数
#define TREE_FRAME_SPAN	(2)//アニメーションのスパン
#define TREE_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

#define TREE_UNBEATABLE_TEME (20)//無敵時間


//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
class Tree :public EntityBase
{
public:
		//EnemyBulletSpawn::Instance()->SetBullet(_pos, targetPos, 150, 1.0f);
		//TreeBulletSpawn::Instance()->SetBullet(_pos, targetPos, 150, 1.0f);
	}
	//const bool GetJump()const { return _jump; }

	Tree(int TexNo) :EntityBase("Tree")
	{
		_textureNo = TexNo;
		Init();
	};
	~Tree() override
	{
		UnInit();
	}
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

