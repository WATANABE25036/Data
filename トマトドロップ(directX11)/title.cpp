//===================================================
//タイトル画面(title.cpp)
//Auhor:渡邉 修	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "title.h"
#include "title_logo.h"
#include "bg.h"
#include "title_tomato.h"
#include "game_option.h"
#include "cursor.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
unsigned int g_TitleTexture;
static int g_BGM;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitTitle()
{
	char bgm[] =
	{
		"data\\BGM\\nc309629.wav"
	};
	g_BGM = LoadSound(&bgm[0]);
	PlaySound(g_BGM, -1);
	InitBg();
	InitTitleTomato();
	InitTitleLogo();
	InitCursor();
	InitGameOption();
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateTitle()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdateBg();
	UpdateTitleTomato();
	UpdateTitleLogo();
	UpdateCursor();
	UpdateGameOption();
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawTitle()
{
	DrawBg();
	DrawTitleTomato();
	DrawTitleLogo();
	DrawCursor();
	DrawGameOption();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitTitle()
{
	UninitBg();
	UninitTitleTomato();
	UninitTitleLogo();
	UninitCursor();
	UninitGameOption();
	StopSoundAll();
}
