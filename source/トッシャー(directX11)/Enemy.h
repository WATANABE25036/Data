/*==============================================================================

   ÉGÉlÉ~Å[(îhê∂) [Enemy.h]
														 Author : ìnÁ≥ èC
														 Date   : 2024/01/11
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <d3dx9.h>
#include "BodyParts.h"
#include "Renderer.h"
#include "Collision.h"
#include "ObjCharacter.h"

class Enemy :public ObjCharacter
{
public:
	Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map);
	~Enemy() override;

	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	D3DXVECTOR3 m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	static int m_sCou;
};


