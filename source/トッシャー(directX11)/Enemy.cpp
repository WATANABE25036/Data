/*==============================================================================

   エネミー(派生) [Enemy.cpp]
														 Author : 渡邉 修
														 Date   : 2024/01/11
--------------------------------------------------------------------------------

==============================================================================*/
#include "Enemy.h"
#include "Shadow.h"
#include "Library.h"
#include "GameWorld.h"
#include "Map.h"

// 静的メンバ変数の定義
int Enemy::m_sCou = 0;

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Enemy::Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map)
	: ObjCharacter(pos, rot, gameWorld, map)
{
	m_sCou++;
	m_OwnerNum = m_sCou;
	m_OwnerTag = ORDER_TAG::ENEMY;
	m_Tag = "Enemy";
	m_HitSize = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_TargetPos = m_Pos;

	//モデルの設定
	MODEL model = { (char*)"data/MODEL/EnemyS.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this ,true) };
	m_ModelMap["Parts"] = model;

	//モデルの読み込み
	Object::ModelLoad();

	m_Spd = 1.5f;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Enemy::~Enemy()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void Enemy::Init(void)
{


	//方向を単位ベクトル化する
	D3DXVec3Normalize(&m_Dir, &m_Dir);

	//影のセット
	m_Shadow = SetShadow(D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z), 80.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void Enemy::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void Enemy::Update(void)
{
	m_ArrayPos = m_pMap->GetArrayPos(m_Pos);//マップの行列での位置

	//-------------------------------------------------------------
	//音がしたタイルへ向かう
	//-------------------------------------------------------------
	TILE tile = m_pMap->GetTile(m_Pos);
	//自分のいるところが範囲内なら
	if (tile.TileState == HEAR_SOUND)
	{
		m_TargetPos = m_pGameWorld->GetPlayer()->GetPos();
	}
	double pdr = PointDirectionRadian(m_Pos.x, m_Pos.z, m_TargetPos.x, m_TargetPos.z);

	D3DXVECTOR2 cv = CalculateVector(double(m_Spd), pdr);

	if (!m_Collision.CollisionBB(m_Pos, m_TargetPos, m_HitSize, D3DXVECTOR3(20,20,20)))
	{
		m_Move.x = cv.x;
		m_Move.z = cv.y;
	}
	else
	{
		m_Move *= 0.5f;
	}

	//-------------------------------------------------------------
	//当たり判定
	//-------------------------------------------------------------
	HitJudge();

	//-------------------------------------------------------------
	//移動
	//-------------------------------------------------------------
	m_Pos += m_Move * m_Spd;

	//-------------------------------------------------------------
	//波紋表示
	//-------------------------------------------------------------
	RipplesSet(ORDER_TAG::ENEMY, m_OwnerNum);

	//影の座標を更新する
	SetPositionShadow(m_Shadow, D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));

	//モデル更新
	Object::Update();

	//前ポジション更新
	m_OldPos = m_Pos;
	m_OldArrayPos = m_ArrayPos;

#ifdef _DEBUG	// デバッグ情報を表示する

#endif
}

