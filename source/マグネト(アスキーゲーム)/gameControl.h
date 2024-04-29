//===================================================
//ゲーム制御[gameControl.h]
//Author:渡邉 修	Date:2023.1.31
//===================================================
#ifndef _GAME_CONTROL_H_ //インクルードガード(二重定義の防止)
#define _GAME_CONTROL_H_
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//マクロ定義
//===================================================
#define GRAVITY (0.0045f)	//重力(0で無重力)
#define DEFAULT_STAGE_SETTING (-1)		//ゲーム開始時の設定
#define FIRST_STAGE (STAGE1)		//最初に読み込むステージ
#define FINAL_STAGE (STAGE15)		//最後のステージ
#define S (8)
#define G (9)

//===================================================
//列挙体宣言
//===================================================
typedef enum
{
	STAGE1 = 1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	STAGE6,
	STAGE7,
	STAGE8,
	STAGE9,
	STAGE10,
	STAGE11,
	STAGE12,
	STAGE13,
	STAGE14,
	STAGE15,
}STAGE;

//===================================================
//構造体宣言
//===================================================
//typedef struct { //ゲームコントロール構造体
//	char stage1[DRAWING_HEIGHT_MAX][DRAWING_WIDTHW_MAX];
//}GAME_CONTROL;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeGameControl(void);
void UpdateGameControl(void);
void DrawGameControl(void);
void FinalizeGameControl(void);

int GetStageNum(void);
bool GetInstructions(void);
void SetStage(char stage[DRAWING_HEIGHT_MAX][DRAWING_WIDTHW_MAX]);
//GAME_CONTROL GetGameControl(void);

#endif