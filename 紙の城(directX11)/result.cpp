//===================================================
//リザルト画面(result.cpp)
//Auhor:渡邉 修	Date:2023.8.8
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "result.h"
#include "tile.h"
#include "game_option.h"
#include "cursor.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "result_background.h"

#include "input.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
unsigned int g_ResultTexture;
static int g_Result;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitResult()
{
	char tilem[] =
	{
		"data\\BGM\\Clear.wav"
	};
	g_Result = LoadSound(&tilem[0]);
	PlaySound(g_Result, 0);
	InitResult_background();
	//InitCursor();
	//InitScore();

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
	UpdateResult_background();
	//UpdateCursor();
	//UpdateScore();
	
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_A))
	{
		//指定シーンに移行
		SetFadeColor(1.0f, 1.0f, 1.0f);
		SetFade(FADE_STATE_OUT);//フェードアウト開始リクエスト
		SceneTransition(SCENE_TITLE);
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawResult()
{
	DrawResult_background();
	//DrawCursor();
	//DrawScore();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitResult()
{
	UninitResult_background();
	//UninitCursor();
	//UninitScore();
	StopSoundAll();
}
