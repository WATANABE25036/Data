/*==============================================================================

   透明なボックス赤(派生) [ClearBoxRed.cpp]
														 Author : 渡邉 修
														 Date   : 2024/02/11
--------------------------------------------------------------------------------

==============================================================================*/
#include "ClearBoxRed.h"
#include "Collision.h"
#include "GameWorld.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
ClearBoxRed::ClearBoxRed(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld)
	: Object(pos, rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), gameWorld)
{
	m_Tag = "ClearBoxRed";
	m_Scl = (D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//モデルの設定
	MODEL model = { (char*)"data/MODEL/ClearBoxRed.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
	m_ModelMap["Parts"] = model;

	//モデルの読み込み
	Object::ModelLoad();
}

ClearBoxRed::~ClearBoxRed()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void ClearBoxRed::Init()
{

}

//=============================================================================
// 終了処理
//=============================================================================
void ClearBoxRed::Uninit()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void ClearBoxRed::Update()
{
	//モデル更新
	Object::Update();
}
