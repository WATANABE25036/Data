/*==============================================================================

   レンダリング処理 [Renderer.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Main.h"

//*********************************************************
// マクロ定義
//*********************************************************
#define LIGHT_MAX		(10)

enum LIGHT_TYPE
{
	LIGHT_TYPE_NONE,		//ライト無し
	LIGHT_TYPE_DIRECTIONAL,	//ディレクショナルライト
	LIGHT_TYPE_POINT,		//ポイントライト

	LIGHT_TYPE_NUM
};

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//ブレンド無し
	BLEND_MODE_ALPHABLEND,	//αブレンド
	BLEND_MODE_ADD,			//加算ブレンド
	BLEND_MODE_SUBTRACT,	//減算ブレンド

	BLEDD_MODE_NUM
};

enum CULL_MODE
{
	CULL_MODE_NONE,			//カリング無し
	CULL_MODE_FRONT,		//表のポリゴンを描画しない(CW)
	CULL_MODE_BACK,			//裏のポリゴンを描画しない(CCW)

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
// 構造体
//*********************************************************

// 頂点構造体
struct VERTEX_3D
{
	D3DXVECTOR3 Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//座標
    D3DXVECTOR3 Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//法線
    D3DXCOLOR  Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//頂点カラー
    D3DXVECTOR2 TexCoord = D3DXVECTOR2(0.0f, 0.0f);			//UV値
};

// マテリアル構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXCOLOR	Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXCOLOR	Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	D3DXCOLOR	Emission = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	float		Shininess = 0.0f;
	int			noTexSampling = 0;	
	float		Dummy[2] = {0};	//16byte境界用(構造体のサイズを16バイトの倍数にする必要がある)
};

// ライト構造体
struct LIGHT {
	D3DXVECTOR4 Direction = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);// ライトの方向
	D3DXVECTOR4 Position = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);	// ライトの位置
	D3DXCOLOR	Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 拡散光の色
	D3DXCOLOR   Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 環境光の色
	float		Attenuation = 0.0f;	// 減衰率
	int			Type = 0;			// ライト種別
	int			Enable = 0;			// 有効フラグ
	float		Dummy = 0.0f;		//16byte境界用(構造体のサイズを16バイトの倍数にする必要がある)
};

//*****************************************************************************
// プロトタイプ宣言
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

