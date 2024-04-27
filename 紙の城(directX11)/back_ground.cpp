//===================================================
//背景(back_ground.cpp)
//Author:渡邉 修	Date:2023.9.3
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
#include "GameEntity/Player/player.h"
#include "GameEntity/EntityManager.h"
#include "GameEntity/Enemy/KumoBoss.h"

#include <time.h>

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_Tex0_sky;
static int g_Tex1_mountains;

static int g_Tex2_clouds1;
static int g_Tex3_clouds2;
static int g_Tex4_clouds3;
static int g_Tex5_mapGb;

static int g_Tex6_fg_bush;
static int g_Tex7_fg;
static int g_Tex8_tree;
static int g_Tex9_castle;
static int g_Tex10_lightFilter;
static int g_Tex11_Castle;
static int g_Tex12_SpikeTree;
static int g_Tex13_mountains2;
static float g_UW;
static float g_VH;
static float g_AnimeSkipFrameFloat;
static BACK_GROUND g_BackGround[BACK_GROUND_MAX][BACK_GROUND_COPY_MAX];
static TILE_DATA* p_Tile;
static CAMERA* p_Camera;
static Player* p_Player;
static KumoBoss* p_Boss;
static bool g_Reverse;

static D3DXCOLOR g_BackgroundColor;
static float transitionDuration;
static float currentTime;
static float deltaTime;
static double timeCount;
static int g_MapX;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitBackGround(void)
{
	g_Tex0_sky = LoadTexture((char*)"data/TEXTURE/0_sky.png");
	g_Tex1_mountains = LoadTexture((char*)"data/TEXTURE/mountains1.png");


	g_Tex2_clouds1 = LoadTexture((char*)"data/TEXTURE/1_clouds1.png");
	g_Tex3_clouds2 = LoadTexture((char*)"data/TEXTURE/2_clouds2.png");
	g_Tex4_clouds3 = LoadTexture((char*)"data/TEXTURE/3_clouds3.png");
	
	g_Tex5_mapGb = LoadTexture((char*)"data/TEXTURE/mapBg.png");
	g_Tex8_tree = LoadTexture((char*)"data/TEXTURE/Tree.png");
	//g_Tex9_castle = LoadTexture((char*)"data/TEXTURE/shiro.png");
	g_Tex10_lightFilter = LoadTexture((char*)"data/TEXTURE/LightFilter.png");
	g_Tex11_Castle = LoadTexture((char*)"data/TEXTURE/shiro.png");
	g_Tex12_SpikeTree = LoadTexture((char*)"data/TEXTURE/BG_SpikeTree.png");
	g_Tex13_mountains2 = LoadTexture((char*)"data/TEXTURE/mountains2.png");

	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			g_BackGround[i][j].use = false;
			g_BackGround[i][j].pos.x = SCREEN_WIDTH / 2;
			g_BackGround[i][j].pos.y = SCREEN_HEIGHT / 4;
			g_BackGround[i][j].spd.x = BACK_GROUND_SPEED;
			g_BackGround[i][j].spd.y = BACK_GROUND_SPEED;
			//ベクトルの正規化
			D3DXVec2Normalize(&g_BackGround[i][j].spd, &g_BackGround[i][j].spd);
			g_BackGround[i][j].spd *= BACK_GROUND_SPEED;//目的のスピードにするためにスピードを乗算する
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
			g_BackGround[i][j].lighting = false;
			g_BackGround[i][j].object = false;
		}
	}

	//グローバル変数初期化
	g_UW = 1.0f / BACK_GROUND_WIDTH_PATTERN;
	g_VH = 1.0f / BACK_GROUND_HEIGHT_PATTERN;
	g_Reverse = false;
	g_MapX = GetMapSize().x;

	//表示登録(レイヤー重複禁止)
	SetBackGround(g_Tex0_sky,			0);
	SetBackGround(g_Tex2_clouds1,		1, 0.05f, true);
	SetBackGround(g_Tex1_mountains,		2, 0.1f);
	SetBackGround(g_Tex13_mountains2,	3, 0.15f);
	SetBackGround(g_Tex3_clouds2,		4, 0.2f, true);
	SetBackObject(g_Tex11_Castle,		5, D3DXVECTOR2(1000.0f, SCREEN_HEIGHT * 0.5f), 0.5f);
	SetBackGround(g_Tex4_clouds3,		6, 0.5f, true);
	SetBackObject(g_Tex12_SpikeTree,	7, D3DXVECTOR2(g_MapX - 1500, SCREEN_HEIGHT * 0.5f), 1.0f);
	//SetBackGround(g_Tex10_lightFilter,	8, 0.0f, false, LAYER_LOW, true);
	SetBackGround(g_Tex10_lightFilter,	9, 0.0f, false, LAYER_LOW, true);

	/*SetBackGround(g_Tex4_mapGb, 2, 0.0f, false, LAYER_HIGH);*/
	//SetBackGround(g_Tex7_tree, 5, 0.5f, false);
	//SetBackGround(g_Tex9_castle, 5, 0.0f, false);
	transitionDuration = 10.0f;
	currentTime = 0.0f;
	deltaTime = 0.01f;
	timeCount = 1.0f;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateBackGround(void)
{
	p_Camera = GetCamera();
	p_Player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	p_Boss = EntityManager::Instance()->GetEntityWithTag<KumoBoss>("KumoBoss");
	if (p_Player->GetUse())
	{
		float notLoopPos = p_Camera[0].pos.x;
		float oldNotLoopPos = p_Camera[0].oldPos.x;

		for (int i = 0; i < BACK_GROUND_MAX; i++)
		{
			for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
			{
				if (!g_BackGround[i][j].autoScroll)
				{
					//背景の移動
					if (!g_BackGround[i][j].object)
					{
						float spd = (notLoopPos - oldNotLoopPos) * g_BackGround[i][j].moveSp;
						g_BackGround[i][j].pos.x -= spd;
						g_BackGround[i][j].moveCou += spd;
					}
					else
					{
						float spd = (notLoopPos - oldNotLoopPos) * g_BackGround[i][j].moveSp;
						g_BackGround[i][j].pos.x -= spd;
					}
				}
				else
				{
					//オートスクロールの場合
					g_BackGround[i][j].pos.x -= g_BackGround[i][j].moveSp;
					g_BackGround[i][j].moveCou += g_BackGround[i][j].moveSp;
				}

				//カメラの位置によって背景も移動させる
				if (!g_BackGround[i][j].object)
				{
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

				//昼夜フィルター
				if (g_BackGround[i][j].lighting)
				{
					auto tile = p_Player->GetTileData();
					if (tile != nullptr && p_Boss->_sleep)
					{
						if (tile[7].attrib == MAP_ATTRIB_STOP && tile[7].spawn)
						{
							timeCount -= 0.01;
							if (g_BackGround[i][j].color.a < 0.7f)
							{
								g_BackGround[i][j].color.a += 0.01f;
							}
						}
						if(tile[7].attrib == MAP_ATTRIB_STOP && !tile[7].spawn)
						{
							timeCount += 0.01;
							if (g_BackGround[i][j].color.a > 0.05f)
							{
								g_BackGround[i][j].color.a -= 0.01f;
							}
						}
					}
					else if (!p_Boss->_sleep)
					{
						if (p_Boss->GetHp() > 0)
						{
							g_BackGround[i][j].color.a = (p_Boss->GetHp() / p_Boss->GetMaxHp()) / 1;

							if (g_BackGround[i][j].color.a > 0.8)g_BackGround[i][j].color.a = 0.8f;
						}
					}

					if (p_Boss->GetHp() <= 0)
					{
						g_BackGround[i][j].color.a += 0.1f;
						timeCount += 0.05f;
					}

					g_BackGround[i][j].color.r = timeCount;
					g_BackGround[i][j].color.g = timeCount;
					g_BackGround[i][j].color.b = timeCount;

					if (timeCount <= 0.0f)
					{
						timeCount = 0.0f;
					}
					if (timeCount > 1.0f)
					{
						timeCount = 1.0f;
					}
				}

				//単体絵だったら
				if (g_BackGround[i][j].object)break;
			}
		}
	}
	//UpdateBackGroundColor();//昼とか夜のやつ
}

void UpdateBackGroundColor(void)
{
	D3DXCOLOR dayColor(0.75f, 0.55f, 0.69f, 1.0f);
	D3DXCOLOR nightColor(0.98f, 0.84f, 0.63f, 1.0f);

	currentTime += deltaTime;

	float transitionRatio = currentTime / transitionDuration;
	if (currentTime >= transitionDuration)
	{
		currentTime = transitionDuration;
		deltaTime = -deltaTime;
	}

	else if (currentTime <= 0.0f)
	{
		deltaTime = -deltaTime;
	}

	D3DXCOLOR lerpedColor;
	D3DXColorLerp(&lerpedColor, &dayColor, &nightColor, transitionRatio);

	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			g_BackGround[i][j].color = lerpedColor;
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawBackGroundLow(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			if (g_BackGround[i][j].use && g_BackGround[i][j].layerWhole == LAYER_LOW)
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
					g_BackGround[i][j].size.x, 
					g_BackGround[i][j].size.y,	//幅、高さ
					g_BackGround[i][j].uv.x, 
					g_BackGround[i][j].uv.y,		//中心UV座標
					g_UW, g_VH,		//テクスチャ幅、高さ
					g_BackGround[i][j].color.r, g_BackGround[i][j].color.g, g_BackGround[i][j].color.b, g_BackGround[i][j].color.a,
					g_BackGround[i][j].rot
				);

				//単体絵だったら
				if (g_BackGround[i][j].object)break;
			}
		}
	}
}

void DrawBackGroundHigh(void)
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_WRAP);
	for (int i = 0; i < BACK_GROUND_MAX; i++)
	{
		for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
		{
			if (g_BackGround[i][j].use && g_BackGround[i][j].layerWhole == LAYER_HIGH)
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

				//単体絵だったら
				if (g_BackGround[i][j].object)break;
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
void SetBackGround(int texNo, int layer, float moveSp, bool autoScroll, LAYER_WHOLE layerWhole, bool lighting)
{
	p_Camera = GetCamera();
	for (int j = 0; j < BACK_GROUND_COPY_MAX; j++)
	{
		g_BackGround[layer][j].texNo = texNo;
		g_BackGround[layer][j].pos = D3DXVECTOR2(p_Camera[0].pos.x - (BACK_GROUND_WIDTH * 2) + (BACK_GROUND_WIDTH * j), SCREEN_HEIGHT * 0.5f);
		g_BackGround[layer][j].uv = D3DXVECTOR2(0, 0);
		g_BackGround[layer][j].animePattern = 0;
		g_BackGround[layer][j].animeWidthPattern = BACK_GROUND_WIDTH_PATTERN;
		g_BackGround[layer][j].animeBasePattern = 1;
		g_BackGround[layer][j].animeSkipFrame = 0;
		g_BackGround[layer][j].moveSp = moveSp;
		g_BackGround[layer][j].autoScroll = autoScroll;
		g_BackGround[layer][j].layerWhole = layerWhole;
		g_BackGround[layer][j].lighting = lighting;
		g_BackGround[layer][j].object = false;
		g_BackGround[layer][j].use = true;
	}
}

//単体の絵として出す場合
void SetBackObject(int texNo, int layer, D3DXVECTOR2 pos, float moveSp, bool autoScroll, LAYER_WHOLE layerWhole, bool lighting)
{
	g_BackGround[layer][0].texNo = texNo;
	g_BackGround[layer][0].pos = pos;
	g_BackGround[layer][0].uv = D3DXVECTOR2(0, 0);
	g_BackGround[layer][0].animePattern = 0;
	g_BackGround[layer][0].animeWidthPattern = BACK_GROUND_WIDTH_PATTERN;
	g_BackGround[layer][0].animeBasePattern = 1;
	g_BackGround[layer][0].animeSkipFrame = 0;
	g_BackGround[layer][0].moveSp = moveSp;
	g_BackGround[layer][0].autoScroll = autoScroll;
	g_BackGround[layer][0].layerWhole = layerWhole;
	g_BackGround[layer][0].lighting = lighting;
	g_BackGround[layer][0].object = true;
	g_BackGround[layer][0].use = true;
}