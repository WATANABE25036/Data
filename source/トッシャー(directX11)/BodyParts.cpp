/*==============================================================================

   �y�A�����g���� [BodyParts.cpp]
														 Author : �w�Z�z�z�A�n� �C
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#include "BodyParts.h"
#include "Input.h"
#include "Polyline.h"
#include "Renderer.h"

BodyParts::BodyParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, Object* obj, bool topParent)
	: m_Pos(pos), m_Rot(rot), m_Scl(scl), m_TopParent(topParent), m_Obj(obj)
{

}

BodyParts::~BodyParts()
{
	//obj���f���̉��
	UnloadModel(&m_Model);
}

void BodyParts::Uninit()
{

}

void BodyParts::Update()
{
	//�e�����X�V
	if (m_TopParent)
	{
		//�I�u�W�F�N�g�N���X�ƈ�Ԑe�p�[�c�̒l�𓯂��ɂ���
		m_Pos = m_Obj->GetPos();
		m_Rot = m_Obj->GetRot();
	}
}

void BodyParts::Draw()
{
		//���C�e�B���OOFF
		//SetLightEnable(FALSE);

		D3DXMATRIX RootMatrix;
		D3DXMatrixIdentity(&RootMatrix); //���[�g�s��(�P�ʍs��)

		//�y�A�����g���f���̕`��
		Parent(RootMatrix);//��Ԑe���f���̐e���[���h�s��͒P�ʍs��ɂ��Ă���

		//���C�e�B���OON
		//SetLightEnable(TRUE);
}

void BodyParts::Parent(D3DXMATRIX mtx)
{
	//�����̃��[���h�s����쐬����
	D3DXMATRIX mtxScl, mtxRot, mtxTranslation;

	//���[���h�s���P�ʍs��ŏ�����
	D3DXMatrixIdentity(&m_MtxWorld);

	//�X�P�[�����O�s��쐬
	D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);

	//��]�ړ��s��쐬
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.x, m_Rot.y, m_Rot.z);

	//���s�ړ��s��쐬
	D3DXMatrixTranslation(&mtxTranslation, m_Pos.x, m_Pos.y, m_Pos.z);

	//���[���h�s��̍쐬
	m_MtxWorld *= mtxScl;
	m_MtxWorld *= mtxRot;
	m_MtxWorld *= mtxTranslation;

	m_MtxWorld = m_MtxWorld * mtx;

	if (m_pChild)//�q�����邩?
	{
		m_pChild->Parent(m_MtxWorld);//�����̃��[���h�s���n���Ďq��������
	}
	if (m_pBros)//�Z�킪���邩?
	{
		m_pBros->Parent(mtx);//�����̐e�̃��[���h�s���n���ČZ�������
	}

	//�s��̃Z�b�g
	SetWorldMatrix(&m_MtxWorld);

	//���f����`�悷��
	DrawModel(m_Model);
}

D3DXVECTOR3 BodyParts::GetGlobalPos() const
{
	if (m_TopParent)return m_Obj->GetPos();//��Ԑe�̏ꍇ���������_
	D3DXVECTOR3 globalPos = D3DXVECTOR3(m_MtxWorld._41, m_MtxWorld._42, m_MtxWorld._43);
	return globalPos;
}

