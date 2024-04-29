/*==============================================================================

   ゲーム処理 [Game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Game.h"
#include "Main.h"
#include "Input.h"
#include "Collision.h"
#include "Sound.h"
#include "Shadow.h"
#include "Polyline.h"
#include "SceneManager.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Game::Game(SceneManager* sceneManager)
	: Scene(sceneManager)
{
}

Game::~Game()
{
}

//=============================================================================
// 初期化
//=============================================================================
void Game::Init(void)
{
	m_GameSystem.Init();

	SetLightEnable(true);

	SetAlphaTestEnable(true);

	m_BGM_Sewer = LoadSound((char*)"data/BGM/Sewer.wav");

	PlaySound(m_BGM_Sewer, -1, 0.2f);//音楽再生

	ShowCursor(false);//マウス未表示
}

//=============================================================================
// 終了処理
//=============================================================================
void Game::Uninit()
{
	StopSoundAll();
	//初期化とは逆順に終了処理を行う
	UninitPolyLine();
	UninitShadow();
	m_GameSystem.Uninit();
	ShowCursor(true);//マウス表示
}

//=============================================================================
// 更新処理
//=============================================================================
void Game::Update(void)
{
	m_GameSystem.Update();

	// 影の更新処理
	UpdateShadow();

	// ポリラインの更新処理
	UpdatePolyLine();

	//カーソルがウィンドウから出ないようにする
	HWND* hWnd = GethWnd();
	if (GetForegroundWindow() == *hWnd)//ウィンドウがアクティブなら実行
	{
		WindowClipCursor();
	}
	m_pSceneManager->SetInventory(m_GameSystem.GetInventory());//インベントリのポインタを渡す

		//リザルト画面へ移行
	if (m_GameSystem.GetPlayer()->GetResultRequest())
	{
		if (m_GameSystem.GetPlayer()->GetComplete())
		{
			m_pSceneManager->SetComplete(true);
		}
		m_pSceneManager->SetScene(SCENE_RESULT);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Game::Draw(void)
{
	m_GameSystem.Draw();

	// ポリラインの描画処理
	DrawPolyLine();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);
}

GameSystem Game::GetGameSystem()
{
	return m_GameSystem;
}
