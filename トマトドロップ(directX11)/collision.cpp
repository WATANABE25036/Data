/*==============================================================================

   �e�N�X�`���̕`�� [collision.cpp]
                                                         Author :
                                                         Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include "collision.h"

//*****************************************************************************
// �����蔻�菈��
//*****************************************************************************
void UpdateCollision()
{

}

//---------------------------------------------------------------------
// �~���m�̓����蔻��
// in pos1, pos2: �~�̒��S���W
//    size1, size2: �~�̔��a
// out true:������ flase:�O��
//---------------------------------------------------------------------
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2)
{
    //���S���m�̒���(���[�g���g���o�[�W����)
    D3DXVECTOR2 distance = pos1 - pos2;
    float length = D3DXVec2Length(&distance);

    //�~1�Ɖ~2�̔��a�̑��a
    float size = size1 + size2;

    //���S���m�̒����Ɣ��a�̑��a�̔�r
    if (length < size)
    {
        return true; //�~���m���������Ă���
    }

    return false; //�~���m���������Ă��Ȃ�
}

//---------------------------------------------------------------------
// �Z�`���m�̓����蔻��
// in pos1, pos2: ��`�̒��S���W
//    size1, size2: ��`�̃T�C�Y
// out true:������ flase:�O��
//---------------------------------------------------------------------
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
    D3DXVECTOR2 min1, max1; //�L�����N�^1�̍�����W�A�E�����W
    D3DXVECTOR2 min2, max2; //�L�����N�^2�̍�����W�A�E�����W

    min1.x = pos1.x - size1.x * 0.5f;//�L�����N�^1�̍�����WX
    min1.y = pos1.y - size1.y * 0.5f;//�L�����N�^1�̍�����WY
    max1.x = pos1.x + size1.x * 0.5f;//�L�����N�^1�̉E�����WX
    max1.y = pos1.y + size1.y * 0.5f;//�L�����N�^1�̉E�����WY

    min2.x = pos2.x - size2.x * 0.5f;//�L�����N�^2�̍�����WX
    min2.y = pos2.y - size2.y * 0.5f;//�L�����N�^2�̍�����WY
    max2.x = pos2.x + size2.x * 0.5f;//�L�����N�^2�̉E�����WX
    max2.y = pos2.y + size2.y * 0.5f;//�L�����N�^2�̉E�����WY

    //X���̔���
    if ((min1.x < max2.x) && (max1.x > min2.x))
    {
        //Y���̔���
        if ((min1.y < max2.y) && (max1.y > min2.y))
        {
            return true; //1�̋�`�͓������Ă���
        }
    }

    return false; //2�̒Z�a�͓������Ă��Ȃ�

}

//---------------------------------------------------------------------
// �Z�`���m����`�̓����蔻��(�p�x�t)
// in pos1, pos2: ��`�̒��S���W
// size1, size2: ��`�̃T�C�Y
// rot2: ��`�̊p�x(���W�A��)
// out true:������ flase:�O��
//---------------------------------------------------------------------
bool CollisionRot(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2, float rot2)
{
    //�Q�l https://yttm-work.jp/collision/collision_0007.html
    // ��`�̒��S�����_�Ƃ������΍��W���쐬����
    D3DXVECTOR2 relative_position = D3DXVECTOR2(pos1.x - pos2.x, pos1.y - pos2.y);

    // ���΍��W�ɑ΂��ċ�`�̉�]��ł������t�s����|����
    D3DXVECTOR2 transform_pos = D3DXVECTOR2(
        cosf(rot2) * relative_position.x + sinf(rot2) * relative_position.y,
        -sinf(rot2) * relative_position.x + cosf(rot2) * relative_position.y
    );

    // ��`�Ɠ_�̓����蔻����s��
    if (-size2.x / 2.0f <= transform_pos.x + size1.x && size2.x / 2.0f >= transform_pos.x - size1.x &&
        -size2.y / 2.0f <= transform_pos.y + size1.y && size2.y / 2.0f >= transform_pos.y - size1.x)
    {
        return true;
    }

    return false;
}