/*==============================================================================

   リザルト画面処理(派生) [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "Input.h"
#include "Texture.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Sound.h"
#include "Score.h"
//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Result::Result(SceneManager* sceneManager)
	: Scene(sceneManager)
{

}

Result::~Result()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void Result::Init(void)
{
	m_TextureNo = LoadTexture((char*)"data/TEXTURE/Result.png");
	m_TextureNoLight = LoadTexture((char*)"data/TEXTURE/Titlelight.png");
	m_TextureNoRetry = LoadTexture((char*)"data/TEXTURE/Retry.png");
	m_TextureNoQuit = LoadTexture((char*)"data/TEXTURE/Quit.png");
	m_TextureNoCursor = LoadTexture((char*)"data/TEXTURE/Cursor.png");
	m_TextureNoCompleteText = LoadTexture((char*)"data/TEXTURE/CompleteText.png");
	m_TextureNoRest = LoadTexture((char*)"data/TEXTURE/Rest.png");

	m_SE_CursorMove = LoadSound((char*)"data/SE/CursorMove.wav");
	m_SE_Decision = LoadSound((char*)"data/SE/Decision.wav");
	m_SE_Result = LoadSound((char*)"data/SE/Result.wav");

	m_SelectX = SCREEN_WIDTH * 0.4f;//はじめるの位置に合わせる
	m_CursorRetry = true;//最初のカーソル

	m_Cou = 0;
	m_Retry = false;
	m_Quit = false;

	m_Score.Init();

	PlaySound(m_SE_Result, 0, 0.2f);
}

//=============================================================================
// 終了処理
//=============================================================================
void Result::Uninit(void)
{
	StopSoundAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void Result::Update(void)
{
	m_LightMove += 0.01f;
	m_LightOffsetX = cos(m_LightMove) * 100;

	m_LeftButton = m_RightButton = m_SelectButton = false;

	if (GetKeyboardTrigger(DIK_LEFT) || GetKeyboardTrigger(DIK_A))
	{
		m_LeftButton = true;
		PlaySound(m_SE_CursorMove, 0, 0.1f);
	}

	if (GetKeyboardTrigger(DIK_RIGHT) || GetKeyboardTrigger(DIK_D))
	{
		m_RightButton = true;
		PlaySound(m_SE_CursorMove, 0, 0.1f);
	}

	if (GetKeyboardTrigger(DIK_E) || GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_RETURN))
	{
		m_SelectButton = true;
		PlaySound(m_SE_Decision, 0, 0.2f);
	}


	if (m_LeftButton)
	{
		m_SelectX = SCREEN_WIDTH * 0.4f;
		m_CursorRetry = true;
		m_CursorQuit = false;
	}
	else if (m_RightButton)
	{
		m_SelectX = SCREEN_WIDTH * 0.6f;
		m_CursorQuit = true;
		m_CursorRetry = false;
	}

	if (m_SelectButton && m_CursorRetry)
	{
		m_Retry = true;
		m_Cou = 45;

	}
	else if (m_SelectButton && m_CursorQuit)
	{
		m_Quit = true;
		m_Cou = 45;

	}

	if (m_Retry || m_Quit)m_Cou--;

	if (m_Retry && m_Cou <= 0)m_pSceneManager->SetScene(SCENE_GAME);
	if (m_Quit && m_Cou <= 0)m_pSceneManager->SetScene(SCENE_TITLE);

	//アイテム情報取得
	m_Inventory = *m_pSceneManager->GetInventory();
}

//=============================================================================
// 描画処理
//=============================================================================
void Result::Draw(void)
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	//背景
	DrawSpriteLeftTop(m_TextureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);

	//光
	DrawSprite(m_TextureNoLight, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 5000 + m_LightOffsetX * 2.0f, 2500 + m_LightOffsetX * 2.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	//カーソル
	DrawSprite(m_TextureNoCursor, m_SelectX, SCREEN_HEIGHT * 0.9f, 96 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	
	//文字
	DrawSprite(m_TextureNoRetry, SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.9f, 64 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	DrawSprite(m_TextureNoQuit, SCREEN_WIDTH * 0.6f, SCREEN_HEIGHT * 0.9f, 48 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);

	//アイテム表示
	m_Inventory.SetPos(D3DXVECTOR2(SCREEN_WIDTH * 0.5f - 450, SCREEN_HEIGHT * 0.3f));
	m_Inventory.Drow();
	//コイン全入手時
	if (m_pSceneManager->GetComplete())
	{
		DrawSprite(m_TextureNoCompleteText, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f, 80 * 3.5f, 49 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		//金貨残り枚数
		if (m_Inventory.GetMaxCoin() != 0)
		{
			//残り
			DrawSprite(m_TextureNoRest, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.1f, 48 * 3.5f, 16 * 3.5f, 1.0f, 1.0f, 1.0f, 1.0f);
			//枚数
			int restCoin = m_Inventory.GetMaxCoin() - (int)m_Inventory.GetItemLest().size();
			m_Score.SetScore(restCoin);
			m_Score.Draw();
		}
	}
}
