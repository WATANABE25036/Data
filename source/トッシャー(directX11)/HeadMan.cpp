/*==============================================================================

   �w�b�h�}�� [HeadMan.cpp]
														 Author : �n� �C
														 Date   : 2024/01/15
--------------------------------------------------------------------------------

==============================================================================*/
#include "HeadMan.h"
#include "Texture.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
HeadMan::HeadMan(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, CAMERA* camera)
	:BillBoard(pos, rot, gameWorld, camera)
{
	m_Tag = "HeadMan";

	//�\���傫���ݒ�
	m_Scl = D3DXVECTOR3(300.0f, 500.0f, 0.0f);

	//�e�N�X�`���̐ݒ�
	m_TexNo = LoadTexture((char*)"data/TEXTURE/HeadMan.png");

	//���f���̓ǂݍ���
	BillBoard::ModelLoad();
}

HeadMan::~HeadMan()
{


}

//=============================================================================
// ������
//=============================================================================
HRESULT HeadMan::Init()
{

	
	return E_NOTIMPL;
}

void HeadMan::Update()
{
	Object::Update();
}
