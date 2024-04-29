/*==============================================================================

   方向性境界ボックス [OBB.h]
                                                         Author : 渡邉 修
                                                         Date   : 2024/02/03
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include <d3dx9.h>
//#include "Object.h"

class OBB
{
private:
    D3DXVECTOR3 m_Pos;              // 位置
    D3DXVECTOR3 m_Rot;              // 回転
    D3DXVECTOR3 m_NormaDirect[3];   // 方向ベクトル
    D3DXVECTOR3 m_Length;           // 各軸方向の長さ
    //Object* m_Obj;

public:
    OBB(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 lengths/*, Object* obj*/);
    void Update();
    D3DXVECTOR3 GetPos() const;               // 位置を取得
    D3DXVECTOR3 GetDirect(int index) const;   // 指定軸番号の方向ベクトルを取得(引数: 0=X方向, 1=Y方向, 2=Z方向)
    D3DXVECTOR3 GetLen() const;               // 指定軸方向の長さを取得
    void SetPos(D3DXVECTOR3 pos);
    void SetDirect(D3DXVECTOR3 rot);
};

