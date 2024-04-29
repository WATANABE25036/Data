/*==============================================================================

   �J���� [Camera.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Camera.h"
#include "Input.h"
#include "Library.h"
 
//=============================================================================
// �R���X�g���N�^ / �f�X�g���N�^
//=============================================================================
Camera::Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Player* player, GameWorld* gameWorld)
	: Object(pos, rot, D3DXVECTOR3(1.0f, 1.0f, 1.0f), gameWorld), m_pPlayer(player)
{

}

Camera::~Camera()
{

}

//=============================================================================
// ������
//=============================================================================
void Camera::Init (void)
{
	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = m_Pos.x - m_At.x;
	vz = m_Pos.z - m_At.z;
	m_Len = sqrtf(vx * vx + vz * vz);
}

//=============================================================================
// �I������
//=============================================================================
void Camera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void Camera::Update(void)
{

}

//=============================================================================
// �Z�b�g�X�V
//=============================================================================
// �J�����̎��_�ƒ����_���Z�b�g
void Camera::SetCameraAT()
{
	D3DXVECTOR3 bodyPos = m_pPlayer->GetBody()->GetPos();
	D3DXVECTOR3 bodyRot = m_pPlayer->GetBody()->GetRot();
	D3DXVECTOR3 headPos = m_pPlayer->GetHead()->GetPos();
	D3DXVECTOR3 headRot = m_pPlayer->GetHead()->GetRot();
	
	m_Pos = bodyPos /*+ headPos*/;
	m_Rot.x = headRot.y;
	m_Rot.y = bodyRot.x;

	//�J������h�炷
	if (m_ShakeRemain != 0)
	{
		m_Pos.x += GetRandomFloat(-m_ShakeRemain, m_ShakeRemain);
		m_Pos.z += GetRandomFloat(-m_ShakeRemain, m_ShakeRemain);

		m_ShakeRemain = max(0, m_ShakeRemain - ((1 / m_ShakeLength) * m_ShakeMagnitude));//max: 2�̒l����傫���ق���Ԃ�
	}

	// ��]�s����쐬���Ē����_���X�V
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_Rot.y, m_Rot.x, 0.0f);
	D3DXVECTOR3 lookDirection(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformCoord(&m_At, &lookDirection, &rotationMatrix);
	m_At += m_Pos;

	//�v���C���[�̑����ɂ���Ď���p��ς���
	m_ViewAngle = m_pPlayer->GetSpd() * 0.01f;
}

void Camera::SetCamera(void)
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&m_MtxView, &m_Pos, &m_At, &m_Up);
	SetViewMatrix(&m_MtxView);

	float det;
	D3DXMatrixInverse(&m_MtxInvView, &det, &m_MtxView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_MtxProjection, 1.0f + m_ViewAngle, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);
	SetProjectionMatrix(&m_MtxProjection);
}

//=============================================================================
// �V�F�C�N [����]shakeMagnitude: �h�炷�傫��, shakeLength: �h�炷����
//=============================================================================
void Camera::Shake(float shakeMagnitude, float shakeLength)
{
	m_ShakeRemain = shakeMagnitude;
	m_ShakeMagnitude = shakeMagnitude;
	m_ShakeLength = shakeLength;
}