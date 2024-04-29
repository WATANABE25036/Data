/*==============================================================================

   �{�[�h(���) [Board.cpp]
														 Author : �n� �C
														 Date   : 2024/02/15
--------------------------------------------------------------------------------

==============================================================================*/
#include "Board.h"
#include "Texture.h"
#include "Shadow.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Board::Board(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld)
	:Object(pos, rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), gameWorld)
{

}

Board::~Board()
{

}

//=============================================================================
// ������
//=============================================================================
void Board::Init()
{

}

//=============================================================================
// �I������
//=============================================================================
void Board::Uninit(void)
{
	if (m_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Board::Update(void)
{
	//���W�̍X�V
	m_Pos += m_Dir * m_Spd;
	
	//�e�̍��W���X�V����
	SetPositionShadow(m_Shadow, D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));
}

//=============================================================================
// �`�揈��
//=============================================================================
void Board::Draw(void)
{
	// ���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	D3DXMATRIX m_MtxView, mtxScale, mtxTranslate, mtxRot;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MtxWorld);

	//��]�ړ��s��쐬
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.x, m_Rot.y, m_Rot.z);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x,
		m_Pos.y,
		m_Pos.z);
	D3DXMatrixMultiply(&m_MtxWorld, &mtxRot, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&m_MtxWorld);

	// �}�e���A���ݒ�
	SetMaterial(m_Material);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(m_TexNo));

	// �|���S���̕`��
	GetDeviceContext()->Draw(4, 0);

	// ���C�e�B���O��L����
	SetLightEnable(true);

	// ���e�X�g�𖳌���
	SetAlphaTestEnable(false);
}

void Board::ModelLoad()
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);


	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = D3DXVECTOR3(-m_Scl.x / 2.0f, 0.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(-m_Scl.x / 2.0f, m_Scl.y, 0.0f);
		vertex[2].Position = D3DXVECTOR3(m_Scl.x / 2.0f, 0.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(m_Scl.x / 2.0f, m_Scl.y, 0.0f);

		// ���_�J���[�̐ݒ�
		vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	// �}�e���A��������
	ZeroMemory(&m_Material, sizeof(m_Material));
	m_Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}