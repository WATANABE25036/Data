/*==============================================================================

   �� [Surface.cpp]
														 Author : �n� �C
														 Date   : 2024/02/05
--------------------------------------------------------------------------------

==============================================================================*/
#include "Surface.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
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