/*==============================================================================

   �G�t�F�N�g(�r���{�[�h) [Effect.cpp]
														 Author : �n� �C
														 Date   : 2024/02/15
--------------------------------------------------------------------------------

==============================================================================*/
#include "Effect.h"
#include "Texture.h"

// �ÓI�����o�ϐ��̒�`
int Effect::m_sCou = 0;

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Effect::Effect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, EFFECT_PATTERN pattern, GameWorld* gameWorld, ORDER_TAG tag, int ownerCou)
	:Board(pos, rot, gameWorld)
{
	m_sCou++;
	m_OwnerNum = m_sCou;
	m_OwnerTag = tag;
	m_OwnerCou = ownerCou;
	m_Tag = "Effect";
	m_HitSize.x = 30.0f;//���̂Ŕ��肷��̂Ŕ��a

	//-------------------------------------------------------------//�G�t�F�N�g��ǉ������炱���ɒǉ�
	//�e�N�X�`���Ƒ傫���̐ݒ�
	switch (pattern)
	{
	case RIPPLES:
		//�\���傫���ݒ�
		m_Scl = D3DXVECTOR3(20.0f, 20.0f, 20.0f);
		//�e�N�X�`���̐ݒ�
		m_TexNo = LoadTexture((char*)"data/TEXTURE/Ripples.png");
		break;

	default:
		break;
	}
	//-------------------------------------------------------------//

	//���f���̓ǂݍ���
	Board::ModelLoad();
}

Effect::~Effect()
{

}

//=============================================================================
// ������
//=============================================================================
void Effect::Init()
{

}

void Effect::Update()
{
	Object::Update();
}
