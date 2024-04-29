/*==============================================================================

   ÉQÅ[ÉÄÉVÉXÉeÉÄ [GameSystem.h]
														 Author : ìnÁ≥ èC
														 Date   : 2023/12/26
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "GameWorld.h"
#include "Player.h"
#include "Map.h"
#include "Inventory.h"

class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	Player* GetPlayer() const { return m_pPlayer; }
	Inventory* GetInventory() { return &m_Inventory; }

private:
	Player* m_pPlayer = nullptr;
	GameWorld m_GameWorld;
	Map m_Map;
	Inventory m_Inventory;
};
