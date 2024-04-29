/*==============================================================================

   方向性境界ボックス [OBB.cpp]
                                                         Author : 渡邉 修
                                                         Date   : 2024/02/03
--------------------------------------------------------------------------------

==============================================================================*/
#include "OBB.h"

//=============================================================================
// コンストラクタ / デストラクタ
//=============================================================================
OBB::OBB(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 lengths/*, Object* obj*/)
    : m_Pos(pos), m_Rot(rot), m_Length(lengths)/*, m_Obj(obj)*/
{
    //動かない場合の方向ベクトルで初期化
    m_NormaDirect[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
    m_NormaDirect[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_NormaDirect[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

void OBB::Update()
{
    //SetDirect(m_Obj->GetRot());
    //SetPos(m_Obj->GetPos());
}

D3DXVECTOR3 OBB::GetPos() const
{
    return m_Pos;
}

D3DXVECTOR3 OBB::GetDirect(int index) const
{
    return m_NormaDirect[index];
}

D3DXVECTOR3 OBB::GetLen() const
{
    return m_Length;
}

void OBB::SetPos(D3DXVECTOR3 pos)
{
    m_Pos = pos;
}

void OBB::SetDirect(D3DXVECTOR3 rot)
{
    D3DXMATRIX rotationX, rotationY, rotationZ;
    D3DXMatrixRotationX(&rotationX, rot.x);
    D3DXMatrixRotationY(&rotationY, rot.y);
    D3DXMatrixRotationZ(&rotationZ, rot.z);
    // 各軸の回転行列を結合して最終的な回転行列を作成
    D3DXMATRIX rotationMatrix = rotationX * rotationY * rotationZ;

    m_NormaDirect[0] = D3DXVECTOR3(rotationMatrix._11, rotationMatrix._12, rotationMatrix._13);
    m_NormaDirect[1] = D3DXVECTOR3(rotationMatrix._21, rotationMatrix._22, rotationMatrix._23);
    m_NormaDirect[2] = D3DXVECTOR3(rotationMatrix._31, rotationMatrix._32, rotationMatrix._33);

    D3DXVec3Normalize(&m_NormaDirect[0], &m_NormaDirect[0]);
    D3DXVec3Normalize(&m_NormaDirect[1], &m_NormaDirect[1]);
    D3DXVec3Normalize(&m_NormaDirect[2], &m_NormaDirect[2]);
}

