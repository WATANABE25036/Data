/*==============================================================================

   ìßñæÇ»É{ÉbÉNÉXê‘(îhê∂) [ClearBoxRed.h]
														 Author : ìnÁ≥ èC
														 Date   : 2024/02/11
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "BodyParts.h"

class ClearBoxRed : public Object
{
public:
	ClearBoxRed(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld);
	~ClearBoxRed() override;
	void Init() override;
	void Uninit() override;
	void Update() override;

private:

};

