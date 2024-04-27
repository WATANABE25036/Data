//===================================================
//リザルト画面(result.cpp)
//Auhor:渡邉 修	Date:2023.8.8
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "result.h"
#include "result_tomato.h"
#include "bg.h"
#include "game_option.h"
#include "cursor.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
unsigned int g_ResultTexture;
static int g_BGM;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitResult()
{
	char bgm[] =
	{
		"data\\BGM\\nc293887.wav"
	};
	g_BGM = LoadSound(&bgm[0]);
	PlaySound(g_BGM, 0);
	InitBg();
	InitResultTomato();
	InitGameOption();
	InitCursor();
	InitScore();

}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateResult()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdateBg();
	UpdateResultTomato();
	UpdateGameOption();
	UpdateCursor();
	UpdateScore();
	
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawResult()
{
	DrawBg();
	DrawResultTomato();
	DrawGameOption();
	DrawCursor();
	DrawScore();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitResult()
{
	UninitBg();
	UninitResultTomato();
	UninitGameOption();
	UninitCursor();
	UninitScore();
	StopSoundAll();
}
