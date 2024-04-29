/*==============================================================================

   透明なボックス青(派生) [ClearBoxBlue.cpp]
														 Author : 渡邉 修
														 Date   : 2024/02/11
--------------------------------------------------------------------------------

==============================================================================*/
#include "ClearBoxBlue.h"
#include "Collision.h"
#include "GameWorld.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
ClearBoxBlue::ClearBoxBlue(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld)
	: Object(pos, rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), gameWorld)
{
	m_Tag = "ClearBoxBlue";
	m_Scl = (D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	//モデルの設定
	MODEL model = { (char*)"data/MODEL/ClearBoxBlue.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
	m_ModelMap["Parts"] = model;

	//モデルの読み込み
	Object::ModelLoad();
}

ClearBoxBlue::~ClearBoxBlue()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void ClearBoxBlue::Init()
{

}

//=============================================================================
// 終了処理
//=============================================================================
void ClearBoxBlue::Uninit()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void ClearBoxBlue::Update()
{
	//モデル更新
	Object::Update();
}

