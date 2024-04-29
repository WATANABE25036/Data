/*==============================================================================

   アイテム管理 [Inventory.h]
														 Author : 渡邉 修
														 Date   : 2024/01/03
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include "Item.h"

class Inventory
{
public:
	Inventory();
	Inventory(GameWorld* gameWorld);

	void Init();
	void Update();
	void Drow();

	void AddItem(Item* item);
	void DeleteItem(Item* item);
	Item* DeleteItem();
	void AllDeleteItem();
	bool Drop();
	void IDSort();
	void IDSortR();
	void NumSort();
	void NumSortR();
	void OverDrop();

	std::list<Item*> GetItemLest() const { return m_pItemLest; }
	int GetMaxCoin() const { return m_MaxCoin; }
	void SetPos(D3DXVECTOR2 pos) { m_Pos = pos; }

private:
	std::list<Item*> m_pItemLest;
	int m_Cou = 0;
	int m_MaxItem = 10;
	int	m_TexNo = 0;	// テクスチャ番号
	int m_MaxCoin = 0;	//マップのコイン数
	D3DXVECTOR2 m_WH = D3DXVECTOR2(0.0f, 0.0f);		// 幅と高さ
	D3DXVECTOR2	m_Pos = D3DXVECTOR2(0.0f, 0.0f);	// ポリゴンの座標
	GameWorld* m_pGameWorld = nullptr;
	Item* m_pItem = nullptr;
};

