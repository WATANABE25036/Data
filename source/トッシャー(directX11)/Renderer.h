/*==============================================================================

   �����_�����O���� [Renderer.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Main.h"

//*********************************************************
// �}�N����`
//*********************************************************
#define LIGHT_MAX		(10)

enum LIGHT_TYPE
{
	LIGHT_TYPE_NONE,		//���C�g����
	LIGHT_TYPE_DIRECTIONAL,	//�f�B���N�V���i�����C�g
	LIGHT_TYPE_POINT,		//�|�C���g���C�g

	LIGHT_TYPE_NUM
};

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//�u�����h����
	BLEND_MODE_ALPHABLEND,	//���u�����h
	BLEND_MODE_ADD,			//���Z�u�����h
	BLEND_MODE_SUBTRACT,	//���Z�u�����h

	BLEDD_MODE_NUM
};

enum CULL_MODE
{
	CULL_MODE_NONE,			//�J�����O����
	CULL_MODE_FRONT,		//�\�̃|���S����`�悵�Ȃ�(CW)
	CULL_MODE_BACK,			//���̃|���S����`�悵�Ȃ�(CCW)

	CULL_MODE_NUM
};

enum ADDRESS_MODE
{
	ADDRESS_MODE_WRAP,
	ADDRESS_MODE_MIRROR,
	ADDRESS_MODE_CLAMP,
	ADDRESS_MODE_BORDER,

	ADDRESS_MODE_NUM
};

enum FILTER_MODE
{
	FILTER_MODE_POINT,
	FILTER_MODE_LINEAR,
	FILTER_MODE_ANISOTROPIC,

	FILTER_MODE_NUM
};

//*********************************************************
// �\����
//*********************************************************

// ���_�\����
struct VERTEX_3D
{
	D3DXVECTOR3 Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���W
    D3DXVECTOR3 Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�@��
    D3DXCOLOR  Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//���_�J���[
    D3DXVECTOR2 TexCoord = D3DXVECTOR2(0.0f, 0.0f);			//UV�l
};

// �}�e���A���\����
struct MATERIAL
{
	D3DXCOLOR	Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXCOLOR	Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXCOLOR	Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXCOLOR	Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	float		Shininess = 0.0f;
	int			noTexSampling = 0;	
	float		Dummy[2] = {0};	//16byte���E�p(�\���̂̃T�C�Y��16�o�C�g�̔{���ɂ���K�v������)
};

// ���C�g�\����
struct LIGHT {
	D3DXVECTOR4 Direction = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);// ���C�g�̕���
	D3DXVECTOR4 Position = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);	// ���C�g�̈ʒu
	D3DXCOLOR	Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �g�U���̐F
	D3DXCOLOR   Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �����̐F
	float		Attenuation = 0.0f;	// ������
	int			Type = 0;			// ���C�g���
	int			Enable = 0;			// �L���t���O
	float		Dummy = 0.0f;		//16byte���E�p(�\���̂̃T�C�Y��16�o�C�g�̔{���ɂ���K�v������)
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);

void Clear(void);
void Present(void);

ID3D11Device *GetDevice( void );
ID3D11DeviceContext *GetDeviceContext( void );

void SetDepthEnable( bool Enable );
void SetBlendState(BLEND_MODE bm);
void SetCullingMode(CULL_MODE cm);
void SetLightEnable(BOOL flag);
void SetAlphaTestEnable(BOOL flag);
void SetSamplerState(FILTER_MODE fm, ADDRESS_MODE am);
void SetSamplerBorderColor(D3DXCOLOR col);

void SetWorldViewProjection2D( void );
void SetWorldMatrix( D3DXMATRIX *WorldMatrix );
void SetViewMatrix( D3DXMATRIX *ViewMatrix );
void SetProjectionMatrix( D3DXMATRIX *ProjectionMatrix );

void SetMaterial( MATERIAL Material );
void SetLight(int index, LIGHT *pLight);
void DebugTextOut(const char* text, int x, int y);

