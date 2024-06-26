//===================================================
//タイル(tile.cpp)
//Auhor:渡邉 修	Date:2023.8.26
//===================================================
#include "tile.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "GameEntity/Player/player.h"
#include "GameEntity/Enemy/enemy.h"
#include "GameEntity/Enemy/EnemySpawn.h"
#include "GameEntity/Enemy/PepperEnemy.h"
#include "score.h"
#include "gun.h"
#include <list>
#include <array>
#include <vector>
#include <unordered_map>
#include "input.h"
#include "range_select.h"

#include "GameEntity/MapObject/Tree.h"
#include "GameEntity/MapObject/NekoCastle.h"

#include "GameEntity/MapObject/EnemyCastle.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_Ground;	//背景用のテクスチャ番号
static int g_Filter;
static float g_UW;
static float g_VH;
static std::vector<TILE_DATA> g_Map; //マップのデータ
static int g_SpawnTimeCou;
static int g_SpawnTime;
static int g_SpawnNum;
static int g_Wave;
int g_MapSizeX = 10; // マップ横サイズ
int g_MapSizeY = 0; // マップ縦サイズ
size_t g_MapSize = 0;
Player* p_Player;
static int mapInitSizeY;
static int mapInitSizeX;

MAP_DATA_T g_MapInfo[MAP_FRAME_MAX] =
{
	//左上座標とマップチップ属性の設定
	//通常
	{ GetTileUV(0), MAP_ATTRIB_NONE, false},	//0無
	{ GetTileUV(1), MAP_ATTRIB_STOP, false},	//1地面左
	{ GetTileUV(2), MAP_ATTRIB_STOP, false},	//2地面上
	{ GetTileUV(3), MAP_ATTRIB_STOP, false},	//3地面右
	{ GetTileUV(4), MAP_ATTRIB_STOP, false},	//4塗りつぶし一色
	{ GetTileUV(5), MAP_ATTRIB_STOP, false},	//5塗りつぶし(小さい石)
	{ GetTileUV(6), MAP_ATTRIB_STOP, false},	//6塗りつぶし
	{ GetTileUV(7), MAP_ATTRIB_STOP, false},	//7塗りつぶし(大きい石)
	{ GetTileUV(8), MAP_ATTRIB_STOP, false},	//8内角右
	{ GetTileUV(9), MAP_ATTRIB_STOP, false},	//9内角左
	{ GetTileUV(10), MAP_ATTRIB_STOP, false},	//10無(通り抜け不可)
	//青
	{ GetTileUV(13), MAP_ATTRIB_STOP, true},	//11地面左
	{ GetTileUV(14), MAP_ATTRIB_STOP, true},	//12地面上
	{ GetTileUV(15), MAP_ATTRIB_STOP, true},	//13地面右
	{ GetTileUV(16), MAP_ATTRIB_STOP, false},	//14塗りつぶし一色
	{ GetTileUV(17), MAP_ATTRIB_STOP, false},	//15塗りつぶし(小さい石)
	{ GetTileUV(18), MAP_ATTRIB_STOP, false},	//16塗りつぶし
	{ GetTileUV(19), MAP_ATTRIB_STOP, false},	//17塗りつぶし(大きい石)
	{ GetTileUV(20), MAP_ATTRIB_STOP, false},	//18内角右
	{ GetTileUV(21), MAP_ATTRIB_STOP, false},	//19内角左

	//自然
	{ GetTileUV(24), MAP_ATTRIB_NATURE, false},//20草
	{ GetTileUV(25), MAP_ATTRIB_NATURE, false},//21草小
	{ GetTileUV(26), MAP_ATTRIB_NATURE, false},//22花黄色
	{ GetTileUV(27), MAP_ATTRIB_NATURE, false},//23しめじ
	//マップチップの種類分作成する
};

//マップデーター(1画面分)
const int P = 'P';	// プレイヤー
const int E = 'E';	// エネミー
const int E2 = 'E2';	// エネミー
const int T = 'T';	//木オブジェクト
const int C = 'C'; //城オブジェクト
const int 口 = 1;	// 地面上
const int 田 = 11;	// 地面上
const int 外 = 10;	// 地面上
const int TT = 'TT';  //とげとげの木
const int ０ = 0;


struct MAP_DATA
{
	std::vector<std::vector<int>> mapData;
	float rate;
};

//各々の属性を入れる
// 
//--------------------------------------------------
//初期マップ
std::vector<std::vector<int>> g_MapAttribDataS =
{ {
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //0
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //1
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //2
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //3
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //4
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //5
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //6
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //7
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //8
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //9
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //0
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //1
	{{外,外,外,外,０,０,０,０,０,０,０,０,０,０,０}}, //2
	{{外,外,外,外,口,口,口,口,口,口,口,口,口,口,口}}, //3
	{{外,外,外,外,口,口,口,口,口,口,口,口,口,口,口}}, //4 ほぼ画面外
	{{外,外,外,外,口,口,口,口,口,口,口,口,口,口,口}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapDataS{ g_MapAttribDataS, 0.0f };//排出確率
//--------------------------------------------------これで1マップ


//--------------------------------------------------
std::vector<std::vector<int>> g_MapAttribData1 =
{ {
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０,０,０}}, //7
	{{０,０,０,０,０, T,０,０, E,０}}, //8
	{{０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{口,口,口,口,口,口,口,口,口,口}}, //2
	{{口,口,口,口,口,口,口,口,口,口}}, //3
	{{口,口,口,口,口,口,口,口,口,口}}, //4 ほぼ画面外
	{{口,口,口,口,口,口,口,口,口,口}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData1{ g_MapAttribData1, 35.0f };//排出確率
//--------------------------------------------------これで1マップ

std::vector<std::vector<int>> g_MapAttribData2 =
{ {
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０, E, E,０,０,０, E}}, //7
	{{０,０,０,０,０,０,０,０,０,０}}, //8
	{{０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,口,口,口,口,０,０,０}}, //1
	{{０,０,口,口,口,口,口,口,口,０}}, //2
	{{口,口,口,口,口,口,口,口,口,口}}, //3
	{{口,口,口,口,口,口,口,口,口,口}}, //4 ほぼ画面外
	{{口,口,口,口,口,口,口,口,口,口}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData2{ g_MapAttribData2, 35.0f };
//--------------------------------------------------これで1マップ

std::vector<std::vector<int>> g_MapAttribData3 =
{ {
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０,０,０}}, //7
	{{０,０,０, T,０,０,０,０,０, T}}, //8
	{{０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{口,口,０,０,０,口,口,口,０,０}}, //2
	{{口,口,口,口,口,口,口,口,口,口}}, //3
	{{口,口,口,口,口,口,口,口,口,口}}, //4 ほぼ画面外
	{{口,口,口,口,口,口,口,口,口,口}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData3{ g_MapAttribData3, 35.0f };
//--------------------------------------------------これで1マップ

std::vector<std::vector<int>> g_MapAttribData4 =
{ {
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０,０,０}}, //7
	{{０,０,０,０,０,０,０,０,０,０}}, //8
	{{０,０,０,０,０,E2,０,０,０,０}}, //9
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０}}, //2
	{{田,田,田,田,田,田,田,田,田,田}}, //3
	{{田,田,田,田,田,田,田,田,田,田}}, //4 ほぼ画面外
	{{田,田,田,田,田,田,田,田,田,田}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData4{ g_MapAttribData4, 25.0f };
//--------------------------------------------------これで1マップ

std::vector<std::vector<int>> g_MapAttribData5 =
{ {
	{{０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０, T,０}}, //7
	{{０,０,０,０,０,０,０,０,０,０}}, //8
	{{０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,田,田,０,E2,０,０,０,０}}, //0
	{{０,田,田,田,０,０,０,０,０,０}}, //1
	{{田,田,田,田,０,０,０,田,田,田}}, //2
	{{田,田,田,田,田,田,田,田,田,田}}, //3
	{{田,田,田,田,田,田,田,田,田,田}}, //4 ほぼ画面外
	{{田,田,田,田,田,田,田,田,田,田}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData5{ g_MapAttribData5, 25.0f };
//--------------------------------------------------これで1マップ

std::vector<std::vector<int>> g_MapAttribData6 =
{ {
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０, T,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //7
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //8
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,０,田,田,田,田,田,田,田,田,田,田,田,０,０,０,０}}, //0
	{{０,０,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,０}}, //1
	{{０,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //2
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //3
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //4 ほぼ画面外
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData6{ g_MapAttribData6, 25.0f };
//--------------------------------------------------これで1マップ
// 
std::vector<std::vector<int>> g_MapAttribData7 =
{ {
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０,０,０,E2,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,E2,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //7
	{{０,０,０,０,E2,０,０,０,０,０,０,０,０,０,０}}, //8
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,０,０,０,田,田,田,田,田,田,田,田,０,０}}, //0
	{{０,０,０,田,田,田,田,田,田,田,田,田,田,０,０}}, //1
	{{０,田,田,田,田,田,田,田,田,田,田,田,田,０,０}}, //2
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //3
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //4 ほぼ画面外
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData7{ g_MapAttribData7, 25.0f };
//--------------------------------------------------これで1マップ
// 
std::vector<std::vector<int>> g_MapAttribData8 =
{ {
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //1
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //2
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //3
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //4
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //5
	{{０,０,０,０,０,０,０,０,０,０,E2,０,０,０,０}}, //6
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //7
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //8
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //9
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０}}, //0
	{{０,０,田,田,０,０,０,０,田,田,田,田,０,０,０}}, //1
	{{０,田,田,田,田,０,０,田,田,田,田,田,田,０,０}}, //2
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //3
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //4 ほぼ画面外
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapData8{ g_MapAttribData8, 25.0f };
//--------------------------------------------------これで1マップ
//ボスマップ
std::vector<std::vector<int>> g_MapAttribDataG =
{ {
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //0
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //1
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //2
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //3
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //4
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //5
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //6
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //7
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,E2,E2,外,外,外,外,外,外,外,外,外}}, //8
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,E2,E2,外,外,外,外,外,外,外,外,外}}, //9
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //0
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外,外}}, //1
	{{０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,０,外,外,外,外,外,外,外,外}}, //2
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,０,外,外,外,外,外,外,外,外}}, //3
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,０,外,外,外,外,外,外,外,外}}, //4 ほぼ画面外
	{{田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,田,０,外,外,外,外,外,外,外,外}}, //5 画面外(ここまで必要)
} };

MAP_DATA g_MapDataG{ g_MapAttribDataG, 0.0f };
//--------------------------------------------------これで1マップ



//マップをまとめる(ランダム生成の候補)
std::unordered_map<int, MAP_DATA>g_MapDatas;


//=============================================================================
// 初期化処理
//=============================================================================
void InitTile(void)
{
	//背景テクスチャの読み込み
	g_Ground = LoadTexture((char*)"data/TEXTURE/MapChip.png");
	g_Filter = LoadTexture((char*)"data/TEXTURE/Filter.png");

	g_UW = 1.0f / MAP_WIDTH_PATTERN;
	g_VH = 1.0f / MAP_HEIGHT_PATTERN;

	for (size_t i = 0; i < g_MapAttribData2.size(); i++)
	{
		for (size_t j = 0; j < g_MapAttribData2[1].size(); j++)
		{
			if (g_MapAttribData2[i][j] == 0)continue;
			g_MapAttribData2[i][j] += 6;
		}
	}
	
	// 配列を合体させる
	//-------------------------------------------------------マップを追加したらここに記入
	g_MapDatas[0] = g_MapDataS;
	g_MapDatas[1] = g_MapData1;
	g_MapDatas[2] = g_MapData2;
	g_MapDatas[3] = g_MapData3;
	g_MapDatas[4] = g_MapData4;
	g_MapDatas[5] = g_MapData5;
	g_MapDatas[6] = g_MapData6;
	g_MapDatas[7] = g_MapData7;
	g_MapDatas[8] = g_MapData8;
	//-------------------------------------------------------

	std::vector<std::vector<int>> g_MapAttribData;//mapデータを結合したものを入れる
	g_MapAttribData = g_MapDatas[0].mapData;//最初の地形を代入
	for (size_t i = 0; i < MAP_MAX; i++)
	{
		int rate = 0;
		//-------------------------------------------------------ここでマップをランダムに選定
		while (rate == 0)
		{
			//0.0fを入れて無理やり処理
			if (i <= 5)rate = RandomPercent(g_MapData1.rate, g_MapData2.rate, g_MapData3.rate);
			else if (i <= 10)rate = RandomPercent(g_MapData1.rate, g_MapData2.rate, g_MapData3.rate, g_MapData4.rate, 0.0f, 0.0f, g_MapData7.rate, g_MapData8.rate);
			else if (i <= 15)rate = RandomPercent(0.0f, 0.0f, 0.0, g_MapData4.rate, g_MapData5.rate, g_MapData6.rate, g_MapData7.rate, g_MapData8.rate);
		}
		//-------------------------------------------------------
		g_MapAttribData = combineArrays(g_MapAttribData, g_MapDatas[rate].mapData);
	}
	//最終マップ
	g_MapAttribData = combineArrays(g_MapAttribData, g_MapDataG.mapData);

	//マップサイズ取得
	mapInitSizeY = g_MapAttribData.size(); // マップ縦サイズ
	mapInitSizeX = (mapInitSizeY > 0) ? g_MapAttribData[0].size() : 0; // マップ横サイズ（最初の行が空でない場合）

	//ランダムタイル配置
//-------------------------------------------------------タイル増えたらここを変更
	//オーバーフローしないように周りに0を入れる
	for (size_t i = 0; i < mapInitSizeY; i++)
	{
		g_MapAttribData[i].push_back(0); //X末尾追加
		g_MapAttribData[i].insert(g_MapAttribData[i].begin(), 0); //X末尾追加
	}
	
	//Y末尾追加
	g_MapAttribData.push_back(std::vector<int>(mapInitSizeX + 2));

	//Y先頭追加
	g_MapAttribData.insert(g_MapAttribData.begin(), std::vector<int>(mapInitSizeX + 2));

	std::vector<std::vector<int>> g_MapAttribDataCopy = g_MapAttribData;//g_MapAttribDataCopyを参照してg_MapAttribDataを書き換えていく

	int rate = 0;//ランダム

	//周りの情報からタイルの見た目を変更
	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//エンティティを配置
			//プレイヤー
			if (g_MapAttribData[y][x] == P)
			{
				g_MapAttribData[y][x] = 0;
			}
			//エネミー
			if (g_MapAttribData[y][x] == E)
			{
				g_MapAttribData[y][x] = 0;
				Spawner::Instance()->SetEnemy({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) });
			}
			if (g_MapAttribData[y][x] == E2)
			{
				g_MapAttribData[y][x] = 0;
				int texPepper = LoadTexture((char*)"data/TEXTURE/paperenemy.png");
				Spawner::Instance()->SetFor<PepperEnemy>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) }, texPepper, 2.0);
			}
			//木
			if (g_MapAttribData[y][x] == T)
			{
				g_MapAttribData[y][x] = 0;
				int texTree = LoadTexture((char*)"data/TEXTURE/Tree.png");
				//木はでかいので地面に埋まらないよう少し上に配置する
				Spawner::Instance()->SetFor<Tree>({ x * static_cast<float>(MAPCHIP_SIZE), y * static_cast<float>(MAPCHIP_SIZE) - 500.0f}, texTree);
			}
			//城(判定のみ)
			if (g_MapAttribData[y][x] == C)
			{
				g_MapAttribData[y][x] = 0;
				Spawner::Instance()->SetFor<Castle>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) });

			}
			//とげとげ木
			if (g_MapAttribData[y][x] == TT)
			{
				g_MapAttribData[y][x] = 0;
				int texSpikeTree = LoadTexture((char*)"data/TEXTURE/SpikeTree.png");
				//Spawner::Instance()->SetFor<EnemyCastle>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) + 150 }, texSpikeTree);
			}


			switch (g_MapAttribDataCopy[y][x])
			{
			case 1://地面
				if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x - 1] == 0)//地面左端
				{
					g_MapAttribData[y][x] = 1;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x + 1] == 0)//地面右端
				{
					g_MapAttribData[y][x] = 3;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0)//上が空なら地面上
				{
					g_MapAttribData[y][x] = 2;
				}
				else if (g_MapAttribDataCopy[y - 1][x + 1] == 0 && g_MapAttribDataCopy[y][x + 1] == 1)//地面内角右
				{
					g_MapAttribData[y][x] = 8;
				}
				else if (g_MapAttribDataCopy[y - 1][x - 1] == 0 && g_MapAttribDataCopy[y][x - 1] == 1)//地面内角右
				{
					g_MapAttribData[y][x] = 9;
				}
				else//塗りつぶす
				{
					//ランダムで種類を決める
					rate = RandomPercent(40, 15, 40, 5);
					if (rate == 1)g_MapAttribData[y][x] = 4;
					if (rate == 2)g_MapAttribData[y][x] = 5;
					if (rate == 3)g_MapAttribData[y][x] = 6;
					if (rate == 4)g_MapAttribData[y][x] = 7;
				}
				break;

			case 11://地面青
				if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x - 1] == 0)//地面左端
				{
					g_MapAttribData[y][x] = 11;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x + 1] == 0)//地面右端
				{
					g_MapAttribData[y][x] = 13;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0)//上が空なら地面上
				{
					g_MapAttribData[y][x] = 12;
				}
				else if (g_MapAttribDataCopy[y - 1][x + 1] == 0 && g_MapAttribDataCopy[y][x + 1] == 11)//地面内角右
				{
					g_MapAttribData[y][x] = 18;
				}
				else if (g_MapAttribDataCopy[y - 1][x - 1] == 0 && g_MapAttribDataCopy[y][x - 1] == 11)//地面内角右
				{
					g_MapAttribData[y][x] = 19;
				}
				else//塗りつぶす
				{
					//ランダムで種類を決める
					rate = RandomPercent(40, 15, 40, 5);
					if (rate == 1)g_MapAttribData[y][x] = 14;
					if (rate == 2)g_MapAttribData[y][x] = 15;
					if (rate == 3)g_MapAttribData[y][x] = 16;
					if (rate == 4)g_MapAttribData[y][x] = 17;
				}
				break;
				break;
			case 80:

				break;
			default:
				break;
			}



		}
	}

	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//地面であれば草とか生やす
			if (g_MapAttribData[y][x] == 0)
			{
				if (g_MapAttribData[y + 1][x] == 2)//通常地面
				{
					rate = RandomPercent(60, 5, 25, 10);
					if (rate == 1) g_MapAttribData[y][x] = 20;
					if (rate == 2) g_MapAttribData[y][x] = 21;
					if (rate == 3) g_MapAttribData[y][x] = 22;
					if (rate == 4) g_MapAttribData[y][x] = 23;
				}
				if (g_MapAttribData[y + 1][x] == 1 || g_MapAttribData[y + 1][x] == 3)//地面端
				{
					g_MapAttribData[y][x] = 21;
				}
			}
		}
	}

	//-------------------------------------------------------

	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//マップデータ初期化
			TILE_DATA tileData;

			int i = x * (y + 1);
			tileData.attrib = g_MapInfo[g_MapAttribData[y][x]].attrib;
			tileData.initAttrib = tileData.attrib;
			tileData.uv = g_MapInfo[g_MapAttribData[y][x]].uv;
			tileData.XYId = D3DXVECTOR2(x, y);
			tileData.pos.x = x * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);
			tileData.pos.y = y * MAPCHIP_SIZE + (MAPCHIP_SIZE * 0.5);
			tileData.initPos.x = tileData.pos.x;
			tileData.initPos.y = tileData.pos.y;
			tileData.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			tileData.move = D3DXVECTOR2(0.0f, 0.0f);
			tileData.spd = TILE_INIT_SPEED;
			tileData.spawn = g_MapInfo[g_MapAttribData[y][x]].spawn;
			tileData.fadeOut = false;

			g_Map.push_back(tileData);

		}
	}

	g_SpawnTimeCou = 0;
	g_SpawnTime = MAP_SPAWN_TIME;
	g_Wave = 0;
	g_SpawnNum = g_Wave + 1; //一回のスポーン数

	g_MapSize = g_Map.size();

	for (int i = 0; i < g_MapSize; i++)
	{
		//敵スポーン
		if (g_Map[i].spawn == true)
		{
			int ran = RandomPercent(50);
			if (ran == 1)Spawner::Instance()->SetEnemy({ g_Map[i].pos.x, g_Map[i].pos.y - DEFAULT_TILE_SIZE });
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTile(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTile(void)
{
	g_MapSize = g_Map.size();

	g_SpawnTimeCou = Counter(g_SpawnTimeCou, g_SpawnTime);

	for (int i = 0; i < g_MapSize; i++)
	{
		//フェードを下げて消す
		if (g_Map[i].fadeOut)
		{
			g_Map[i].color.a *= 0.95f;

			if (g_Map[i].color.a < 0.01f)
			{
				g_Map[i].fadeOut = false;
				g_Map[i].attrib = MAP_ATTRIB_NONE;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTile(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);//テクスチャのフィルターをOFF

	for (const auto& it : g_Map)
	{
		if (it.attrib != MAP_ATTRIB_NONE)
		{
			DrawSpriteColorRotateCamera
			(
				g_Ground,
				(int)it.pos.x,
				(int)it.pos.y,
				MAPCHIP_SIZE, MAPCHIP_SIZE,	//幅、高さ
				it.uv.x, it.uv.y,			//左上UV座標
				g_UW, g_VH,					//テクスチャ幅、高
				it.color.r, it.color.g, it.color.b, it.color.a,
				0.0f
			);
		}


		/*[デバッグ用]-------------------------------------------*/
		//マップ属性ごとに色分け表示
		//{
		//	switch (it.attrib)
		//	{
		//	case MAP_ATTRIB_STOP:
		//		DrawSpriteColorRotateCamera
		//		(
		//			g_Filter,
		//			it.pos.x, it.pos.y,
		//			MAPCHIP_SIZE, MAPCHIP_SIZE,
		//			0.5f, 0.5f,
		//			1, 1,
		//			0, 0, 1, 0.2f,
		//			0
		//		);

		//	default:
		//		break;
		//	}

		//	if (it.spawn)
		//	{
		//		DrawSpriteColorRotateCamera
		//		(
		//			g_Filter,
		//			it.pos.x, it.pos.y,
		//			MAPCHIP_SIZE, MAPCHIP_SIZE,
		//			0.5f, 0.5f,
		//			1, 1,
		//			1, 0, 1, 0.2f,
		//			0
		//		);
		//	}
		//}
		/*-------------------------------------------------------*/
	}
}

//=============================================================================
// U座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
float GetTileU(int index)
{
	return ((index % MAP_WIDTH_PATTERN) * (1.0f / MAP_WIDTH_PATTERN));
}

//=============================================================================
// V座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
float GetTileV(int index)
{
	return ((index / MAP_WIDTH_PATTERN) * (1.0f / MAP_HEIGHT_PATTERN));
}

//=============================================================================
// UV座標をセット(引数 : 左上端を0その右隣りを1,2,3...としたときの数)
//=============================================================================
D3DXVECTOR2 GetTileUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetTileU(index), GetTileV(index));
	return UV;
}

//=============================================================================
// 座標直下のマップ情報を返す
// ０１２ 
// ３４５
// ６７８ 4が引数の座標
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos)
{
	TILE_DATA* tile = new TILE_DATA[9];

	// 周囲のタイルの位置を計算
	int posX = int(pos.x / MAPCHIP_SIZE);
	int posY = int(pos.y / MAPCHIP_SIZE);

	for (int i = 0; i < 9; i++)
	{
		int offsetX = (i % 3) - 1; // 列（左から中央へのオフセット）
		int offsetY = (i / 3) - 1; // 行（上から中央へのオフセット）

		int checkX = posX + offsetX;
		int checkY = posY + offsetY;

		// 境界チェック（マップの範囲外をチェック）
		if (checkX >= 0 && checkX < g_MapSizeX && checkY >= 0 && checkY < g_MapSizeY)
		{
			int checkXY = checkY * checkX;
			tile[i] = g_Map[checkXY];
		}
		else
		{
			// マップの範囲外の場合、デフォルト値を設定するかエラー処理を行う
			tile[i].attrib = MAP_ATTRIB_ERROR;
			tile[i].pos = D3DXVECTOR2(-1, -1); // マップ外の座標を示す値など
		}
	}

	return tile;
}

//=============================================================================
// 座標直下のマップ情報を返す(ポジション基準)
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	TILE_DATA* tile = new TILE_DATA[9];
	//初期化
	for (size_t i = 0; i < 9; i++)
	{
		tile[i].attrib = MAP_ATTRIB_ERROR;
		tile[i].pos = D3DXVECTOR2(-1, -1); // マップ外の座標を示す値など
	}

	D3DXVECTOR2 sizeH = D3DXVECTOR2(size.x * 0.5f, size.y * 0.5f);

	for (const auto& it : g_Map)
	{
		if (it.color.a < 0.5f) continue;

		if ((it.pos.x < pos.x + size.x && it.pos.x > pos.x - size.x) || (it.pos.y < pos.y + size.y && it.pos.y > pos.y - size.y))
		{
			//横のタイル取得
			//右
			if (CollisionRot(pos.x + sizeH.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[5].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[5].attrib == MAP_ATTRIB_NONE || tile[5].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[5] = it;
				}
			}
			//左
			if (CollisionRot(pos.x - sizeH.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[3].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[3].attrib == MAP_ATTRIB_NONE || tile[3].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[3] = it;
				}
			}
			//下
			if (CollisionRot(pos.x, pos.y + sizeH.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[7].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[7].attrib == MAP_ATTRIB_NONE || tile[7].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[7] = it;
				}
			}
			//上
			if (CollisionRot(pos.x, pos.y - sizeH.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[1].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[1].attrib == MAP_ATTRIB_NONE || tile[1].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[1] = it;
				}
			}
			//中央
			if (CollisionRot(pos.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[4].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[4].attrib == MAP_ATTRIB_NONE || tile[4].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[4] = it;
				}
			}
		}
	}

	return tile;
}

//=============================================================================
// 当たり判定 [戻り値] 1: 上, 3: 左, 5: 右, 7: 下
//=============================================================================
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight)
{
	TILE_DATA* tile = GetMapInfo(pos);
	DIRECTION dir = { false };

	for (int j = 0; j < 9; j++)
	{
		if (tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//横に壁がある場合
			if (CollisionRot(pos.x + hsp, pos.y, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 3) dir.left = true;
				if (j == 5) dir.right = true;
			}

			//縦に壁がある場合
			if (CollisionRot(pos.x, pos.y + vsp, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 1) dir.up = true;
				if (j == 7) dir.down = true;
			}
		}
	}
	delete[] tile;
	return dir;
}

//=============================================================================
// マップのタイル変更 [引数] 1: 元のマップ, 2: 上書きするマップ, 3: 上書きする箇所
//=============================================================================
void ChangeTile(std::vector<std::vector<int>>& map1, std::vector<std::vector<int>> map2, int group)
{
	int startPos = map2[0].size() * (group - 1);

	for (int i = 0; i < map2.size(); i++)
	{
		for (int j = 0; j < map2[0].size(); j++)
		{
			map1[i].insert(map1[i].begin() + j + startPos, map2[i][j]);
		}
	}
}

void CatTile(float minPosX, float maxPosX)
{

	for (size_t i = 0; i < g_MapSize; i++)
	{
		if (g_Map[i].pos.x >= minPosX && g_Map[i].pos.x <= maxPosX)
		{
			g_Map[i].fadeOut = true;
		}
	}
}

std::vector<std::vector<int>> combineArrays(const std::vector<std::vector<int>>& arr1, const std::vector<std::vector<int>>& arr2)
{
	// arr1とarr2を横に結合して新しい配列を作成
	std::vector<std::vector<int>> combinedArray = arr1;

	for (size_t i = 0; i < arr1.size(); ++i)
	{
		combinedArray[i].insert(combinedArray[i].end(), arr2[i].begin(), arr2[i].end());
	}

	return combinedArray;
}

void SetTilePlayer(Player* player)
{
	p_Player = player;
}

D3DXVECTOR2 GetMapSize()
{
	D3DXVECTOR2 mapSize = D3DXVECTOR2(mapInitSizeX * MAPCHIP_SIZE, mapInitSizeY * MAPCHIP_SIZE);
	return mapSize;
}