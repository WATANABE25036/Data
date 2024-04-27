//===================================================
//背景(bg.h)
//Auhor:渡邉 修	Date:2023.8.8
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define BG_WIDTH		(SCREEN_WIDTH)//画像横幅
#define BG_HEIGHT		(SCREEN_HEIGHT)//画像縦高さ
#define BG_WIDTH_PATTERN	(4)//横アニメパターン数
#define BG_HEIGHT_PATTERN	(4)//縦アニメパターン数
#define BG_MAX			(1)//キャラクターの数
#define BG_FRAME_MAX	((BG_WIDTH_PATTERN * BG_HEIGHT_PATTERN) -1)//フレーム数
#define BG_FRAME_SPAN	(32)//アニメーションのスパン
#define BG_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitBg(void);
void UpdateBg(void);
void DrawBg(void);
void UninitBg(void);
