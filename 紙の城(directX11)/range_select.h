//===================================================
//マップ範囲選択(range_select.h)
//Auhor:渡邉 修	Date:2024.1.20
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define RANGE_SELECT_MAX			(1)//キャラクターの数
#define RANGE_SELECT_WIDTH		(DEFAULT_TILE_SIZE)//画像横幅
#define RANGE_SELECT_HEIGHT		(DEFAULT_TILE_SIZE)//画像縦高さ
#define RANGE_SELECT_SPEED		(4.0f)//移動速度

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct RANGE_SELECT {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	spd;	//スピード
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	int dir;	//向き
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitRangeSelect(void);
void UninitRangeSelect(void);
void UpdateRangeSelect(void);
void DrawRangeSelect(void);

void SetRangeSelect(D3DXVECTOR2 pos, int dir);
void DecisionRangeSelect();
