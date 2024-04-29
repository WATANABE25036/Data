/*==============================================================================

   �G�l�~�[(�h��) [Enemy.cpp]
														 Author : �n� �C
														 Date   : 2024/01/11
--------------------------------------------------------------------------------

==============================================================================*/
#include "Enemy.h"
#include "Shadow.h"
#include "Library.h"
#include "GameWorld.h"
#include "Map.h"

// �ÓI�����o�ϐ��̒�`
int Enemy::m_sCou = 0;

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Enemy::Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Map* map)
	: ObjCharacter(pos, rot, gameWorld, map)
{
	m_sCou++;
	m_OwnerNum = m_sCou;
	m_OwnerTag = ORDER_TAG::ENEMY;
	m_Tag = "Enemy";
	m_HitSize = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_TargetPos = m_Pos;

	//���f���̐ݒ�
	MODEL model = { (char*)"data/MODEL/EnemyS.obj", new BodyParts(m_Pos, m_Rot, m_Scl, this ,true) };
	m_ModelMap["Parts"] = model;

	//���f���̓ǂݍ���
	Object::ModelLoad();

	m_Spd = 1.5f;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Enemy::~Enemy()
{

}

//=============================================================================
// ����������
//=============================================================================
void Enemy::Init(void)
{


	//������P�ʃx�N�g��������
	D3DXVec3Normalize(&m_Dir, &m_Dir);

	//�e�̃Z�b�g
	m_Shadow = SetShadow(D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z), 80.0f);
}

//=============================================================================
// �I������
//=============================================================================
void Enemy::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Enemy::Update(void)
{
	m_ArrayPos = m_pMap->GetArrayPos(m_Pos);//�}�b�v�̍s��ł̈ʒu

	//-------------------------------------------------------------
	//���������^�C���֌�����
	//-------------------------------------------------------------
	TILE tile = m_pMap->GetTile(m_Pos);
	//�����̂���Ƃ��낪�͈͓��Ȃ�
	if (tile.TileState == HEAR_SOUND)
	{
		m_TargetPos = m_pGameWorld->GetPlayer()->GetPos();
	}
	double pdr = PointDirectionRadian(m_Pos.x, m_Pos.z, m_TargetPos.x, m_TargetPos.z);

	D3DXVECTOR2 cv = CalculateVector(double(m_Spd), pdr);

	if (!m_Collision.CollisionBB(m_Pos, m_TargetPos, m_HitSize, D3DXVECTOR3(20,20,20)))
	{
		m_Move.x = cv.x;
		m_Move.z = cv.y;
	}
	else
	{
		m_Move *= 0.5f;
	}

	//-------------------------------------------------------------
	//�����蔻��
	//-------------------------------------------------------------
	HitJudge();

	//-------------------------------------------------------------
	//�ړ�
	//-------------------------------------------------------------
	m_Pos += m_Move * m_Spd;

	//-------------------------------------------------------------
	//�g��\��
	//-------------------------------------------------------------
	RipplesSet(ORDER_TAG::ENEMY, m_OwnerNum);

	//�e�̍��W���X�V����
	SetPositionShadow(m_Shadow, D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));

	//���f���X�V
	Object::Update();

	//�O�|�W�V�����X�V
	m_OldPos = m_Pos;
	m_OldArrayPos = m_ArrayPos;

#ifdef _DEBUG	// �f�o�b�O����\������

#endif
}

