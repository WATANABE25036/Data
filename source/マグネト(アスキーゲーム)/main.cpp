// =============================================================================
// メイン [main.cpp]
// Author:渡邉 修	Date:2023.1.13
// =============================================================================
#include "main.h"
#include "title.h"
#include "game.h"
#include "result.h"

#include "conioex.h"

// *****************************************************************************
// マクロ定義
// *****************************************************************************
#define		DEBUG_TIMER (500)	// デバッグ表示の間隔 500ms

// *****************************************************************************
// プロトタイプ宣言
// *****************************************************************************
#ifdef _DEBUG
	void DispFPS(void);	// デバッグ時のみ有効な関数
#endif

// *****************************************************************************
// グローバル変数
// *****************************************************************************
int g_fpsCounter;				//  FPSカウンタ
SCENE g_scene;					//  シーン制御用

// =============================================================================
// メイン関数
// =============================================================================
int main(void)
{
	int execLastTime;	// ゲーム処理をした時間（タイマー値）
	int fpsLastTime;	// デバッグ表示をした時間（タイマー値）
	int currentTime;	// 現在の時間（タイマー値）
	int frameCount;		// ゲームの処理をした回数

	setcaption((char*)"マグネト");

	//  タイマー分解能を高精度に設定
	//  1/1000秒ごとに1ずつ増えるタイマーを使える
	timeBeginPeriod(1);

	execLastTime = 
	fpsLastTime = timeGetTime();	// 現在のタイマー値取得

	// 変数を0に初期化
	currentTime =
	frameCount = 0;

	//  カーソル表示ＯＦＦ
	setcursortype(NOCURSOR);

	//初期化
	g_scene = SCENE_TITLE;
	// ==========================
	// この辺で初期化処理を行う
	// ==========================
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitializeTitle();
		break;
	case SCENE_GAME:
		InitializeGame();
		break;
	case SCENE_RESULT:
		InitializeResult();
		break;
	default:
		break;
	}

	//  ここからゲームループ
	do
	{
		currentTime = timeGetTime();	// 現在のタイマー値
		if((currentTime - fpsLastTime) >= DEBUG_TIMER)	// タイマーの差が500ms以上かどうか
		{	// 処理回数と経過時間から1秒間に何回処理できるかを計算
			g_fpsCounter = frameCount * 1000 / (currentTime - fpsLastTime);
			fpsLastTime = currentTime;	// 現在のタイマー値を保存
			frameCount = 0;				// 処理回数リセット
		}

		// 前回ゲーム処理時のタイマー値と現在のタイマー値の差が
		// 1/60秒(17ms)以上になっていたら処理を実行
		if((currentTime - execLastTime) >= (1000 / 60))
		{
			execLastTime = currentTime;// 現在のタイマー値保存

			// 更新処理
			switch (g_scene)
			{
			case SCENE_TITLE:
				UpdateTitle();
				break;
			case SCENE_GAME:
				UpdateGame();
				break;
			case SCENE_RESULT:
				UpdateResult();
				break;
			default:
				break;
			}

			// 描画処理(上書きされるため順番注意)
			switch (g_scene)
			{
			case SCENE_TITLE:
				DrawTitle();
				break;
			case SCENE_GAME:
				DrawGame();
				break;
			case SCENE_RESULT:
				DrawResult();
				break;
			default:
				break;
			}

			frameCount++;// ゲーム処理回数アップ

			//  デバッグ時のみ表示
			#ifdef _DEBUG
				DispFPS();
			#endif
		}
	} while( !inport(PK_ESC) ); // ESC押すまでループ


	// ===============================
	// この辺で後始末処理を行う
	// ===============================
	switch (g_scene)
	{
	case SCENE_TITLE:
		FinalizeTitle();
		break;
	case SCENE_GAME:
		FinalizeGame();
		break;
	case SCENE_RESULT:
		FinalizeResult();
		break;
	default:
		break;
	}

	//  カーソル表示ＯＮ
	setcursortype(NORMALCURSOR);

	//  タイマー分解能を戻す
	timeEndPeriod(1);

	return 0;
}

#ifdef _DEBUG
// =============================================================================
// デバッグ表示
// =============================================================================
void DispFPS(void)
{
	//  色設定
	textattr(0x01);

	gotoxy(1, 1);	// 表示位置設定
	printf("FPS:%d", g_fpsCounter);// FPS値表示

	//  色設定(もとに戻す)
	textcolor(WHITE);

}
#endif

// =============================================================================
// シーン切り替え
// =============================================================================
void SetScene(SCENE scene)
{
	//以前のシーンの終了処理を行う
	switch (g_scene)
	{
	case SCENE_TITLE:
		FinalizeTitle();
		break;
	case SCENE_GAME:
		FinalizeGame();
		break;
	case SCENE_RESULT:
		FinalizeResult();
		break;
	default:
		break;
	}

	//シーンの更新
	g_scene = scene;

	//画面のクリア
	clrscr();

	//更新後のシーンの初期化を行う
	switch (g_scene)
	{
	case SCENE_TITLE:
		InitializeTitle();
		break;
	case SCENE_GAME:
		InitializeGame();
		break;
	case SCENE_RESULT:
		InitializeResult();
		break;
	default:
		break;
	}
}

// =============================================================================
// 現在のシーンをゲット
// =============================================================================
SCENE GetScene(void)
{
	return(g_scene);
}