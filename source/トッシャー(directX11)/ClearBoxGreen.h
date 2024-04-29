/*==============================================================================

   ìßñæÇ»É{ÉbÉNÉXóŒ(îhê∂) [ClearBoxGreen.h]
														 Author : ìnÁ≥ èC
														 Date   : 2024/02/11
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "BodyParts.h"

class ClearBoxGreen : public Object
{
public:
	ClearBoxGreen(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld);
	~ClearBoxGreen() override;
	void Init() override;
	void Uninit() override;
	void Update() override;

private:

};

