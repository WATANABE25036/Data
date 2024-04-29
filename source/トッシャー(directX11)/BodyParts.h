/*==============================================================================

   ペアレント処理 [BodyParts.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
/*
* ペアレント処理サンプル
*/

#include <d3dx9.h>
#include "Renderer.h"
#include "Model.h"
#include "Object.h"

constexpr float VALUE_MOVE() { return 5.0f; }// 移動量

class BodyParts
{
public:
	BodyParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, Object* obj,  bool topParent = false);
	virtual ~BodyParts();

	void Uninit();
	void Update();
	void Draw();

	//ペアレント処理関数
	void Parent(D3DXMATRIX mtx);//mtx : 親・兄弟のワールド行列

	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }
	void SetScl(D3DXVECTOR3 scl) { m_Scl = scl; }
	void SetHitSize(D3DXVECTOR3 hitSize) { m_HitSize = hitSize; }
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_MtxWorld = mtxWorld; }
	void SetChild(BodyParts* bodyParts) { m_pChild = bodyParts; }
	void SetBros(BodyParts* bodyParts) { m_pBros = bodyParts; }
	void SetModel(DX11_MODEL model) { m_Model = model; }
	void SetTopParent(bool topParent) { m_TopParent = topParent; }
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }
	D3DXVECTOR3 GetPos()const { return m_Pos; }
	D3DXVECTOR3 GetRot()const { return m_Rot; }
	D3DXVECTOR3 GetScl()const { return m_Scl; }
	D3DXVECTOR3 GetHitSize()const { return m_HitSize; }
	D3DXMATRIX GetMtxWorld() const { return m_MtxWorld; }
	D3DXVECTOR3 GetMove() const { return m_Move; }
	bool GetTopParent() const { return m_TopParent; }
	DX11_MODEL GetModel()const { return m_Model; }
	D3DXVECTOR3 GetGlobalPos()const;
	
private:
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//表示座標
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//回転角度
	D3DXVECTOR3 m_Scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//大きさ
	D3DXVECTOR3 m_HitSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//当たり判定大きさ
	D3DXVECTOR3 m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量
	D3DXMATRIX m_MtxWorld;//ワールド行列
	BodyParts* m_pChild = nullptr;//子供オブジェクトポインター
	BodyParts* m_pBros = nullptr;//兄弟オブジェクトポインター
	DX11_MODEL m_Model;//モデルデータ
	bool m_TopParent = false;//一番親か
	Object* m_Obj = nullptr;//自分の所持者
};



