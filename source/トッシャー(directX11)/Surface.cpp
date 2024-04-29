/*==============================================================================

   面 [Surface.cpp]
														 Author : 渡邉 修
														 Date   : 2024/02/05
--------------------------------------------------------------------------------

==============================================================================*/
#include "Surface.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
Surface::Surface()
{
}

Surface::~Surface()
{
}

void Surface::SetPointA(D3DXVECTOR3 posA)
{
	m_PointA = posA;
}

void Surface::SetPointB(D3DXVECTOR3 posB)
{
	m_PointB = posB;
}

void Surface::SetDirVec(D3DXVECTOR3 dirVec)
{
}

D3DXVECTOR3 Surface::GetPointA() const
{
	return m_PointA;
}

D3DXVECTOR3 Surface::GetPointB() const
{
	return m_PointB;
}

D3DXVECTOR3 Surface::GetDirVec() const
{
	return m_DirVec;
}