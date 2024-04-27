//===================================================
//タイル(tile.h)
//Auhor:渡邉 修	Date:2023.8.26
//===================================================
#pragma once

#include <list>
#include <array>
#include <vector>
#include "main.h"
#include "renderer.h"

class Player;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAPCHIP_SIZE (DEFAULT_TILE_SIZE) //マップチップサイズ
#define MAP_SIZE_X (500) //1マップ(1画面)横12キャラクター ※g_MapSizeXと同じにする
#define MAP_SIZE_Y (14) //1マップ(1画面)縦7キャラクター ※g_MapSizeYと同じにする
#define MAP_WIDTH_PATTERN (4)
#define MAP_HEIGHT_PATTERN (7)
#define MAP_FRAME_MAX (MAP_WIDTH_PATTERN * MAP_HEIGHT_PATTERN)//フレーム数
#define MAP_SPAWN_TIME (60 * 15)	//敵出現間隔
#define STAGE_SIZE  (MAP_SIZE_X * MAPCHIP_SIZE)
#define MAP_MAX (15)
#define TILE_INIT_SPEED (1)

//*****************************************************************************
// 列挙体宣言
//*****************************************************************************
enum MAPATTRIB //マップのアトリビュート(属性)
{//追加したらタイル取得関数を更新しないと床を貫通する
	MAP_ATTRIB_NONE = 0,	//通過可能(描画されないので注意)
	MAP_ATTRIB_STOP,		//進入不可
	MAP_ATTRIB_NATURE,		//自然
	MAP_ATTRIB_SLOW,		//速度低下
	MAP_ATTRIB_ERROR
};

//*****************************************************************************
// 構造体宣言
//*****************************************************************************
struct MAP_DATA_T //タイル種類ごとのデータ
{
	D3DXVECTOR2 uv;		//テクスチャの左上座標
	MAPATTRIB attrib;	//このマップチップが持つ属性
	bool spawn;			//敵がこのブロック位置に湧くかどうか
};

struct TILE_DATA //タイルごとのデータ
{
	D3DXVECTOR2 uv;
	D3DXVECTOR2 pos;	//中心座標
	MAPATTRIB attrib;	//このマップチップが持つ属性
	bool spawn;			//敵がこのブロック位置に湧くかどうか
	int groupId;			//グループ判別用
	D3DXCOLOR color;
	float spd; //移動スピード
	D3DXVECTOR2 move; //移動量
	D3DXVECTOR2 initPos;	//中心座標
	MAPATTRIB initAttrib;	//このマップチップが持つ属性
	D3DXVECTOR2 XYId;//Xの何番目かとYの何番目か
	bool fadeOut;//フェードアウトしてるかどうか
};

struct POLYGON
{
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		spd;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
};

struct DIRECTION
{
	bool right;
	bool down;
	bool up;
	bool left;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTile(void);
void UninitTile(void);
void UpdateTile(void);
void DrawTile(void);
float GetTileU(int index);
float GetTileV(int index);
D3DXVECTOR2 GetTileUV(int index);
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos);//座標直下のマップ情報を返す
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos, D3DXVECTOR2 size);
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight);
void ChangeTile(std::vector<std::vector<int>>& map1, std::vector<std::vector<int>> map2, int group);
void CatTile(float minPosX, float maxPosX);
std::vector<std::vector<int>> combineArrays(const std::vector<std::vector<int>>& arr1, const std::vector<std::vector<int>>& arr2);//マップを結合
void SetTilePlayer(Player* player);
D3DXVECTOR2 GetMapSize();
