//===================================================
//マップ制御(drawing.h)
//Auhor:渡邉 修	Date:2023.1.24
//===================================================
#ifndef _DRAWING_H_ //インクルードガード(二重定義の防止)
#define _DRAWING_H_

#define CONIOEX
#include "conioex.h"

//===================================================
//マクロ定義
//===================================================
#define DRAWING_WIDTHW_MAX (188)//右の描画範囲(101)
#define DRAWING_HEIGHT_MAX (47)	//下の描画範囲(30)
#define DRAWING_WIDTHW_MIN (0)	//左の描画範囲(0)
#define DRAWING_HEIGHT_MIN (0)	//上の描画範囲(0)
#define BACK_COLOR (WHITE)		//背景色
#define NOT_COLOR (72)			//指定色なし
#define ASCLl_COLOR (LIGHTGRAY)	//文字の色
#define ASCLl_BACK_COLOR (DARKGRAY)//文字の背景色
#define START_TOP_COLOR (LIGHTMAGENTA)	//スタートの上面
#define START_COLOR (MAGENTA)			//スタートの側面
#define GOAL_TOP_COLOR (LIGHTGREEN)		//ゴールの上面
#define GOAL_COLOR (GREEN)				//ゴールの側面

//===================================================
//構造体宣言
//===================================================
typedef struct//バッファ用構造体
{ 
	char moji[2];
	int color;
	int backColor;
}BUFFER;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeDrawing(void);
void UpdateDrawing(void);
void DrawDrawing(void);
void FinalizeDrawing(void);

void BufferSet(BUFFER* p, int x, int y, char* moji, int color, int backColor = NOT_COLOR);
void BufferPrint(BUFFER* p0, BUFFER* p1);
void PlayerMotionRightTurn(int startFrame);
void PlayerMotionRightRise(void);
void PlayerMotionRightFall(void);
void PlayerMotionLeftTurn(int startFrame);
void PlayerMotionLeftRise(void);
void PlayerMotionLeftFall(void);

#endif
