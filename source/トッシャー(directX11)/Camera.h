/*==============================================================================

   �J���� [Camera.h]
														 Author : �w�Z�z�z�A�n� �C
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(0.0f)			// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-25.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(15000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Camera : public Object
{
public:
	Camera(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Player* player, GameWorld* gameWorld);
	~Camera();

	void Init() override;
	void Uninit() override;
	void Update() override;

	void Shake(float shakeMagnitude, float shakeLength);

	void SetCamera();
	void SetCameraAT();
	D3DXMATRIX GetMtxView() const { return m_MtxView; }
	D3DXMATRIX GetMtxInvView() const { return m_MtxInvView; }

private:
	BodyParts*	m_pBodyParts = nullptr;

	D3DXVECTOR3	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �J�����̎��_(�ʒu)
	D3DXVECTOR3	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �J�����̒����_
	D3DXVECTOR3	m_Up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �J�����̏�����x�N�g��
	D3DXVECTOR3	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �J�����̉�]
	float		m_Len = 0.0f;			// �J�����̎��_�ƒ����_�̋���

	D3DXMATRIX	m_MtxView;		// �r���[�}�g���b�N�X(���[���h���W�n���王�_���W�n�i�J�������W�n�j�ւ̕ϊ�)
	D3DXMATRIX	m_MtxInvView;	// �r���[�}�g���b�N�X�̋t�}�g���b�N�X(���_���W�n�i�J�������W�n�j���烏�[���h���W�n�ւ̕ϊ�)
	D3DXMATRIX	m_MtxProjection;// �v���W�F�N�V�����}�g���b�N�X
	Player*		m_pPlayer = nullptr;
	float		m_ViewAngle = 0.0f;

	MODEL*		m_pJudgeSphereBlue = nullptr;

	float		m_ShakeRemain = 0.0f;
	float		m_ShakeLength = 0.0f;
	float		m_ShakeMagnitude = 0.0f;
};