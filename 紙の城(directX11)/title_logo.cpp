//===================================================
//タイトルロゴ(title_logo.cpp)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "title_logo.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int g_TexNo;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static D3DXVECTOR2 g_pos;
static int g_AnimePattern;
static int g_AnimeBasePattern;//アニメーション番号の方向ごとのベース値
static int g_AnimeSkipFrame;
static D3DXCOLOR g_Color;
static float g_AlphaAdd;
static float g_Move;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitTitleLogo(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/TitleLogo.png");

	//グローバル変数初期化
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / TITLE_LOGO_WIDTH_PATTERN;
	g_VH = 1.0f / TITLE_LOGO_HEIGHT_PATTERN;
	g_pos = D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.7f);
	g_AnimePattern = TITLE_LOGO_FRAME_MAX;
	g_AnimeBasePattern = 0;
	g_AnimeSkipFrame = 0;
	g_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	g_AlphaAdd = 0.0f;
	g_Move = 2.0f;//移動速度
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateTitleLogo(void)
{
	//アルファ調整
	g_AlphaAdd += 0.01f;//アルファの速度をここで調整

	if (g_Color.a < 1.0f) g_Color.a += exp(g_AlphaAdd) * 0.0001f;
	else g_Color.a = 1.0f;

	//上移動
	g_Move *= 0.995f;//移動減少量をここで調整
	float RangeY = SCREEN_HEIGHT_HALF * 0.7f;//ロゴの最大高さをここで調整

	if (g_pos.y > RangeY) g_pos.y -= g_Move;
	else g_pos.y = RangeY;

	//UVアニメーション
	//      w             N % 横のパターン数
	g_U = (1.0f / TITLE_LOGO_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % TITLE_LOGO_WIDTH_PATTERN);	//横の座標計算
	//     H              N / 横のパターン数
	g_V = (1.0f / TITLE_LOGO_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / TITLE_LOGO_WIDTH_PATTERN); //縦の座標計算

	//カウンターを整数でやる場合の例1
	g_AnimeSkipFrame++;
	if (g_AnimeSkipFrame > TITLE_LOGO_FRAME_SPAN)
	{
		g_AnimeSkipFrame = 0;
		g_AnimePattern++;

		if (g_AnimePattern > TITLE_LOGO_FRAME_MAX)
		{
			g_AnimePattern = 0;
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawTitleLogo(void)
{
	DrawSpriteColor(g_TexNo,
		g_pos.x,
		g_pos.y,
		TITLE_LOGO_WIDTH, TITLE_LOGO_HEIGHT,	//幅、高さ
		g_U, g_V,		//中心UV座標
		g_UW, g_VH,	//テクスチャ幅、高さ
		g_Color.r, g_Color.g, g_Color.b, g_Color.a//色
	);
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitTitleLogo(void)
{

}




