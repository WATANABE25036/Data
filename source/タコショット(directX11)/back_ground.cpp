//===================================================
//背景(back_ground.cpp)
//Auhor:渡邉 修	Date:2023.9.3
//===================================================
#include "back_ground.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "camera.h"
#include "tile.h"
#include "hit_spark.h"
#include "player.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNoMountain;
static int g_TexNoSky;
static float g_UW;
static float g_VH;
static float g_AnimeSkipFrameFloat;
static BACK_GROUND g_BackGround[BACK_GROUND_MAX][BACK_GROUND_COPY_MAX];
static TILE_DATA* p_Tile;
static CAMERA* p_Camera;
static PLAYER* p_Player;
static bool g_Reverse;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitBackGround(void)
{
	g_TexNoMountain = LoadTexture((char*)"data/TEXTURE/BgMountain.png");
	g_TexNoSky = LoadTexture((char*)"data/TEXTURE/BgSky.png");

	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			g_BackGround[i][j].use = false;
			g_BackGround[i][j].pos.x = SCREEN_WIDTH / 2;
			g_BackGround[i][j].pos.y = SCREEN_HEIGHT / 4;
			g_BackGround[i][j].vel.x = BACK_GROUND_SPEED;
			g_BackGround[i][j].vel.y = BACK_GROUND_SPEED;
			//ベクトルの正規化
			D3DXVec2Normalize(&g_BackGround[i][j].vel, &g_BackGround[i][j].vel);
			g_BackGround[i][j].vel *= BACK_GROUND_SPEED;//目的のスピードにするためにスピードを乗算する
			g_BackGround[i][j].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_BackGround[i][j].size = D3DXVECTOR2(BACK_GROUND_WIDTH, BACK_GROUND_HEIGHT);
			g_BackGround[i][j].rot = 0.0f;
			g_BackGround[i][j].uv = D3DXVECTOR2(0, 0);
			g_BackGround[i][j].animePattern = 0;
			g_BackGround[i][j].animeWidthPattern = BACK_GROUND_WIDTH_PATTERN;
			g_BackGround[i][j].animeBasePattern = 1;
			g_BackGround[i][j].animeSkipFrame = 0;
			g_BackGround[i][j].texNo = 0;
			g_BackGround[i][j].moveSp = 0;
			g_BackGround[i][j].moveCou = 0;
			g_BackGround[i][j].autoScroll = false;
		}
	}

	//グローバル変数初期化
	g_UW = 1.0f / BACK_GROUND_WIDTH_PATTERN;
	g_VH = 1.0f / BACK_GROUND_HEIGHT_PATTERN;
	g_Reverse = false;

	SetBackGround(g_TexNoMountain, 1, 0.05f);
	SetBackGround(g_TexNoSky, 0, 0.05f, true);
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateBackGround(void)
{
	p_Camera = GetCamera();
	p_Player = GetPlayer();

	if (p_Player[0].use)
	{
		float notLoopPos = p_Camera[0].notLoopPos.x;
		float oldNotLoopPos = p_Camera[0].oldNotLoopPos.x;

		for (int i = 0; i < BACK_GROUND_MAX; i++)
		{
			for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
			{
				if (!g_BackGround[i][j].autoScroll)
				{
					//背景の移動
					float vel = (notLoopPos - oldNotLoopPos) * g_BackGround[i][j].moveSp;
					g_BackGround[i][j].pos.x -= vel;
					g_BackGround[i][j].moveCou += vel;
				}
				else
				{
					//オートスクロールの場合
					g_BackGround[i][j].pos.x -= g_BackGround[i][j].moveSp;
					g_BackGround[i][j].moveCou += g_BackGround[i][j].moveSp;
				}

				//カメラの位置によって背景も移動させる
				if (g_BackGround[i][j].moveCou > BACK_GROUND_WIDTH)
				{
					g_BackGround[i][j].pos.x += BACK_GROUND_WIDTH;
					g_BackGround[i][j].moveCou = 0;
				}

				if (g_BackGround[i][j].moveCou < -BACK_GROUND_WIDTH)
				{
					g_BackGround[i][j].pos.x -= BACK_GROUND_WIDTH;
					g_BackGround[i][j].moveCou = 0;
				}
			}
		}
	}

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawBackGround(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			if (g_BackGround[i][j].use)
			{
				//アニメーション
				g_BackGround[i][j].uv = SetAnimation(g_BackGround[i][j].animeBasePattern, g_BackGround[i][j].animePattern, BACK_GROUND_WIDTH_PATTERN, BACK_GROUND_HEIGHT_PATTERN, g_BackGround[i][j].animeWidthPattern, g_Reverse);

				g_BackGround[i][j].animeSkipFrame = Counter(g_BackGround[i][j].animeSkipFrame, BACK_GROUND_FRAME_SPAN);

				if (g_BackGround[i][j].animeSkipFrame == 0)
				{
					g_BackGround[i][j].animePattern = Counter(g_BackGround[i][j].animePattern, BACK_GROUND_FRAME_MAX);
				}

				DrawSpriteColorRotate(g_BackGround[i][j].texNo,
					g_BackGround[i][j].pos.x,
					g_BackGround[i][j].pos.y,
					g_BackGround[i][j].size.x, g_BackGround[i][j].size.y,	//幅、高さ
					g_BackGround[i][j].uv.x, g_BackGround[i][j].uv.y,		//中心UV座標
					g_UW, g_VH,		//テクスチャ幅、高さ
					g_BackGround[i][j].color.r, g_BackGround[i][j].color.g, g_BackGround[i][j].color.b, g_BackGround[i][j].color.a,
					g_BackGround[i][j].rot
				);
			}
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitBackGround(void)
{

}

//---------------------------------------------------
// 背景取得処理
//---------------------------------------------------
BACK_GROUND* GetBackGround()
{
	return &g_BackGround[0][0];
}

//---------------------------------------------------
// 背景配置処理
//---------------------------------------------------
void SetBackGround(int texNo, int layer, float moveSp, bool autoScroll)
{
	p_Camera = GetCamera();
	for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
	{
		g_BackGround[layer][j].texNo = texNo;
		g_BackGround[layer][j].pos = D3DXVECTOR2(p_Camera[0].pos.x - (BACK_GROUND_WIDTH * 2) + (BACK_GROUND_WIDTH * j), SCREEN_HEIGHT * 0.5);
		g_BackGround[layer][j].uv = D3DXVECTOR2(0, 0);
		g_BackGround[layer][j].animePattern = 0;
		g_BackGround[layer][j].animeWidthPattern = BACK_GROUND_WIDTH_PATTERN;
		g_BackGround[layer][j].animeBasePattern = 1;
		g_BackGround[layer][j].animeSkipFrame = 0;
		g_BackGround[layer][j].moveSp = moveSp;
		g_BackGround[layer][j].autoScroll = autoScroll;
		g_BackGround[layer][j].use = true;
	}
}
