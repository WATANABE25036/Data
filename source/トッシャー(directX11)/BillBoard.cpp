/*==============================================================================

   �r���{�[�h [BillBoard.cpp]
														 Author : �n� �C
														 Date   : 2023/11/30
--------------------------------------------------------------------------------

==============================================================================*/
#include "BillBoard.h"
#include "Texture.h"
#include "Shadow.h"

//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
BillBoard::BillBoard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Camera* camera)
	:Object(pos, rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f), gameWorld), m_pCamera(camera)
{

}

BillBoard::~BillBoard()
{

}

//=============================================================================
// ������
//=============================================================================
void BillBoard::Init()
{

}

//=============================================================================
// �I������
//=============================================================================
void BillBoard::Uninit(void)
{
	if (m_VertexBuffer != nullptr)
	{// ���_�o�b�t�@�̉��
		m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void BillBoard::Update(void)
{
		//���W�̍X�V
		m_Pos += m_Dir * m_Spd;

		//�e�̍��W���X�V����
		SetPositionShadow(m_Shadow, D3DXVECTOR3(m_Pos.x, 0.0f, m_Pos.z));
}

//=============================================================================
// �`�揈��
//=============================================================================
void BillBoard::Draw(void)
{
	// ���e�X�g��L����
	SetAlphaTestEnable(true);

	// ���C�e�B���O�𖳌�
	SetLightEnable(false);

	D3DXMATRIX m_MtxView, mtxScale, mtxTranslate;

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_MtxWorld);

			// �|���S���𐳖ʂɌ�����
#if 0
			// �r���[�}�g���b�N�X�̋t�s����擾
			m_MtxWorld = m_pCamera->GetMtxInvView();
			m_MtxWorld._41 = 0.0f;
			m_MtxWorld._42 = 0.0f;
			m_MtxWorld._43 = 0.0f;
#else
			// �r���[�}�g���b�N�X���擾
			D3DXMATRIX m_CameraMtxView = m_pCamera->GetMtxView();

			m_MtxWorld._11 = m_CameraMtxView._11;
			m_MtxWorld._12 = m_CameraMtxView._21;
			m_MtxWorld._13 = m_CameraMtxView._31;
			m_MtxWorld._21 = m_CameraMtxView._12;
			m_MtxWorld._22 = m_CameraMtxView._22;
			m_MtxWorld._23 = m_CameraMtxView._32;
			m_MtxWorld._31 = m_CameraMtxView._13;
			m_MtxWorld._32 = m_CameraMtxView._23;
			m_MtxWorld._33 = m_CameraMtxView._33;
#endif


			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, m_Pos.x,
				m_Pos.y,
				m_Pos.z);
			D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxTranslate);

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

void BillBoard::ModelLoad()
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