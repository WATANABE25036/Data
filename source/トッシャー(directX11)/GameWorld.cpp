/*==============================================================================

   ゲームオブジェクト管理 [GameWorld.cpp]
														 Author : 渡邉 修
														 Date   : 2023/12/24
--------------------------------------------------------------------------------

==============================================================================*/
#include "Polyline.h"
#include "Shadow.h"
#include "GameWorld.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT GameWorld::Init()
{
	m_pCamera->Init();

	// 影の初期化
	InitShadow();

	// ポリラインの初期化
	InitPolyLine();

	m_pPlayer->Init();

	HRESULT hr = S_OK;
	for (auto it : m_pObjectList)
	{
		hr = it->InitAll();
		it->Init();

		if (FAILED(hr))	// 初期化が失敗
		{
			DebugPrint("初期化失敗 タグ番号", (float)(it->GetOwnerTag()));
			return E_ABORT;
		}
	}
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void GameWorld::Uninit()
{
	m_pCamera->Uninit();

	m_pPlayer->Uninit();
	for (auto it : m_pObjectList)
	{
		it->Uninit();
	}

	for (auto it : m_pObjectList)
	{
		if (it != nullptr) delete it;
	}
	m_pObjectList.clear();

	if (m_pCamera != nullptr) delete m_pCamera;
	if (m_pPlayer != nullptr) delete m_pPlayer;
}

//=============================================================================
// 更新処理
//=============================================================================
void GameWorld::Update()
{
	m_pCamera->Update();
	
	m_pPlayer->Update();

	for (auto it : m_pObjectList)
	{
		it->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void GameWorld::Draw()
{
	m_pCamera->SetCameraAT();
	m_pCamera->SetCamera();
	
	// 深度テスト有効
	SetDepthEnable(true);

	// ライティング有効
	SetLightEnable(true);

	// 影の描画処理
	DrawShadow();

	m_pPlayer->Draw();
	for (auto it : m_pObjectList)
	{
		if (it->GetTag() == "Enemy") continue; //エネミーは描画しない
		it->Draw();
	}
}

//=============================================================================
// 生成
//=============================================================================
Player* GameWorld::CreatePlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Map* map, Inventory* m_Inventory)
{
	m_pPlayer = new Player(pos, rot, this, map, m_Inventory);
	return m_pPlayer;
}

Camera* GameWorld::CreateCamera(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pCamera = new Camera(pos, rot, m_pPlayer, this);
	return m_pCamera;
}

Tile* GameWorld::CreateWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::WALL, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateWallEnd(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::WALL_END, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateAisle(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::AISLE, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateCeiling(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::CEILING, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateDeadEnd(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::DEAD_END, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreatePillar(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::PILLAR, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateCorner(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::CORNER, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateT(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::T, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Tile* GameWorld::CreateCross(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Tile* pObj = new Tile(pos, rot, TILE_PATTERN::CROSS, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Enemy* GameWorld::CreateEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Map* map)
{
	Enemy* pObj = new Enemy(pos, rot, this, map);
	m_pObjectList.push_back(pObj);
	return pObj;
}

ClearBoxRed* GameWorld::CreateClearBoxRed(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ClearBoxRed* pObj = new ClearBoxRed(pos, rot, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

ClearBoxBlue* GameWorld::CreateClearBoxBlue(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ClearBoxBlue* pObj = new ClearBoxBlue(pos, rot, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

ClearBoxGreen* GameWorld::CreateClearBoxGreen(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ClearBoxGreen* pObj = new ClearBoxGreen(pos, rot, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

ClearBoxWater* GameWorld::CreateClearBoxWater(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ClearBoxWater* pObj = new ClearBoxWater(pos, rot, this);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Item* GameWorld::CreateCoinGold(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Item* pObj = new Item(pos, rot, COIN_GOLD, this, m_pCamera);
	m_pObjectList.push_back(pObj);
	return pObj;
}

Effect* GameWorld::CreateRipples(D3DXVECTOR3 pos, ORDER_TAG tag, int ownerCou, D3DXVECTOR3 rot)
{
	Effect* pObj = new Effect(pos, D3DXVECTOR3(0.0f, D3DXToRadian(90.0f) , 0.0f), RIPPLES, this, tag, ownerCou);
	m_pObjectList.push_back(pObj);
	return pObj;
}

//=============================================================================
// 削除
//=============================================================================
void GameWorld::DestroyObject(Object* obj)
{
	m_pObjectList.remove(obj);
	delete obj;
}

//タグで削除
void GameWorld::DestroyObject(std::string tag)
{
	m_pObjectList.remove_if([&](Object* obj)
		{
			bool shouldRemove = obj->GetTag() == tag;
			if (shouldRemove)
			{
				delete obj;
			}
			return shouldRemove;
		});
}

//オーダータグで削除
void GameWorld::DestroyObject(ORDER_TAG tag, int ownerCou)
{
	for (auto it = m_pObjectList.begin(); it != m_pObjectList.end(); ++it)
	{
		if ((*it)->GetOwnerTag() == tag && (*it)->GetOwnerCou() == ownerCou)
		{
			delete* it;
			m_pObjectList.erase(it);
			break; // タグが一致する最初のオブジェクトを見つけたらループを終了
		}
	}
}

void GameWorld::DestroyCamera()
{
	delete m_pCamera;  // m_Camera が指すオブジェクトを解放
	m_pCamera = nullptr;  // ポインタを無効化
}

//=============================================================================
// ゲッター・セッター
//=============================================================================
Player* GameWorld::GetPlayer()
{
	return m_pPlayer;
}

std::list<Object*> GameWorld::GetObjectList()
{
	return m_pObjectList;
}

Camera* GameWorld::GetCamera()
{
	return m_pCamera;
}

