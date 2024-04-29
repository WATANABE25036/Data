///*==============================================================================
//
//   ���� [Plane.cpp]
//                                                         Author : �n� �C
//                                                         Date   : 2024/02/04
//--------------------------------------------------------------------------------
//
//==============================================================================*/
//#include "Plane.h"
//
//Plane::Plane()
//{
//    m_LocalNormal.x = 0.0f;
//    m_LocalNormal.y = 0.0f;
//    m_LocalNormal.z = 1.0f;
//}
//
//// ���[�J�����W�ł̖@���x�N�g����ݒ�
//bool Plane::SetNormal_L(D3DXVECTOR3* norm)
//{
//    m_LocalNormal = *norm;
//    D3DXVec3Normalize(&m_LocalNormal, &m_LocalNormal);
//}
//
//// ���[�J�����W�ł̖@���x�N�g�����擾
//void Plane::GetNormal_L(D3DXVECTOR3* norm) const
//{
//    *norm = m_LocalNormal;
//}
//
//// ���[���h���W�ł̖@���x�N�g�����擾
//void Plane::GetNormal_W(D3DXVECTOR3* norm) const
//{
//    *norm = m_LocalNormal;
//}
//
//// ���[�J���ʒu��ݒ�
//void Plane::SetPos_L(FLOAT x, FLOAT y, FLOAT z)
//{
//    m_Pos.x = x;
//    m_Pos.y = y;
//    m_Pos.z = z;
//}
//
//void Plane::SetPos_L(D3DXVECTOR3* pos)
//{
//    m_Pos = *pos;
//}
//
//// ���[�J�����W�ʒu���擾
//D3DXVECTOR3 Plane::GetPos_L() const
//{
//    return m_Pos;
//}
//
//// ���[���h���W�ʒu���擾
//D3DXVECTOR3 Plane::GetPos_W() const
//{
//    // ����: ���[�J�����W���烏�[���h���W�ւ̕ϊ����蓮�ōs����ꍇ
//    // ��̓I�ȕϊ����W�b�N���K�v
//    return m_Pos;
//}
//
//// ���[���h���W�ł̖@���x�N�g�����擾 (�蓮�ϊ���)
//void Plane::GetNormal_W_Manual(D3DXVECTOR3* norm, const D3DXMATRIX& worldMatrix)
//{
//    // �@���x�N�g������]�s��ŕϊ�
//    D3DXVec3TransformNormal(norm, &m_LocalNormal, &worldMatrix);
//    D3DXVec3Normalize(norm, norm);
//}
//
//// ���[���h���W�ʒu���擾 (�蓮�ϊ���)
//D3DXVECTOR3 Plane::GetPos_W_Manual(const D3DXMATRIX& worldMatrix)
//{
//    D3DXVECTOR3 worldPos;
//    // �ʒu�x�N�g����ϊ�
//    D3DXVec3TransformCoord(&worldPos, &m_Pos, &worldMatrix);
//    return worldPos;
//}