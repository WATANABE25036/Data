/*==============================================================================

   ゲームオブジェクト管理 [GameWorld.h]
														 Author : 渡邉 修
														 Date   : 2023/12/24
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <d3dx9.h>
#include <list>
#include "Object.h"
#include "Camera.h"
#include "Player.h"
#include "BillBoard.h"
#include "Enemy.h"
#include "Tile.h"
#include "ClearBoxRed.h"
#include "ClearBoxBlue.h"
#include "ClearBoxGreen.h"
#include "ClearBoxWater.h"
#include "Item.h"
#include "Effect.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
enum class ORDER_TAG
{
	NONE,
	PLAYER,
	ENEMY,
};

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void DestroyCamera();
	void DestroyObject(Object* obj);
	void DestroyObject(std::string tag);
	void DestroyObject(ORDER_TAG tag, int ownerCou);
	Player* GetPlayer();
	Camera* GetCamera();
	std::list<Object*> GetObjectList();

	Player* CreatePlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Map* map, Inventory* m_Inventory);
	Camera* CreateCamera(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateWallEnd(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateAisle(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateCeiling(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateDeadEnd(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreatePillar(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateCorner(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateT(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Tile* CreateCross(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	ClearBoxRed* CreateClearBoxRed(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	ClearBoxBlue* CreateClearBoxBlue(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	ClearBoxGreen* CreateClearBoxGreen(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	ClearBoxWater* CreateClearBoxWater(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Item* CreateCoinGold(D3DXVECTOR3 pos, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Enemy* CreateEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Map* map);
	Effect* CreateRipples(D3DXVECTOR3 pos, ORDER_TAG tag, int ownerCou, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f));

private:
	std::list<Object*> m_pObjectList;
	Player* m_pPlayer = nullptr;
	Camera* m_pCamera = nullptr;
};





