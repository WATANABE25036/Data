/*********************************************************************
 * \file   Alpaca.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024/03/04
 *********************************************************************/
#pragma once
#define ALPACA_MAX			(50)//キャラクターの数
#define ALPACA_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//画像横幅
#define ALPACA_HEIGHT		(DEFAULT_TILE_SIZE * 0.5f)//画像縦高さ
#define ALPACA_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//エネミーのヒットボックス横
#define ALPACA_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.5f)//エネミーのヒットボックス縦
#define ALPACA_WIDTH_PATTERN	(2)//横アニメパターン数
#define ALPACA_HEIGHT_PATTERN	(4)//縦アニメパターン数
#define ALPACA_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//フレーム数
#define ALPACA_FRAME_SPAN	(8)//アニメーションのスパン
#define ALPACA_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define ALPACA_SPEED		(4.0f)//エネミーの移動速度
#define ALPACA_UNBEATABLE_TEME (20)//無敵時間


#include "GameEntity/EntityBase.h"
#include <vector>
class Alpaca:public EntityBase
{
public:
	Alpaca():EntityBase("Alpaca"),_buffSize(50), _head(0), _tail(0),_full(false)
	{
		Init();
	}

	~Alpaca(){}

	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
private:
	int							_buffSize;
	int							_head;
	int							_tail;
	bool						_full;
	std::vector<D3DXVECTOR2>	_posBuffer;
	void Push(const D3DXVECTOR2& pos);
	D3DXVECTOR2& GetPos(size_t offset);
};
