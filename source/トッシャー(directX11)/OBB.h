/*==============================================================================

   ���������E�{�b�N�X [OBB.h]
                                                         Author : �n� �C
                                                         Date   : 2024/02/03
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include <d3dx9.h>
//#include "Object.h"

class OBB
{
private:
    D3DXVECTOR3 m_Pos;              // �ʒu
    D3DXVECTOR3 m_Rot;              // ��]
    D3DXVECTOR3 m_NormaDirect[3];   // �����x�N�g��
    D3DXVECTOR3 m_Length;           // �e�������̒���
    //Object* m_Obj;

public:
    OBB(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 lengths/*, Object* obj*/);
    void Update();
    D3DXVECTOR3 GetPos() const;               // �ʒu���擾
    D3DXVECTOR3 GetDirect(int index) const;   // �w�莲�ԍ��̕����x�N�g�����擾(����: 0=X����, 1=Y����, 2=Z����)
    D3DXVECTOR3 GetLen() const;               // �w�莲�����̒������擾
    void SetPos(D3DXVECTOR3 pos);
    void SetDirect(D3DXVECTOR3 rot);
};

