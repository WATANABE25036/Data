/*==============================================================================

   �L�����N�^�[(�I�u�W�F�N�g) [ObjCharacter.cpp]
														 Author : �n� �C
														 Date   : 2023/02/14
--------------------------------------------------------------------------------

==============================================================================*/
#include "ObjCharacter.h"
#include "Library.h"
#include "Input.h"
#include "Map.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
ObjCharacter::ObjCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map)
	: Object(pos, rot, D3DXVECTOR3(1.0f, 1.0f, 1.0f), gameWorld), m_StartPos(pos), m_pMap(map)
{

}

ObjCharacter::~ObjCharacter()
{

}

//=============================================================================
// �ǂƂ̓����蔻�菈��
//=============================================================================
void ObjCharacter::HitJudge()
{
	//�ǂƂ̓����蔻��
	//����̃^�C�������擾
	m_ArrayPos = m_pMap->GetArrayPos(m_Pos);//�}�b�v�̍s��ł̈ʒu
	D3DXVECTOR3 dir(Sign(m_Dir.x), Sign(m_Dir.y), Sign(m_Dir.z));
	AROUND_TILE aroundTile = m_pMap->GetAroundTile(m_Pos);//�����̎���̃^�C��
	TILE_ATTRIBUTE tileNext = m_pMap->GetTile(m_Pos + m_Move).TileAttribute;//�ړ���^�C��
	D3DXVECTOR2 arrayPosNext = m_pMap->GetArrayPos(m_Pos + m_Move);//�}�b�v�̍s��ł̈ړ���ʒu

	if (!GetKeyboardPress(DIK_V))//�����蔻�薳��(�f�o�b�O�p)
	{
		//�΂߂ɂ���^�C���ɂ͈ړ��ł��Ȃ��悤�ɂ���
		if (
			//�΂ߍ�������ӂɃ^�C��������΂߂̃^�C���Ɉړ������ꍇ
			((aroundTile.Top.TileAttribute == STOP && aroundTile.Right.TileAttribute == STOP) && (m_ArrayPos.x < arrayPosNext.x) && (m_ArrayPos.y < arrayPosNext.y)) ||
			((aroundTile.Right.TileAttribute == STOP && aroundTile.Under.TileAttribute == STOP) && (m_ArrayPos.x < arrayPosNext.x) && (m_ArrayPos.y > arrayPosNext.y)) ||
			((aroundTile.Under.TileAttribute == STOP && aroundTile.Left.TileAttribute == STOP) && (m_ArrayPos.x > arrayPosNext.x) && (m_ArrayPos.y > arrayPosNext.y)) ||
			((aroundTile.Left.TileAttribute == STOP && aroundTile.Top.TileAttribute == STOP) && (m_ArrayPos.x > arrayPosNext.x) && (m_ArrayPos.y < arrayPosNext.y))
			)
		{
			m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // �ړ����Ȃ�
		}

		//�㉺���E�ōs���~�܂�^�C���ɂԂ������Ƃ�
		else if (tileNext == STOP)//�ړ��悪�s���~�܂肾������
		{
			D3DXVECTOR3 wallNormal;//�@���x�N�g��

			//���肪�s���~�܂�ōs��ł̈ʒu���ς������
			if (aroundTile.Top.TileAttribute == STOP && m_ArrayPos.y < arrayPosNext.y)
			{
				wallNormal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);//�Œ肳�ꂽ�p�x�ł̔z�u�Ȃ̂ň��
				WallSlidingMove(m_Move, wallNormal);//�ǐ���ړ�
			}
			else if (aroundTile.Right.TileAttribute == STOP && m_ArrayPos.x < arrayPosNext.x)
			{
				wallNormal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
				WallSlidingMove(m_Move, wallNormal);
			}
			else if (aroundTile.Under.TileAttribute == STOP && m_ArrayPos.y > arrayPosNext.y)
			{
				wallNormal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				WallSlidingMove(m_Move, wallNormal);
			}
			else if (aroundTile.Left.TileAttribute == STOP && m_ArrayPos.x > arrayPosNext.x)
			{
				wallNormal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
				WallSlidingMove(m_Move, wallNormal);
			}

			//�܂��s���~�܂�ɍs�����Ƃ��Ă�����~�߂�
			tileNext = m_pMap->GetTile(m_Pos + m_Move).TileAttribute;
			if (tileNext == STOP)
			{
				m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
}

//=============================================================================
// �ǐ���ړ��̈ړ���ɂ���
//=============================================================================
void ObjCharacter::WallSlidingMove(D3DXVECTOR3& out, D3DXVECTOR3 normal)
{
	float velocityProjection = D3DXVec3Dot(&out, &normal);
	out -= velocityProjection * normal;
}


//=============================================================================
// �g����Z�b�g
//=============================================================================
void ObjCharacter::RipplesSet(ORDER_TAG tag, int ownerCou)
{
	if (m_RipplesSE == true)m_RipplesSE = false;//�g��̉���؂�

	//�g�䐶������
	m_RipplesPoint++;
	if (
		(m_RipplesPoint > m_RipplesSpan && m_Pos != m_OldPos) ||					//���������̏���
		(m_Pos == m_OldPos && m_RipplesPoint % 300 == 0 && m_RipplesDeleteNum <= 0)	//�����ĂȂ����̏���
		)
	{
		m_pGameWorld->CreateRipples(D3DXVECTOR3(m_OldPos.x + GetRandomInt(-m_RipplesRange, m_RipplesRange), 14.0f, m_OldPos.z + GetRandomInt(-m_RipplesRange, m_RipplesRange)), tag, ownerCou);
		m_RipplesPoint = 0;
		m_RipplesDeleteNum++;//�g��̐����v���X
		m_RipplesSE = true;//���ʉ���炷
	}

	//�g��폜����
	if (m_RipplesDeleteNum > 0 && m_RipplesDeleteCou <= 0)
	{
		m_RipplesDeleteCou = m_RipplesDeleteSpan;//�J�E���^�[���Z�b�g
	}
	if (m_RipplesDeleteNum > 0)//�g�䂪����������͏���ȏ゠��
	{
		m_RipplesDeleteCou--;

		if (m_RipplesDeleteCou <= 0 || m_RipplesDeleteNum > m_RipplesMax)
		{
			m_pGameWorld->DestroyObject(tag, ownerCou);
			m_RipplesDeleteNum--;
		}
	}
}
