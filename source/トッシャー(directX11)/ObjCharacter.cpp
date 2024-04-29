/*==============================================================================

   キャラクター(オブジェクト) [ObjCharacter.cpp]
														 Author : 渡邉 修
														 Date   : 2023/02/14
--------------------------------------------------------------------------------

==============================================================================*/
#include "ObjCharacter.h"
#include "Library.h"
#include "Input.h"
#include "Map.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
ObjCharacter::ObjCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map)
	: Object(pos, rot, D3DXVECTOR3(1.0f, 1.0f, 1.0f), gameWorld), m_StartPos(pos), m_pMap(map)
{

}

ObjCharacter::~ObjCharacter()
{

}

//=============================================================================
// 壁との当たり判定処理
//=============================================================================
void ObjCharacter::HitJudge()
{
	//壁との当たり判定
	//周りのタイル情報を取得
	m_ArrayPos = m_pMap->GetArrayPos(m_Pos);//マップの行列での位置
	D3DXVECTOR3 dir(Sign(m_Dir.x), Sign(m_Dir.y), Sign(m_Dir.z));
	AROUND_TILE aroundTile = m_pMap->GetAroundTile(m_Pos);//自分の周りのタイル
	TILE_ATTRIBUTE tileNext = m_pMap->GetTile(m_Pos + m_Move).TileAttribute;//移動先タイル
	D3DXVECTOR2 arrayPosNext = m_pMap->GetArrayPos(m_Pos + m_Move);//マップの行列での移動先位置

	if (!GetKeyboardPress(DIK_V))//当たり判定無視(デバッグ用)
	{
		//斜めにあるタイルには移動できないようにする
		if (
			//斜め合った二辺にタイルがあり斜めのタイルに移動した場合
			((aroundTile.Top.TileAttribute == STOP && aroundTile.Right.TileAttribute == STOP) && (m_ArrayPos.x < arrayPosNext.x) && (m_ArrayPos.y < arrayPosNext.y)) ||
			((aroundTile.Right.TileAttribute == STOP && aroundTile.Under.TileAttribute == STOP) && (m_ArrayPos.x < arrayPosNext.x) && (m_ArrayPos.y > arrayPosNext.y)) ||
			((aroundTile.Under.TileAttribute == STOP && aroundTile.Left.TileAttribute == STOP) && (m_ArrayPos.x > arrayPosNext.x) && (m_ArrayPos.y > arrayPosNext.y)) ||
			((aroundTile.Left.TileAttribute == STOP && aroundTile.Top.TileAttribute == STOP) && (m_ArrayPos.x > arrayPosNext.x) && (m_ArrayPos.y < arrayPosNext.y))
			)
		{
			m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 移動しない
		}

		//上下左右で行き止まりタイルにぶつかったとき
		else if (tileNext == STOP)//移動先が行き止まりだったら
		{
			D3DXVECTOR3 wallNormal;//法線ベクトル

			//周りが行き止まりで行列での位置が変わったら
			if (aroundTile.Top.TileAttribute == STOP && m_ArrayPos.y < arrayPosNext.y)
			{
				wallNormal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);//固定された角度での配置なので一定
				WallSlidingMove(m_Move, wallNormal);//壁摺り移動
			}
			else if (aroundTile.Right.TileAttribute == STOP && m_ArrayPos.x < arrayPosNext.x)
			{
				wallNormal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
				WallSlidingMove(m_Move, wallNormal);
			}
			else if (aroundTile.Under.TileAttribute == STOP && m_ArrayPos.y > arrayPosNext.y)
			{
				wallNormal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				WallSlidingMove(m_Move, wallNormal);
			}
			else if (aroundTile.Left.TileAttribute == STOP && m_ArrayPos.x > arrayPosNext.x)
			{
				wallNormal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				WallSlidingMove(m_Move, wallNormal);
			}

			//まだ行き止まりに行こうとしていたら止める
			tileNext = m_pMap->GetTile(m_Pos + m_Move).TileAttribute;
			if (tileNext == STOP)
			{
				m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
}

//=============================================================================
// 壁摺り移動の移動先にする
//=============================================================================
void ObjCharacter::WallSlidingMove(D3DXVECTOR3& out, D3DXVECTOR3 normal)
{
	float velocityProjection = D3DXVec3Dot(&out, &normal);
	out -= velocityProjection * normal;
}


//=============================================================================
// 波紋をセット
//=============================================================================
void ObjCharacter::RipplesSet(ORDER_TAG tag, int ownerCou)
{
	if (m_RipplesSE == true)m_RipplesSE = false;//波紋の音を切る

	//波紋生成処理
	m_RipplesPoint++;
	if (
		(m_RipplesPoint > m_RipplesSpan && m_Pos != m_OldPos) ||					//動いた時の条件
		(m_Pos == m_OldPos && m_RipplesPoint % 300 == 0 && m_RipplesDeleteNum <= 0)	//動いてない時の条件
		)
	{
		m_pGameWorld->CreateRipples(D3DXVECTOR3(m_OldPos.x + GetRandomInt(-m_RipplesRange, m_RipplesRange), 14.0f, m_OldPos.z + GetRandomInt(-m_RipplesRange, m_RipplesRange)), tag, ownerCou);
		m_RipplesPoint = 0;
		m_RipplesDeleteNum++;//波紋の数をプラス
		m_RipplesSE = true;//効果音を鳴らす
	}

	//波紋削除処理
	if (m_RipplesDeleteNum > 0 && m_RipplesDeleteCou <= 0)
	{
		m_RipplesDeleteCou = m_RipplesDeleteSpan;//カウンターをセット
	}
	if (m_RipplesDeleteNum > 0)//波紋があるもしくは上限以上ある
	{
		m_RipplesDeleteCou--;

		if (m_RipplesDeleteCou <= 0 || m_RipplesDeleteNum > m_RipplesMax)
		{
			m_pGameWorld->DestroyObject(tag, ownerCou);
			m_RipplesDeleteNum--;
		}
	}
}
