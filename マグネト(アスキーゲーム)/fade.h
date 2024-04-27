//===================================================
//暗転制御(fade.h)
//Auhor:渡邉 修	Date:2023.2.25
//===================================================
#ifndef _FADE_H_ //インクルードガード
#define _FADE_H_

#include "drawing.h"

//===================================================
//マクロ定義
//===================================================
#define MAX_FADE ((DRAWING_WIDTHW_MAX / 2) * DRAWING_HEIGHT_MAX)	//暗転の数

//===================================================
//構造体宣言
//===================================================
typedef struct {	//暗転構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;		//スピード
	float ySpeed;		//スピード
	bool isUse;			//使用フラグ
}FADE;

//===================================================
//列挙体宣言
//===================================================

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeFade(void);
void UpdateFade(void);
void DrawFade(void);
void FinalizeFade(void);

void SetFadeOut(void);
void SetFadeIn(void);
bool GetBlacKOutTrigger(void);

FADE* GetFadeLeft(void);
FADE* GetFadeRight(void);

#endif
