//===================================================
//霧(fog.cpp)
//Auhor:渡邉 修	Date:2023.8.7
//===================================================
#include "fog.h"
#include "texture.h"
#include "sprite.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static float g_U;
static float g_V;
static FOG	g_Fog[FOG_MAX];

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitFog(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/barrier.png");

	//グローバル変数初期化
	g_U = FOG_WIDTH * 0.5f;
	g_V = FOG_HEIGHT * 0.5f;

	for (int i = 0; i < FOG_MAX; i++)
	{
		g_Fog[i].color = D3DXCOLOR(0, 0, 0, 0);
		g_Fog[i].pos = D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF);
		g_Fog[i].size = D3DXVECTOR2(FOG_WIDTH, FOG_HEIGHT);
		g_Fog[i].use = false;
	}

	for (int i = 0; i < 3; i++)
	{
		SetFog();
	}
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateFog(void)
{

}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawFog()
{
	for (int i = 0; i < FOG_MAX; i++)
	{
		if (g_Fog[i].use)
		{
			DrawSpriteColor(g_TexNo,
				g_Fog[i].pos.x,
				g_Fog[i].pos.y,
				g_Fog[i].size.x, g_Fog[i].size.y,	//幅、高さ
				g_U, g_V,	//中心UV座標
				1, 1,	//テクスチャ幅、高さ
				g_Fog[i].color.r, g_Fog[i].color.g, g_Fog[i].color.b, g_Fog[i].color.a
			);
			break;
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitFog(void)
{

}

//---------------------------------------------------
// 霧をセット
//---------------------------------------------------
void SetFog()
{
	for (int i = 0; i < FOG_MAX; i++)
	{
		if (!g_Fog[i].use)
		{
			g_Fog[i].color = D3DXCOLOR(0, 0, 0.2f, 0.2f);
			g_Fog[i].pos = D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF);
			g_Fog[i].size = D3DXVECTOR2(FOG_WIDTH, FOG_HEIGHT);
			g_Fog[i].use = true;
			break;
		}
	}
}
