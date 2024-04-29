//===================================================
//ƒ^ƒCƒ‹(tile.cpp)
//Auhor:“nç³ C	Date:2023.8.26
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
// ƒOƒ[ƒoƒ‹•Ï”
//*****************************************************************************
static int g_Ground;	//”wŒi—p‚ÌƒeƒNƒXƒ`ƒƒ”Ô†
static int g_Filter;
static float g_UW;
static float g_VH;
static std::vector<TILE_DATA> g_Map; //ƒ}ƒbƒv‚Ìƒf[ƒ^
static int g_SpawnTimeCou;
static int g_SpawnTime;
static int g_SpawnNum;
static int g_Wave;
int g_MapSizeX = 10; // ƒ}ƒbƒv‰¡ƒTƒCƒY
int g_MapSizeY = 0; // ƒ}ƒbƒvcƒTƒCƒY
size_t g_MapSize = 0;
Player* p_Player;
static int mapInitSizeY;
static int mapInitSizeX;

MAP_DATA_T g_MapInfo[MAP_FRAME_MAX] =
{
	//¶ãÀ•W‚Æƒ}ƒbƒvƒ`ƒbƒv‘®«‚Ìİ’è
	//’Êí
	{ GetTileUV(0), MAP_ATTRIB_NONE, false},	//0–³
	{ GetTileUV(1), MAP_ATTRIB_STOP, false},	//1’n–Ê¶
	{ GetTileUV(2), MAP_ATTRIB_STOP, false},	//2’n–Êã
	{ GetTileUV(3), MAP_ATTRIB_STOP, false},	//3’n–Ê‰E
	{ GetTileUV(4), MAP_ATTRIB_STOP, false},	//4“h‚è‚Â‚Ô‚µˆêF
	{ GetTileUV(5), MAP_ATTRIB_STOP, false},	//5“h‚è‚Â‚Ô‚µ(¬‚³‚¢Î)
	{ GetTileUV(6), MAP_ATTRIB_STOP, false},	//6“h‚è‚Â‚Ô‚µ
	{ GetTileUV(7), MAP_ATTRIB_STOP, false},	//7“h‚è‚Â‚Ô‚µ(‘å‚«‚¢Î)
	{ GetTileUV(8), MAP_ATTRIB_STOP, false},	//8“àŠp‰E
	{ GetTileUV(9), MAP_ATTRIB_STOP, false},	//9“àŠp¶
	{ GetTileUV(10), MAP_ATTRIB_STOP, false},	//10–³(’Ê‚è”²‚¯•s‰Â)
	//Â
	{ GetTileUV(13), MAP_ATTRIB_STOP, true},	//11’n–Ê¶
	{ GetTileUV(14), MAP_ATTRIB_STOP, true},	//12’n–Êã
	{ GetTileUV(15), MAP_ATTRIB_STOP, true},	//13’n–Ê‰E
	{ GetTileUV(16), MAP_ATTRIB_STOP, false},	//14“h‚è‚Â‚Ô‚µˆêF
	{ GetTileUV(17), MAP_ATTRIB_STOP, false},	//15“h‚è‚Â‚Ô‚µ(¬‚³‚¢Î)
	{ GetTileUV(18), MAP_ATTRIB_STOP, false},	//16“h‚è‚Â‚Ô‚µ
	{ GetTileUV(19), MAP_ATTRIB_STOP, false},	//17“h‚è‚Â‚Ô‚µ(‘å‚«‚¢Î)
	{ GetTileUV(20), MAP_ATTRIB_STOP, false},	//18“àŠp‰E
	{ GetTileUV(21), MAP_ATTRIB_STOP, false},	//19“àŠp¶

	//©‘R
	{ GetTileUV(24), MAP_ATTRIB_NATURE, false},//20‘
	{ GetTileUV(25), MAP_ATTRIB_NATURE, false},//21‘¬
	{ GetTileUV(26), MAP_ATTRIB_NATURE, false},//22‰Ô‰©F
	{ GetTileUV(27), MAP_ATTRIB_NATURE, false},//23‚µ‚ß‚¶
	//ƒ}ƒbƒvƒ`ƒbƒv‚Ìí—Ş•ªì¬‚·‚é
};

//ƒ}ƒbƒvƒf[ƒ^[(1‰æ–Ê•ª)
const int P = 'P';	// ƒvƒŒƒCƒ„[
const int E = 'E';	// ƒGƒlƒ~[
const int E2 = 'E2';	// ƒGƒlƒ~[
const int T = 'T';	//–ØƒIƒuƒWƒFƒNƒg
const int C = 'C'; //éƒIƒuƒWƒFƒNƒg
const int Œû = 1;	// ’n–Êã
const int “c = 11;	// ’n–Êã
const int ŠO = 10;	// ’n–Êã
const int TT = 'TT';  //‚Æ‚°‚Æ‚°‚Ì–Ø
const int ‚O = 0;


struct MAP_DATA
{
	std::vector<std::vector<int>> mapData;
	float rate;
};

//ŠeX‚Ì‘®«‚ğ“ü‚ê‚é
// 
//--------------------------------------------------
//‰Šúƒ}ƒbƒv
std::vector<std::vector<int>> g_MapAttribDataS =
{ {
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{ŠO,ŠO,ŠO,ŠO,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{ŠO,ŠO,ŠO,ŠO,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //3
	{{ŠO,ŠO,ŠO,ŠO,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{ŠO,ŠO,ŠO,ŠO,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapDataS{ g_MapAttribDataS, 0.0f };//”roŠm—¦
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv


//--------------------------------------------------
std::vector<std::vector<int>> g_MapAttribData1 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{‚O,‚O,‚O,‚O,‚O, T,‚O,‚O, E,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //2
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //3
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData1{ g_MapAttribData1, 35.0f };//”roŠm—¦
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv

std::vector<std::vector<int>> g_MapAttribData2 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O, E, E,‚O,‚O,‚O, E}}, //7
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,Œû,Œû,Œû,Œû,‚O,‚O,‚O}}, //1
	{{‚O,‚O,Œû,Œû,Œû,Œû,Œû,Œû,Œû,‚O}}, //2
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //3
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData2{ g_MapAttribData2, 35.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv

std::vector<std::vector<int>> g_MapAttribData3 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{‚O,‚O,‚O, T,‚O,‚O,‚O,‚O,‚O, T}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{Œû,Œû,‚O,‚O,‚O,Œû,Œû,Œû,‚O,‚O}}, //2
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //3
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû,Œû}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData3{ g_MapAttribData3, 35.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv

std::vector<std::vector<int>> g_MapAttribData4 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,E2,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //3
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData4{ g_MapAttribData4, 25.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv

std::vector<std::vector<int>> g_MapAttribData5 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O, T,‚O}}, //7
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,“c,“c,‚O,E2,‚O,‚O,‚O,‚O}}, //0
	{{‚O,“c,“c,“c,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{“c,“c,“c,“c,‚O,‚O,‚O,“c,“c,“c}}, //2
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //3
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData5{ g_MapAttribData5, 25.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv

std::vector<std::vector<int>> g_MapAttribData6 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O, T,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O}}, //1
	{{‚O,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //2
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //3
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData6{ g_MapAttribData6, 25.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv
// 
std::vector<std::vector<int>> g_MapAttribData7 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,E2,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,E2,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{‚O,‚O,‚O,‚O,E2,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,‚O,‚O,“c,“c,“c,“c,“c,“c,“c,“c,‚O,‚O}}, //0
	{{‚O,‚O,‚O,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O,‚O}}, //1
	{{‚O,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O,‚O}}, //2
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //3
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData7{ g_MapAttribData7, 25.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv
// 
std::vector<std::vector<int>> g_MapAttribData8 =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,E2,‚O,‚O,‚O,‚O}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //7
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //9
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O}}, //0
	{{‚O,‚O,“c,“c,‚O,‚O,‚O,‚O,“c,“c,“c,“c,‚O,‚O,‚O}}, //1
	{{‚O,“c,“c,“c,“c,‚O,‚O,“c,“c,“c,“c,“c,“c,‚O,‚O}}, //2
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //3
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapData8{ g_MapAttribData8, 25.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv
//ƒ{ƒXƒ}ƒbƒv
std::vector<std::vector<int>> g_MapAttribDataG =
{ {
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //2
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //3
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //4
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //5
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //6
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //7
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,E2,E2,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //8
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,E2,E2,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //9
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //0
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //1
	{{‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //2
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //3
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //4 ‚Ù‚Ú‰æ–ÊŠO
	{{“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,“c,‚O,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO,ŠO}}, //5 ‰æ–ÊŠO(‚±‚±‚Ü‚Å•K—v)
} };

MAP_DATA g_MapDataG{ g_MapAttribDataG, 0.0f };
//--------------------------------------------------‚±‚ê‚Å1ƒ}ƒbƒv



//ƒ}ƒbƒv‚ğ‚Ü‚Æ‚ß‚é(ƒ‰ƒ“ƒ_ƒ€¶¬‚ÌŒó•â)
std::unordered_map<int, MAP_DATA>g_MapDatas;


//=============================================================================
// ‰Šú‰»ˆ—
//=============================================================================
void InitTile(void)
{
	//”wŒiƒeƒNƒXƒ`ƒƒ‚Ì“Ç‚İ‚İ
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
	
	// ”z—ñ‚ğ‡‘Ì‚³‚¹‚é
	//-------------------------------------------------------ƒ}ƒbƒv‚ğ’Ç‰Á‚µ‚½‚ç‚±‚±‚É‹L“ü
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

	std::vector<std::vector<int>> g_MapAttribData;//mapƒf[ƒ^‚ğŒ‹‡‚µ‚½‚à‚Ì‚ğ“ü‚ê‚é
	g_MapAttribData = g_MapDatas[0].mapData;//Å‰‚Ì’nŒ`‚ğ‘ã“ü
	for (size_t i = 0; i < MAP_MAX; i++)
	{
		int rate = 0;
		//-------------------------------------------------------‚±‚±‚Åƒ}ƒbƒv‚ğƒ‰ƒ“ƒ_ƒ€‚É‘I’è
		while (rate == 0)
		{
			//0.0f‚ğ“ü‚ê‚Ä–³—‚â‚èˆ—
			if (i <= 5)rate = RandomPercent(g_MapData1.rate, g_MapData2.rate, g_MapData3.rate);
			else if (i <= 10)rate = RandomPercent(g_MapData1.rate, g_MapData2.rate, g_MapData3.rate, g_MapData4.rate, 0.0f, 0.0f, g_MapData7.rate, g_MapData8.rate);
			else if (i <= 15)rate = RandomPercent(0.0f, 0.0f, 0.0, g_MapData4.rate, g_MapData5.rate, g_MapData6.rate, g_MapData7.rate, g_MapData8.rate);
		}
		//-------------------------------------------------------
		g_MapAttribData = combineArrays(g_MapAttribData, g_MapDatas[rate].mapData);
	}
	//ÅIƒ}ƒbƒv
	g_MapAttribData = combineArrays(g_MapAttribData, g_MapDataG.mapData);

	//ƒ}ƒbƒvƒTƒCƒYæ“¾
	mapInitSizeY = g_MapAttribData.size(); // ƒ}ƒbƒvcƒTƒCƒY
	mapInitSizeX = (mapInitSizeY > 0) ? g_MapAttribData[0].size() : 0; // ƒ}ƒbƒv‰¡ƒTƒCƒYiÅ‰‚Ìs‚ª‹ó‚Å‚È‚¢ê‡j

	//ƒ‰ƒ“ƒ_ƒ€ƒ^ƒCƒ‹”z’u
//-------------------------------------------------------ƒ^ƒCƒ‹‘‚¦‚½‚ç‚±‚±‚ğ•ÏX
	//ƒI[ƒo[ƒtƒ[‚µ‚È‚¢‚æ‚¤‚Éü‚è‚É0‚ğ“ü‚ê‚é
	for (size_t i = 0; i < mapInitSizeY; i++)
	{
		g_MapAttribData[i].push_back(0); //X––”ö’Ç‰Á
		g_MapAttribData[i].insert(g_MapAttribData[i].begin(), 0); //X––”ö’Ç‰Á
	}
	
	//Y––”ö’Ç‰Á
	g_MapAttribData.push_back(std::vector<int>(mapInitSizeX + 2));

	//Yæ“ª’Ç‰Á
	g_MapAttribData.insert(g_MapAttribData.begin(), std::vector<int>(mapInitSizeX + 2));

	std::vector<std::vector<int>> g_MapAttribDataCopy = g_MapAttribData;//g_MapAttribDataCopy‚ğQÆ‚µ‚Äg_MapAttribData‚ğ‘‚«Š·‚¦‚Ä‚¢‚­

	int rate = 0;//ƒ‰ƒ“ƒ_ƒ€

	//ü‚è‚Ìî•ñ‚©‚çƒ^ƒCƒ‹‚ÌŒ©‚½–Ú‚ğ•ÏX
	for (int y = 1; y < mapInitSizeY; y++)
	{
		for (int x = 1; x < mapInitSizeX; x++)
		{
			//ƒGƒ“ƒeƒBƒeƒB‚ğ”z’u
			//ƒvƒŒƒCƒ„[
			if (g_MapAttribData[y][x] == P)
			{
				g_MapAttribData[y][x] = 0;
			}
			//ƒGƒlƒ~[
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
			//–Ø
			if (g_MapAttribData[y][x] == T)
			{
				g_MapAttribData[y][x] = 0;
				int texTree = LoadTexture((char*)"data/TEXTURE/Tree.png");
				//–Ø‚Í‚Å‚©‚¢‚Ì‚Å’n–Ê‚É–„‚Ü‚ç‚È‚¢‚æ‚¤­‚µã‚É”z’u‚·‚é
				Spawner::Instance()->SetFor<Tree>({ x * static_cast<float>(MAPCHIP_SIZE), y * static_cast<float>(MAPCHIP_SIZE) - 500.0f}, texTree);
			}
			//é(”»’è‚Ì‚İ)
			if (g_MapAttribData[y][x] == C)
			{
				g_MapAttribData[y][x] = 0;
				Spawner::Instance()->SetFor<Castle>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) });

			}
			//‚Æ‚°‚Æ‚°–Ø
			if (g_MapAttribData[y][x] == TT)
			{
				g_MapAttribData[y][x] = 0;
				int texSpikeTree = LoadTexture((char*)"data/TEXTURE/SpikeTree.png");
				//Spawner::Instance()->SetFor<EnemyCastle>({ x * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5), y * static_cast<float>(MAPCHIP_SIZE) + static_cast<float>(MAPCHIP_SIZE * 0.5) + 150 }, texSpikeTree);
			}


			switch (g_MapAttribDataCopy[y][x])
			{
			case 1://’n–Ê
				if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x - 1] == 0)//’n–Ê¶’[
				{
					g_MapAttribData[y][x] = 1;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x + 1] == 0)//’n–Ê‰E’[
				{
					g_MapAttribData[y][x] = 3;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0)//ã‚ª‹ó‚È‚ç’n–Êã
				{
					g_MapAttribData[y][x] = 2;
				}
				else if (g_MapAttribDataCopy[y - 1][x + 1] == 0 && g_MapAttribDataCopy[y][x + 1] == 1)//’n–Ê“àŠp‰E
				{
					g_MapAttribData[y][x] = 8;
				}
				else if (g_MapAttribDataCopy[y - 1][x - 1] == 0 && g_MapAttribDataCopy[y][x - 1] == 1)//’n–Ê“àŠp‰E
				{
					g_MapAttribData[y][x] = 9;
				}
				else//“h‚è‚Â‚Ô‚·
				{
					//ƒ‰ƒ“ƒ_ƒ€‚Åí—Ş‚ğŒˆ‚ß‚é
					rate = RandomPercent(40, 15, 40, 5);
					if (rate == 1)g_MapAttribData[y][x] = 4;
					if (rate == 2)g_MapAttribData[y][x] = 5;
					if (rate == 3)g_MapAttribData[y][x] = 6;
					if (rate == 4)g_MapAttribData[y][x] = 7;
				}
				break;

			case 11://’n–ÊÂ
				if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x - 1] == 0)//’n–Ê¶’[
				{
					g_MapAttribData[y][x] = 11;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0 && g_MapAttribDataCopy[y][x + 1] == 0)//’n–Ê‰E’[
				{
					g_MapAttribData[y][x] = 13;
				}
				else if (g_MapAttribDataCopy[y - 1][x] == 0)//ã‚ª‹ó‚È‚ç’n–Êã
				{
					g_MapAttribData[y][x] = 12;
				}
				else if (g_MapAttribDataCopy[y - 1][x + 1] == 0 && g_MapAttribDataCopy[y][x + 1] == 11)//’n–Ê“àŠp‰E
				{
					g_MapAttribData[y][x] = 18;
				}
				else if (g_MapAttribDataCopy[y - 1][x - 1] == 0 && g_MapAttribDataCopy[y][x - 1] == 11)//’n–Ê“àŠp‰E
				{
					g_MapAttribData[y][x] = 19;
				}
				else//“h‚è‚Â‚Ô‚·
				{
					//ƒ‰ƒ“ƒ_ƒ€‚Åí—Ş‚ğŒˆ‚ß‚é
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
			//’n–Ê‚Å‚ ‚ê‚Î‘‚Æ‚©¶‚â‚·
			if (g_MapAttribData[y][x] == 0)
			{
				if (g_MapAttribData[y + 1][x] == 2)//’Êí’n–Ê
				{
					rate = RandomPercent(60, 5, 25, 10);
					if (rate == 1) g_MapAttribData[y][x] = 20;
					if (rate == 2) g_MapAttribData[y][x] = 21;
					if (rate == 3) g_MapAttribData[y][x] = 22;
					if (rate == 4) g_MapAttribData[y][x] = 23;
				}
				if (g_MapAttribData[y + 1][x] == 1 || g_MapAttribData[y + 1][x] == 3)//’n–Ê’[
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
			//ƒ}ƒbƒvƒf[ƒ^‰Šú‰»
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
	g_SpawnNum = g_Wave + 1; //ˆê‰ñ‚ÌƒXƒ|[ƒ“”

	g_MapSize = g_Map.size();

	for (int i = 0; i < g_MapSize; i++)
	{
		//“GƒXƒ|[ƒ“
		if (g_Map[i].spawn == true)
		{
			int ran = RandomPercent(50);
			if (ran == 1)Spawner::Instance()->SetEnemy({ g_Map[i].pos.x, g_Map[i].pos.y - DEFAULT_TILE_SIZE });
		}
	}
}

//=============================================================================
// I—¹ˆ—
//=============================================================================
void UninitTile(void)
{

}

//=============================================================================
// XVˆ—
//=============================================================================
void UpdateTile(void)
{
	g_MapSize = g_Map.size();

	g_SpawnTimeCou = Counter(g_SpawnTimeCou, g_SpawnTime);

	for (int i = 0; i < g_MapSize; i++)
	{
		//ƒtƒF[ƒh‚ğ‰º‚°‚ÄÁ‚·
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
// •`‰æˆ—
//=============================================================================
void DrawTile(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);//ƒeƒNƒXƒ`ƒƒ‚ÌƒtƒBƒ‹ƒ^[‚ğOFF

	for (const auto& it : g_Map)
	{
		if (it.attrib != MAP_ATTRIB_NONE)
		{
			DrawSpriteColorRotateCamera
			(
				g_Ground,
				(int)it.pos.x,
				(int)it.pos.y,
				MAPCHIP_SIZE, MAPCHIP_SIZE,	//•A‚‚³
				it.uv.x, it.uv.y,			//¶ãUVÀ•W
				g_UW, g_VH,					//ƒeƒNƒXƒ`ƒƒ•A‚
				it.color.r, it.color.g, it.color.b, it.color.a,
				0.0f
			);
		}


		/*[ƒfƒoƒbƒO—p]-------------------------------------------*/
		//ƒ}ƒbƒv‘®«‚²‚Æ‚ÉF•ª‚¯•\¦
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
// UÀ•W‚ğƒZƒbƒg(ˆø” : ¶ã’[‚ğ0‚»‚Ì‰E—×‚è‚ğ1,2,3...‚Æ‚µ‚½‚Æ‚«‚Ì”)
//=============================================================================
float GetTileU(int index)
{
	return ((index % MAP_WIDTH_PATTERN) * (1.0f / MAP_WIDTH_PATTERN));
}

//=============================================================================
// VÀ•W‚ğƒZƒbƒg(ˆø” : ¶ã’[‚ğ0‚»‚Ì‰E—×‚è‚ğ1,2,3...‚Æ‚µ‚½‚Æ‚«‚Ì”)
//=============================================================================
float GetTileV(int index)
{
	return ((index / MAP_WIDTH_PATTERN) * (1.0f / MAP_HEIGHT_PATTERN));
}

//=============================================================================
// UVÀ•W‚ğƒZƒbƒg(ˆø” : ¶ã’[‚ğ0‚»‚Ì‰E—×‚è‚ğ1,2,3...‚Æ‚µ‚½‚Æ‚«‚Ì”)
//=============================================================================
D3DXVECTOR2 GetTileUV(int index)
{
	D3DXVECTOR2 UV = D3DXVECTOR2(GetTileU(index), GetTileV(index));
	return UV;
}

//=============================================================================
// À•W’¼‰º‚Ìƒ}ƒbƒvî•ñ‚ğ•Ô‚·
// ‚O‚P‚Q 
// ‚R‚S‚T
// ‚U‚V‚W 4‚ªˆø”‚ÌÀ•W
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos)
{
	TILE_DATA* tile = new TILE_DATA[9];

	// üˆÍ‚Ìƒ^ƒCƒ‹‚ÌˆÊ’u‚ğŒvZ
	int posX = int(pos.x / MAPCHIP_SIZE);
	int posY = int(pos.y / MAPCHIP_SIZE);

	for (int i = 0; i < 9; i++)
	{
		int offsetX = (i % 3) - 1; // —ñi¶‚©‚ç’†‰›‚Ö‚ÌƒIƒtƒZƒbƒgj
		int offsetY = (i / 3) - 1; // siã‚©‚ç’†‰›‚Ö‚ÌƒIƒtƒZƒbƒgj

		int checkX = posX + offsetX;
		int checkY = posY + offsetY;

		// ‹«ŠEƒ`ƒFƒbƒNiƒ}ƒbƒv‚Ì”ÍˆÍŠO‚ğƒ`ƒFƒbƒNj
		if (checkX >= 0 && checkX < g_MapSizeX && checkY >= 0 && checkY < g_MapSizeY)
		{
			int checkXY = checkY * checkX;
			tile[i] = g_Map[checkXY];
		}
		else
		{
			// ƒ}ƒbƒv‚Ì”ÍˆÍŠO‚Ìê‡AƒfƒtƒHƒ‹ƒg’l‚ğİ’è‚·‚é‚©ƒGƒ‰[ˆ—‚ğs‚¤
			tile[i].attrib = MAP_ATTRIB_ERROR;
			tile[i].pos = D3DXVECTOR2(-1, -1); // ƒ}ƒbƒvŠO‚ÌÀ•W‚ğ¦‚·’l‚È‚Ç
		}
	}

	return tile;
}

//=============================================================================
// À•W’¼‰º‚Ìƒ}ƒbƒvî•ñ‚ğ•Ô‚·(ƒ|ƒWƒVƒ‡ƒ“Šî€)
//=============================================================================
TILE_DATA* GetMapInfo(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	TILE_DATA* tile = new TILE_DATA[9];
	//‰Šú‰»
	for (size_t i = 0; i < 9; i++)
	{
		tile[i].attrib = MAP_ATTRIB_ERROR;
		tile[i].pos = D3DXVECTOR2(-1, -1); // ƒ}ƒbƒvŠO‚ÌÀ•W‚ğ¦‚·’l‚È‚Ç
	}

	D3DXVECTOR2 sizeH = D3DXVECTOR2(size.x * 0.5f, size.y * 0.5f);

	for (const auto& it : g_Map)
	{
		if (it.color.a < 0.5f) continue;

		if ((it.pos.x < pos.x + size.x && it.pos.x > pos.x - size.x) || (it.pos.y < pos.y + size.y && it.pos.y > pos.y - size.y))
		{
			//‰¡‚Ìƒ^ƒCƒ‹æ“¾
			//‰E
			if (CollisionRot(pos.x + sizeH.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[5].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[5].attrib == MAP_ATTRIB_NONE || tile[5].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[5] = it;
				}
			}
			//¶
			if (CollisionRot(pos.x - sizeH.x, pos.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[3].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[3].attrib == MAP_ATTRIB_NONE || tile[3].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[3] = it;
				}
			}
			//‰º
			if (CollisionRot(pos.x, pos.y + sizeH.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[7].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[7].attrib == MAP_ATTRIB_NONE || tile[7].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[7] = it;
				}
			}
			//ã
			if (CollisionRot(pos.x, pos.y - sizeH.y, it.pos.x, it.pos.y, size.x, size.y, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (tile[1].attrib == MAP_ATTRIB_ERROR || (it.attrib != MAP_ATTRIB_NONE && (tile[1].attrib == MAP_ATTRIB_NONE || tile[1].attrib == MAP_ATTRIB_NATURE)))
				{
					tile[1] = it;
				}
			}
			//’†‰›
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
// “–‚½‚è”»’è [–ß‚è’l] 1: ã, 3: ¶, 5: ‰E, 7: ‰º
//=============================================================================
DIRECTION TileHit(D3DXVECTOR2 pos, float hsp, float vsp, float hitBoxWidth, float hitBoxHeight)
{
	TILE_DATA* tile = GetMapInfo(pos);
	DIRECTION dir = { false };

	for (int j = 0; j < 9; j++)
	{
		if (tile[j].attrib == MAP_ATTRIB_STOP)
		{
			//‰¡‚É•Ç‚ª‚ ‚éê‡
			if (CollisionRot(pos.x + hsp, pos.y, tile[j].pos.x, tile[j].pos.y, hitBoxWidth, hitBoxHeight, MAPCHIP_SIZE, MAPCHIP_SIZE, 0.0f))
			{
				if (j == 3) dir.left = true;
				if (j == 5) dir.right = true;
			}

			//c‚É•Ç‚ª‚ ‚éê‡
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
// ƒ}ƒbƒv‚Ìƒ^ƒCƒ‹•ÏX [ˆø”] 1: Œ³‚Ìƒ}ƒbƒv, 2: ã‘‚«‚·‚éƒ}ƒbƒv, 3: ã‘‚«‚·‚é‰ÓŠ
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
	// arr1‚Æarr2‚ğ‰¡‚ÉŒ‹‡‚µ‚ÄV‚µ‚¢”z—ñ‚ğì¬
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