/*==============================================================================

   ゲームシステム [GameSystem.cpp]
                                                         Author : 渡邉 修
                                                         Date   : 2023/12/26
--------------------------------------------------------------------------------

==============================================================================*/
#include "GameSystem.h"

GameSystem::GameSystem()
    : m_Map(&m_GameWorld), m_Inventory(&m_GameWorld)
{
}

GameSystem::~GameSystem()
{

}

void GameSystem::Init()
{
    // プレイヤーの生成
    m_GameWorld.CreatePlayer(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), &m_Map, &m_Inventory);
    m_GameWorld.CreateCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
    m_Map.RandomMapCreate(8, 20, 2, 5);
    m_Map.CreateMap();//カメラより後

    m_Inventory.Init();

    m_GameWorld.Init();
}

void GameSystem::Uninit()
{
    m_GameWorld.Uninit();
}

void GameSystem::Update()
{
    m_GameWorld.Update();
    m_pPlayer = m_GameWorld.GetPlayer();
    m_Map.Update();
}

void GameSystem::Draw()
{
    m_GameWorld.Draw();
    m_Inventory.Drow();
}
