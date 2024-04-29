//===================================================
//リザルトトマト(result_tomato.h)
//Auhor:渡邉 修	Date:2023.8.8
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define RESULT_TOMATO_WIDTH		(1824*0.5f)//画像横幅
#define RESULT_TOMATO_HEIGHT		(1240*0.5f)//画像縦高さ
#define RESULT_TOMATO_WIDTH_PATTERN	(4)//横アニメパターン数
#define RESULT_TOMATO_HEIGHT_PATTERN	(5)//縦アニメパターン数
#define RESULT_TOMATO_MAX			(1)//キャラクターの数
#define RESULT_TOMATO_FRAME_MAX	((RESULT_TOMATO_WIDTH_PATTERN * RESULT_TOMATO_HEIGHT_PATTERN) -1)//フレーム数
#define RESULT_TOMATO_FRAME_SPAN	(5)//アニメーションのスパン
#define RESULT_TOMATO_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitResultTomato(void);
void UpdateResultTomato(void);
void DrawResultTomato(void);
void UninitResultTomato(void);
