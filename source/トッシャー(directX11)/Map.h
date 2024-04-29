/*==============================================================================

   マップ [Map.h]
														 Author : 渡邉 修
														 Date   : 2024/01/18
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include <list>
#include "GameWorld.h"

#define MAX_TILE_X (50)//最大50くらい
#define MAX_TILE_Y (50)//最大50くらい
#define ATTRIBUTE_X (MAX_TILE_X - 4)//周りの壁用とオーバーラン対策で-4
#define ATTRIBUTE_Y (MAX_TILE_Y - 4)
#define TILE_HET_SIZE (80.0f)
#define TILE_OFFSET (60.0f)
#define TILE_OFFSET_HALF (TILE_OFFSET * 0.5f)

//タイルの属性
enum TILE_ATTRIBUTE
{
	OUT_RANGE,
	AIR,
	STOP,
};

enum TILE_STATE
{
	TILE_STATE_NONE,
	HEAR_SOUND,
};

//アイテムの属性
enum ITEM_ATTRIBUTE
{
	ITEM_ATTRIBUTE_NONE,
	ITEM_SET,
};

struct TILE
{
	TILE_ATTRIBUTE TileAttribute = OUT_RANGE;
	ITEM_ATTRIBUTE ItemAttribute = ITEM_ATTRIBUTE_NONE;
	D3DXVECTOR3 Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//タイル向き
	TILE_PATTERN TilePattern = TILE_PATTERN_NONE;
	ITEM_PATTERN ItemPattern = ITEM_PATTERN_NONE;
	TILE_STATE TileState = TILE_STATE_NONE;
	bool Player = false;//プレイヤーがいるか
	bool Enemy = false;//エネミーがいるか
	D3DXVECTOR2 arrayPos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};

struct  AROUND_TILE
{
	TILE Top;
	TILE Right;
	TILE Under;
	TILE Left;
};

class Map
{
public:
	Map(GameWorld* gameWorld);
	~Map();

	void Update();

	void CreateMap();//情報をもとにマップを画面上に生成
	AROUND_TILE GetAroundTile(D3DXVECTOR3 pos) const;	//周りのタイルの情報を返す
	AROUND_TILE GetAroundTile(D3DXVECTOR2 pos) const;	//配列版
	void RandomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin);
	void SoundEcho(D3DXVECTOR2 arrayPos);

	TILE GetTile(D3DXVECTOR3 pos) const;
	D3DXVECTOR2 GetArrayPos(D3DXVECTOR3 pos) const;	//位置からmap配列のどこにいるかを返す
	D3DXVECTOR3 GetXYPos(D3DXVECTOR2 arrayPos) const;//map配列から位置のどこにいるかを返す
	D3DXVECTOR3 GetPlayerSpawnPos() const { return m_PlayerSpawnPos; }

private:
	TILE m_Map[MAX_TILE_Y][MAX_TILE_X];
	GameWorld* m_pGameWorld;
	D3DXVECTOR3 m_PlayerOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 m_PlayerOldArrayPos = D3DXVECTOR2(0.0f, 0.0f);
	int m_PlayerNoMoveCou = 0;
	std::list<TILE*> m_TileHistory;//タイルの履歴
	D3DXVECTOR3 m_PlayerSpawnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//プレイヤーのスポーン地点
};

