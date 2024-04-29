/*==============================================================================

   マップに並べるタイル(派生) [Tile.cpp]
														 Author : 渡邉 修
														 Date   : 2024/01/16
--------------------------------------------------------------------------------

==============================================================================*/
#include "Tile.h"
#include "GameWorld.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Tile::Tile(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TILE_PATTERN pattern, GameWorld* gameWorld)
	: Object(pos, rot, D3DXVECTOR3(50.0f, 100.0f, 50.0f), gameWorld)
{
	m_Tag = "Tile";
	m_Scl = (D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	MODEL model{};

	//-------------------------------------------------------------//タイルを追加したらここに追加
	//モデルの設定
	switch (pattern)
	{
	case WALL:
		model = { (char*)"data/MODEL/Wall.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case WALL_END:
		model = { (char*)"data/MODEL/WallEnd.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case PILLAR:
		model = { (char*)"data/MODEL/Pillar.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case CORNER:
		model = { (char*)"data/MODEL/WallCorner.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case T:
		model = { (char*)"data/MODEL/WallT.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case CROSS:
		model = { (char*)"data/MODEL/WallCross.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case DEAD_END:
		model = { (char*)"data/MODEL/DeadEnd.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case AISLE:
		model = { (char*)"data/MODEL/Aisle.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	case CEILING:
		model = { (char*)"data/MODEL/Ceiling.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this, true) };
		break;
	default:
		break;
	}
	//-------------------------------------------------------------//

	m_ModelMap["Parts"] = model;

	//モデルの読み込み
	Object::ModelLoad();
}

Tile::~Tile()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void Tile::Init()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void Tile::Update()
{
	Object::Update();





}


