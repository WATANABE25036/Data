//===================================================
//タイトル背景(title_background.h)
//Auhor:渡邉 修	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define TITLE_BACKGROUND_WIDTH		(1920)//画像横幅
#define TITLE_BACKGROUND_HEIGHT		(1080)//画像縦高さ
#define TITLE_BACKGROUND_WIDTH_PATTERN	(10)//横アニメパターン数
#define TITLE_BACKGROUND_HEIGHT_PATTERN	(15)//縦アニメパターン数
#define TITLE_BACKGROUND_MAX			(1)//キャラクターの数
#define TITLE_BACKGROUND_FRAME_MAX	(145)//フレーム数
#define TITLE_BACKGROUND_FRAME_SPAN	(5)//アニメーションのスパン
#define TITLE_BACKGROUND_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitTitleBackground(void);
void UpdateTitleBackground(void);
void DrawTitleBackground(void);
void UninitTitleBackground(void);
