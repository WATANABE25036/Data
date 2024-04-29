/*==============================================================================

   ìñÇΩÇËîªíËèàóù [Collision.h]
														 Author : ìnÁ≥ èC
														 Date   : 2024/02/03
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "OBB.h"

class Collision
{
public:
	Collision();
	~Collision();
	bool CollisionBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2);
	bool CollisionBS(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
	bool ColOBBs(const OBB& obb1, const OBB& obb2, const D3DXVECTOR3 offset) const;
	FLOAT LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3 = 0) const;
	D3DXVECTOR3* CalcWallScratchVector(D3DXVECTOR3* out, const D3DXVECTOR3& front, const D3DXVECTOR3& normal);

private:
	D3DXVECTOR3 m_Pos1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Size1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Size2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};
