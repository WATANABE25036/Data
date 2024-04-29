/*==============================================================================

   シーン管理 [SceneManager.cpp]
														 Author : 渡邉 修
														 Date   : 2023/12/29
--------------------------------------------------------------------------------

==============================================================================*/
#include "SceneManager.h"
#include "Fade.h"
#include "Input.h"


//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
SceneManager::SceneManager()
	: m_Title(this), m_Game(this), m_Result(this)
{
	m_pFade = new Fade();
}

SceneManager::~SceneManager()
{
	delete m_pFade;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT SceneManager::Init(SCENE_INDEX index)
{
	m_SceneIndex = m_SceneNextIndex = index;

	switch (m_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Init();
		break;

	case SCENE_GAME:
		m_Game.Init();
		break;

	case SCENE_RESULT:
		m_Result.Init();
		break;
	}

	HRESULT hr = S_OK;
	hr = m_pFade->Init();
	if (FAILED(hr))	// 初期化が失敗
	{
		DebugPrint("フェード初期化失敗");
		return E_ABORT;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneManager::Uninit()
{
	switch (m_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Uninit();
		break;

	case SCENE_GAME:
		m_Game.Uninit();
		break;

	case SCENE_RESULT:
		m_Result.Uninit();
		break;
	}
	m_pFade->Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneManager::Update()
{
	m_pFade->Update();

	switch( m_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Update();
		break;

	case SCENE_GAME:
		m_Game.Update();
		break;

	case SCENE_RESULT:
		m_Result.Update();
		break;
	}
	
	m_pPlayer = m_Game.GetGameSystem().GetPlayer();

	CheckScene();//シーンが切り替わったか監視
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneManager::Draw()
{
	switch( m_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		m_Title.Draw();
		break;

	case SCENE_GAME:
		m_Game.Draw();
		break;

	case SCENE_RESULT:
		m_Result.Draw();
		break;
	}
	m_pFade->Draw();
}

//=============================================================================
// シーン遷移を要求
//=============================================================================
void SceneManager::SetScene(SCENE_INDEX index)
{
	//遷移先シーンを設定する
	m_SceneNextIndex = index;
}

//=============================================================================
// シーン遷移をゲット
//=============================================================================
SCENE_INDEX SceneManager::GetNextIndex() const
{
	return m_SceneNextIndex;
}

//=============================================================================
// 遷移を要求がある場合にシーンを切り替える
//=============================================================================
void SceneManager::CheckScene()
{
	//現在のシーンと遷移先シーンが違っていたら
	if( m_SceneIndex != m_SceneNextIndex )
	{
		if (m_pFade->GetFadeState() == FADE_OUT_COMP)
		{
			//現在のシーンを終了させる
			Uninit();
			//遷移先シーンの初期化処理を行う
			Init(m_SceneNextIndex);
			m_pFade->FadeIn();
		}
		else
		{
			m_pFade->FadeOut();
		}

	}
}
