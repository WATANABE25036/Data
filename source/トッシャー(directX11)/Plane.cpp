///*==============================================================================
//
//   平面 [Plane.cpp]
//                                                         Author : 渡邉 修
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
//// ローカル座標での法線ベクトルを設定
//bool Plane::SetNormal_L(D3DXVECTOR3* norm)
//{
//    m_LocalNormal = *norm;
//    D3DXVec3Normalize(&m_LocalNormal, &m_LocalNormal);
//}
//
//// ローカル座標での法線ベクトルを取得
//void Plane::GetNormal_L(D3DXVECTOR3* norm) const
//{
//    *norm = m_LocalNormal;
//}
//
//// ワールド座標での法線ベクトルを取得
//void Plane::GetNormal_W(D3DXVECTOR3* norm) const
//{
//    *norm = m_LocalNormal;
//}
//
//// ローカル位置を設定
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
//// ローカル座標位置を取得
//D3DXVECTOR3 Plane::GetPos_L() const
//{
//    return m_Pos;
//}
//
//// ワールド座標位置を取得
//D3DXVECTOR3 Plane::GetPos_W() const
//{
//    // 仮定: ローカル座標からワールド座標への変換が手動で行われる場合
//    // 具体的な変換ロジックが必要
//    return m_Pos;
//}
//
//// ワールド座標での法線ベクトルを取得 (手動変換版)
//void Plane::GetNormal_W_Manual(D3DXVECTOR3* norm, const D3DXMATRIX& worldMatrix)
//{
//    // 法線ベクトルを回転行列で変換
//    D3DXVec3TransformNormal(norm, &m_LocalNormal, &worldMatrix);
//    D3DXVec3Normalize(norm, norm);
//}
//
//// ワールド座標位置を取得 (手動変換版)
//D3DXVECTOR3 Plane::GetPos_W_Manual(const D3DXMATRIX& worldMatrix)
//{
//    D3DXVECTOR3 worldPos;
//    // 位置ベクトルを変換
//    D3DXVec3TransformCoord(&worldPos, &m_Pos, &worldMatrix);
//    return worldPos;
//}