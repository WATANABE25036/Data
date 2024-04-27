//===================================================
//マップ範囲選択(range_select.cpp)
//Auhor:渡邉 修	Date:2024.1.20
//===================================================
#include "range_select.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "main.h"
#include "tile.h"
#include "tile.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static int g_SE_landing;
static int g_SE_range_selectHit;
static int g_SE_range_selectDown;
static int g_SE_coinGet;
static int g_SE_hpUp;
static int g_SE_powerUp;
static int g_SE_boxOpen;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//アニメーション番号の方向ごとのベース値
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static RANGE_SELECT g_RangeSelect[RANGE_SELECT_MAX];
static TILE_DATA* p_Tile;
static bool g_Reverse;
static D3DXVECTOR2 g_LastGroundPos;
static int g_DropRevivalTime;
static int g_DropRevivalCou;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitRangeSelect(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Filter.png");

	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		g_RangeSelect[i].use = false;
		g_RangeSelect[i].pos.x = SCREEN_WIDTH / 2;
		g_RangeSelect[i].pos.y = SCREEN_HEIGHT / 4;
		g_RangeSelect[i].spd.x = RANGE_SELECT_SPEED;
		g_RangeSelect[i].spd.y = RANGE_SELECT_SPEED;
		//ベクトルの正規化
		g_RangeSelect[i].spd = D3DXVECTOR2(RANGE_SELECT_SPEED, RANGE_SELECT_SPEED);//目的のスピードにするためにスピードを乗算する
		g_RangeSelect[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		g_RangeSelect[i].size = D3DXVECTOR2(RANGE_SELECT_WIDTH, RANGE_SELECT_HEIGHT);
		g_RangeSelect[i].dir = 0;
	}

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / 1.0f;
	g_VH = 1.0f / 1.0f;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
	g_AnimeSkipFrameFloat = 0;
	g_AnimeBasePattern = 0;
	g_Reverse = false;
	g_LastGroundPos = D3DXVECTOR2(0, 0);
	g_DropRevivalTime = 60;
	g_DropRevivalCou = 0;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateRangeSelect(void)
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (GetKeyboardPress(DIK_P))
		{
			g_RangeSelect[i].pos.x = SCREEN_WIDTH / 2;
			g_RangeSelect[i].pos.y = SCREEN_HEIGHT / 4;


		}

		if (g_RangeSelect[i].use)
		{
			//引き伸ばし
			g_RangeSelect[i].pos.x += g_RangeSelect[i].spd.x * g_RangeSelect[i].dir * 0.5f;
			g_RangeSelect[i].size.x += g_RangeSelect[i].spd.x * abs(g_RangeSelect[i].dir);

		}
		//ボタンを離したとき
		else
		{
			//ボタンを離したとき範囲内を消す
			if (g_RangeSelect[i].size.x > MAPCHIP_SIZE * 1.5f)
			{
				CatTile(g_RangeSelect[i].pos.x - g_RangeSelect[i].size.x * 0.5f, g_RangeSelect[i].pos.x + g_RangeSelect[i].size.x * 0.5f);
				g_RangeSelect[i].size.x = 0.0f;
			}
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawRangeSelect(void)
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (g_RangeSelect[i].use)
		{
			//左上基準
			DrawSpriteColorRotateCamera(g_TexNo,
				(int)g_RangeSelect[i].pos.x,
				(int)g_RangeSelect[i].pos.y,
				g_RangeSelect[i].size.x, g_RangeSelect[i].size.y,	//幅、高さ
				g_U, g_V,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_RangeSelect[i].color.r, g_RangeSelect[i].color.g, g_RangeSelect[i].color.b, g_RangeSelect[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitRangeSelect(void)
{

}

//---------------------------------------------------
// 取得処理
//---------------------------------------------------
RANGE_SELECT* GetRangeSelect()
{
	return &g_RangeSelect[0];
}

//---------------------------------------------------
// 配置(引数 : dir -1か1かで向きを判断)
//---------------------------------------------------
void SetRangeSelect(D3DXVECTOR2 pos, int dir)
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (!g_RangeSelect[i].use)
		{
			g_RangeSelect[i].pos.x = pos.x;
			g_RangeSelect[i].pos.y = pos.y;
			g_RangeSelect[i].spd.x = RANGE_SELECT_SPEED;
			g_RangeSelect[i].spd.y = RANGE_SELECT_SPEED;
			g_RangeSelect[i].spd = D3DXVECTOR2(RANGE_SELECT_SPEED, RANGE_SELECT_SPEED);
			g_RangeSelect[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			g_RangeSelect[i].size = D3DXVECTOR2(1.0f, SCREEN_HEIGHT);
			g_RangeSelect[i].dir = dir;

			g_RangeSelect[i].use = true;
			break;
		}
	}
}

//---------------------------------------------------
// 削除(範囲決定)
//---------------------------------------------------
void DecisionRangeSelect()
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (g_RangeSelect[i].use)
		{
			g_RangeSelect[i].use = false;
		}
	}
}