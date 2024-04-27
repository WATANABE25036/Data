//===================================================
//タイトル画面(title.cpp)
//Auhor:渡邉 修	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "title.h"
#include "title_logo.h"
#include "tile.h"
#include "title_background.h"
#include "game_option.h"
#include "cursor.h"
#include "fade.h"
#include "sound.h"

#include "input.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
unsigned int g_TitleTexture;
static int g_Result;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitTitle()
{
	char tilem[] =
	{
		"data\\BGM\\Title.wav"
	};
	g_Result = LoadSound(&tilem[0]);
	//SetVolume(g_Result, 0.3f);//音量
	PlaySound(g_Result, -1, 0.4f);

	InitTitleBackground();
	InitTitleLogo();
	//InitCursor();
	//InitGameOption();
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

	UpdateTitleBackground();
	UpdateTitleLogo();
	//UpdateCursor();
	//UpdateGameOption();

	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_A))
	{
		//指定シーンに移行
		SetFadeColor(1.0f, 1.0f, 1.0f);
		SetFade(FADE_STATE_OUT);//フェードアウト開始リクエスト
		SceneTransition(SCENE_GAME);
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawTitle()
{

	DrawTitleBackground();
	DrawTitleLogo();
	//DrawCursor();
	//DrawGameOption();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitTitle()
{

	UninitTitleBackground();
	UninitTitleLogo();
	//UninitCursor();
	//UninitGameOption();
	StopSoundAll();
}
