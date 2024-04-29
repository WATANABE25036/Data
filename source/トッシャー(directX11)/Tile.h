/*==============================================================================

   マップに並べるタイル(派生) [Tile.h]
														 Author : 渡邉 修
														 Date   : 2024/01/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "BodyParts.h"

//タイルの見た目
enum TILE_PATTERN
{
	//タイルを追加したらここに追加
	//---------------------
	//壁
	TILE_PATTERN_NONE,
	WALL,		//平らな壁
	WALL_END,	//平らな壁端
	PILLAR,		//柱
	CORNER,		//角
	T,			//T字
	CROSS,		//十字
	DEAD_END,	//行き止まり
	//---------------------
	//道
	AISLE,		//通路
	CEILING,	//天井付き床
	//---------------------
};

class Tile : public Object
{
public:
	Tile(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TILE_PATTERN pattern, GameWorld* gameWorld);
	~Tile() override;

	void Init() override;
	void Update() override;

private:

};
