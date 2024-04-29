/*==============================================================================

   ìßñæÇ»É{ÉbÉNÉXêÖ(îhê∂) [ClearBoxWater.h]
														 Author : ìnÁ≥ èC
														 Date   : 2024/02/11
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "BodyParts.h"

class ClearBoxWater : public Object
{
public:
	ClearBoxWater(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld);
	~ClearBoxWater() override;
	void Init() override;
	void Uninit() override;
	void Update() override;

private:

};



