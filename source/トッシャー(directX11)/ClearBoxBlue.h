/*==============================================================================

   ìßñæÇ»É{ÉbÉNÉXê¬(îhê∂) [ClearBoxBlue.h]
														 Author : ìnÁ≥ èC
														 Date   : 2024/02/11
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "BodyParts.h"

class ClearBoxBlue : public Object
{
public:
	ClearBoxBlue(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld);
	~ClearBoxBlue() override;
	void Init() override;
	void Uninit() override;
	void Update() override;

private:

};

