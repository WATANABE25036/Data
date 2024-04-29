/*==============================================================================

   ペアレント処理 [BodyParts.cpp]
														 Author : 学校配布、渡邉 修
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#include "BodyParts.h"
#include "Input.h"
#include "Polyline.h"
#include "Renderer.h"

BodyParts::BodyParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, Object* obj, bool topParent)
	: m_Pos(pos), m_Rot(rot), m_Scl(scl), m_TopParent(topParent), m_Obj(obj)
{

}

BodyParts::~BodyParts()
{
	//objモデルの解放
	UnloadModel(&m_Model);
}

void BodyParts::Uninit()
{

}

void BodyParts::Update()
{
	//親だけ更新
	if (m_TopParent)
	{
		//オブジェクトクラスと一番親パーツの値を同じにする
		m_Pos = m_Obj->GetPos();
		m_Rot = m_Obj->GetRot();
	}
}

void BodyParts::Draw()
{
		//ライティングOFF
		//SetLightEnable(FALSE);

		D3DXMATRIX RootMatrix;
		D3DXMatrixIdentity(&RootMatrix); //ルート行列(単位行列)

		//ペアレントモデルの描画
		Parent(RootMatrix);//一番親モデルの親ワールド行列は単位行列にしておく

		//ライティングON
		//SetLightEnable(TRUE);
}

void BodyParts::Parent(D3DXMATRIX mtx)
{
	//自分のワールド行列を作成する
	D3DXMATRIX mtxScl, mtxRot, mtxTranslation;

	//ワールド行列を単位行列で初期化
	D3DXMatrixIdentity(&m_MtxWorld);

	//スケーリング行列作成
	D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);

	//回転移動行列作成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.x, m_Rot.y, m_Rot.z);

	//平行移動行列作成
	D3DXMatrixTranslation(&mtxTranslation, m_Pos.x, m_Pos.y, m_Pos.z);

	//ワールド行列の作成
	m_MtxWorld *= mtxScl;
	m_MtxWorld *= mtxRot;
	m_MtxWorld *= mtxTranslation;

	m_MtxWorld = m_MtxWorld * mtx;

	if (m_pChild)//子がいるか?
	{
		m_pChild->Parent(m_MtxWorld);//自分のワールド行列を渡して子供を処理
	}
	if (m_pBros)//兄弟がいるか?
	{
		m_pBros->Parent(mtx);//自分の親のワールド行列を渡して兄弟を処理
	}

	//行列のセット
	SetWorldMatrix(&m_MtxWorld);

	//モデルを描画する
	DrawModel(m_Model);
}

D3DXVECTOR3 BodyParts::GetGlobalPos() const
{
	if (m_TopParent)return m_Obj->GetPos();//一番親の場合自分が原点
	D3DXVECTOR3 globalPos = D3DXVECTOR3(m_MtxWorld._41, m_MtxWorld._42, m_MtxWorld._43);
	return globalPos;
}

