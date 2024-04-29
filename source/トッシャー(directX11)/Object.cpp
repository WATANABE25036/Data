/*==============================================================================

   表示物全般(基底) [Object.cpp]
														 Author : 渡邉 修
														 Date   : 2023/12/12
--------------------------------------------------------------------------------

==============================================================================*/
#include "Object.h"
#include "BodyParts.h"
#include "Map.h"
#include "Collision.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Object::Object(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 hitSize, GameWorld* gameWorld)
	: m_Pos(pos), m_Rot(rot), m_HitSize(hitSize), m_pGameWorld(gameWorld)
{
	m_OwnerTag = ORDER_TAG::NONE;
}

Object::~Object()
{

}

//=============================================================================
// 初期化
//=============================================================================
//すべてのオブジェクトで実行
HRESULT Object::InitAll()
{
	if (this == nullptr)return E_POINTER;
	return S_OK;
}

void Object::Init()
{

}

//=============================================================================
// 修了処理
//=============================================================================
void Object::Uninit()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void Object::Update()
{
	if (m_ParentParts != nullptr)
	{
		m_ParentParts->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Object::Draw()
{
	if (m_ParentParts != nullptr)
	{
		//モデル更新
		Collision collision;
		if (collision.CollisionBS(m_Pos, m_pGameWorld->GetPlayer()->GetPos(), 1500.0f, 1.0f))//範囲内だけ表示
		{
			m_ParentParts->Draw();
		}
	}
}

//=============================================================================
// モデル読み込み
//=============================================================================
void Object::ModelLoad()
{
	//モデルの読み込み
	for (auto& it : m_ModelMap)
	{
		DX11_MODEL model;

		if (DoubleCheck((std::string)it.second.ModelAddress, model))//読み込み済みのモデルか確認
		{
			LoadModel(it.second.ModelAddress, &model, (std::string)it.second.ModelAddress);
		}

		it.second.Parts->SetModel(model);

		//一番親のパーツのポインターを取得
		if (it.second.Parts->GetTopParent())
		{
			m_ParentParts = it.second.Parts;
		}

		m_Model = model;
	}
}
