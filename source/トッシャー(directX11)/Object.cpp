/*==============================================================================

   �\�����S��(���) [Object.cpp]
														 Author : �n� �C
														 Date   : 2023/12/12
--------------------------------------------------------------------------------

==============================================================================*/
#include "Object.h"
#include "BodyParts.h"
#include "Map.h"
#include "Collision.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Object::Object(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 hitSize, GameWorld* gameWorld)
	: m_Pos(pos), m_Rot(rot), m_HitSize(hitSize), m_pGameWorld(gameWorld)
{
	m_OwnerTag = ORDER_TAG::NONE;
}

Object::~Object()
{

}

//=============================================================================
// ������
//=============================================================================
//���ׂẴI�u�W�F�N�g�Ŏ��s
HRESULT Object::InitAll()
{
	if (this == nullptr)return E_POINTER;
	return S_OK;
}

void Object::Init()
{

}

//=============================================================================
// �C������
//=============================================================================
void Object::Uninit()
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Object::Update()
{
	if (m_ParentParts != nullptr)
	{
		m_ParentParts->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Object::Draw()
{
	if (m_ParentParts != nullptr)
	{
		//���f���X�V
		Collision collision;
		if (collision.CollisionBS(m_Pos, m_pGameWorld->GetPlayer()->GetPos(), 1500.0f, 1.0f))//�͈͓������\��
		{
			m_ParentParts->Draw();
		}
	}
}

//=============================================================================
// ���f���ǂݍ���
//=============================================================================
void Object::ModelLoad()
{
	//���f���̓ǂݍ���
	for (auto& it : m_ModelMap)
	{
		DX11_MODEL model;

		if (DoubleCheck((std::string)it.second.ModelAddress, model))//�ǂݍ��ݍς݂̃��f�����m�F
		{
			LoadModel(it.second.ModelAddress, &model, (std::string)it.second.ModelAddress);
		}

		it.second.Parts->SetModel(model);

		//��Ԑe�̃p�[�c�̃|�C���^�[���擾
		if (it.second.Parts->GetTopParent())
		{
			m_ParentParts = it.second.Parts;
		}

		m_Model = model;
	}
}
