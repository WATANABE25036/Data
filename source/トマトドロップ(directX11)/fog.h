//===================================================
//霧(fog.h)
//Auhor:渡邉 修	Date:2023.8.7
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define FOG_WIDTH		(SCREEN_WIDTH)	//画像横幅
#define FOG_HEIGHT		(SCREEN_HEIGHT)	//画像縦高さ
#define FOG_MAX			(10)	//画像縦高さ

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct FOG {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXCOLOR		color;	//頂点カラー
	bool			use;	//使用中フラグ
	D3DXVECTOR2		size;	//サイズ
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitFog();
void UninitFog();
void UpdateFog();
void DrawFog();

void SetFog();
