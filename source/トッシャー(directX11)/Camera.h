/*==============================================================================

   カメラ [Camera.h]
														 Author : 学校配布、渡邉 修
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "Player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(0.0f)			// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(-25.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(15000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

//*****************************************************************************
// クラス定義
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

	D3DXVECTOR3	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// カメラの視点(位置)
	D3DXVECTOR3	m_At = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// カメラの注視点
	D3DXVECTOR3	m_Up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// カメラの上方向ベクトル
	D3DXVECTOR3	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// カメラの回転
	float		m_Len = 0.0f;			// カメラの視点と注視点の距離

	D3DXMATRIX	m_MtxView;		// ビューマトリックス(ワールド座標系から視点座標系（カメラ座標系）への変換)
	D3DXMATRIX	m_MtxInvView;	// ビューマトリックスの逆マトリックス(視点座標系（カメラ座標系）からワールド座標系への変換)
	D3DXMATRIX	m_MtxProjection;// プロジェクションマトリックス
	Player*		m_pPlayer = nullptr;
	float		m_ViewAngle = 0.0f;

	MODEL*		m_pJudgeSphereBlue = nullptr;

	float		m_ShakeRemain = 0.0f;
	float		m_ShakeLength = 0.0f;
	float		m_ShakeMagnitude = 0.0f;
};