//===================================================
//ゲーム画面(game.cpp)
//Auhor:渡邉 修	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "game.h"
#include "wall.h"
#include "barrier.h"
#include "dead.h"
#include "fog.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
static int g_BGM;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitGame()
{
	char bgm[] =
	{
		"data\\BGM\\nc296708.wav"
	};
	g_BGM = LoadSound(&bgm[0]);
	PlaySound(g_BGM, -1);
	InitPlayer();
	InitWall();
	InitBarrier();
	InitDead();
	InitFog();
	InitScore();
	SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
	SetFadeTime(240.0f);//time:何フレームでフェード処理を完了したいか？
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateGame()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//なんか適当な色をセット
		SetFadeTime(30.0f);//time:何フレームでフェード処理を完了したいか？
		SetFade(FADE_STATE_IN);
	}
	UpdatePlayer();
	UpdateWall();
	UpdateBarrier();
	UpdateDead();
	UpdateFog();
	UpdateScore();
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawGame()
{
	//DrawBarrier()は壁で呼び出すため入れない
	//DrawFog()は壁で呼び出すため入れない
	DrawWall();
	//DrawPlayer()は壁で呼び出すため入れない;
	DrawDead();
	DrawScore();
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitGame()
{
	UninitDead();
	UninitBarrier();
	UninitWall();
	UninitPlayer();
	UninitFog();
	UninitScore();
	StopSoundAll();
}
