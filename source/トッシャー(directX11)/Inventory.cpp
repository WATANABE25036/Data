/*==============================================================================

   アイテム管理 [Inventory.cpp]
														 Author : 渡邉 修
														 Date   : 2024/01/03
--------------------------------------------------------------------------------

==============================================================================*/
#include "Inventory.h"
#include "GameWorld.h"
#include "Texture.h"
#include "Sprite.h"

Inventory::Inventory()
{

}

Inventory::Inventory(GameWorld* gameWorld)
	: m_pGameWorld(gameWorld)
{

}

void Inventory::Init()
{
	//テクスチャ生成
	m_TexNo = LoadTexture((char*)"data/TEXTURE/CoinGold.png");
	m_pItemLest.clear();
	m_WH = D3DXVECTOR2(100.0f, 100.0f);
	m_Pos = D3DXVECTOR2(800.0f, 60.0f);
}

void Inventory::AddItem(Item* item)
{
	m_Cou++;
	m_MaxCoin = item->GetItemCou();
	item->SetNum(m_Cou);
	m_pItemLest.push_back(item);
}

//捨てるアイテムを指定して消す
void Inventory::DeleteItem(Item* item)
{
	m_pItemLest.remove_if([item](Item* itemA)
	{
		if (item->GetItemPattern() == itemA->GetItemPattern())
		{
			delete itemA;
			return true;
		}
		return false;
	});
}

//一番古いアイテムを消す
Item* Inventory::DeleteItem()
{
	if(m_pItemLest.size() < 1) return nullptr;

	m_pItemLest.sort([](Item* itemA, Item* itemB)
	{
		return itemA->GetNum() < itemB->GetNum();
	});
	Item* item = m_pItemLest.front();
	m_pGameWorld->DestroyObject(item);
	m_pItemLest.pop_front();

	return item;//捨てたアイテムを返す
}

void Inventory::AllDeleteItem()
{
	m_pItemLest.clear();
	for (auto it : m_pItemLest)
	{
		delete it;
	}
}

//一番古いアイテムをフィールドに捨てる
bool Inventory::Drop()
{
	if (m_pItemLest.size() < 1) return false;

	D3DXVECTOR3 playerPos = m_pGameWorld->GetPlayer()->GetPos();
	m_pGameWorld->CreateCoinGold(playerPos);
	return true;
}

//アイテムID順でソート
void Inventory::IDSort()
{
	m_pItemLest.sort([](Item* itemA, Item* itemB)
	{
		return itemA->GetItemPattern() < itemB->GetItemPattern();
	});
}

//アイテムID順でソート(逆)
void Inventory::IDSortR()
{
	m_pItemLest.sort([](Item* itemA, Item* itemB)
	{
		return itemA->GetItemPattern() > itemB->GetItemPattern();
	});
}

//拾った順にソート
void Inventory::NumSort()
{
	m_pItemLest.sort([](Item* itemA, Item* itemB)
	{
			return itemA->GetNum() < itemB->GetNum();
	});
}

//拾った順にソート(逆)
void Inventory::NumSortR()
{
	m_pItemLest.sort([](Item* itemA, Item* itemB)
	{
		return itemA->GetNum() > itemB->GetNum();
	});
}

//インベントリがいっぱいだったら一番古いアイテムを消す
void Inventory::OverDrop()
{
	if (m_pItemLest.size() > m_MaxItem)
	{
		Drop();
	}
}

void Inventory::Update()
{
	OverDrop();
}

void Inventory::Drow()
{
	int cou = 0;
	int couY = 0;
	float offsetX = 0.0f;

	for (auto item : m_pItemLest)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexNo));

		// スコアの位置やテクスチャー座標を反映
		float px = m_Pos.x + m_WH.x * cou;	// 表示位置X
		float py = m_Pos.y + m_WH.y * couY;	// 表示位置Y
		float pw = m_WH.x;					// 表示幅
		float ph = m_WH.y;					// 表示高さ

		float tw = 1.0f / 1;		// テクスチャの幅
		float th = 1.0f / 1;		// テクスチャの高さ
		float tx = offsetX * tw;	// テクスチャの左上X座標
		float ty = 0.0f;			// テクスチャの左上Y座標

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		DrawSprite(m_TexNo, px, py, pw, ph, tx, ty, tw, th);

		cou++;

		//改行
		if (cou >= 10)
		{
			couY++;
			cou = 0;
		}
	}
}