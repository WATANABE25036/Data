/*==============================================================================

   キャラクター(オブジェクト) [ObjCharacter.h]
														 Author : 渡邉 修
														 Date   : 2023/02/14
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "Collision.h"
class Map;

class ObjCharacter : public Object
{
public:
	ObjCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map);
	~ObjCharacter() override;

	void HitJudge();//壁との当たり判定処理
	void WallSlidingMove(D3DXVECTOR3& out, D3DXVECTOR3 normal);
	void RipplesSet(ORDER_TAG tag, int ownerCou);

	bool GetRipplesSE() const { return m_RipplesSE; }

protected:
	Collision m_Collision;
	Map* m_pMap = nullptr;
	D3DXVECTOR3 m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前の表示座標
	D3DXVECTOR2 m_ArrayPos = D3DXVECTOR2(0.0f, 0.0f);			//マップの行列番号
	D3DXVECTOR2 m_OldArrayPos = D3DXVECTOR2(0.0f, 0.0f);		//前のマップの行列番号
	D3DXVECTOR3 m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//スタート時の位置
	D3DXVECTOR3 m_NormaMoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_RipplesRange = 8;			//表示時のばらつき
	int m_RipplesSpan = 18;			//波紋が出る間隔
	int m_RipplesDeleteSpan = 20;	//波紋を何フレーム後に消すか
	int m_RipplesPoint = 0;			//カウンター
	int m_RipplesDeleteCou = 0;		//カウンター
	int m_RipplesDeleteNum = 0;		//波紋の数
	int m_RipplesMax = 5;			//波紋最大数
	bool m_RipplesSE = false;
};

