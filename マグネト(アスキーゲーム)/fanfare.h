//===================================================
//ファンファーレ制御(fanfare.h)
//Auhor:渡邉 修	Date:2023.1.16
//===================================================
#ifndef _FANFARE_H_ //インクルードガード
#define _FANFARE_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_FANFARE (100) //ファンファーレの数

//===================================================
//構造体宣言
//===================================================
typedef struct {	//ファンファーレ構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;	//xスピード
	float ySpeed;	//yスピード
	bool isUse;		//使用フラグ
}FANFARE;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeFanfare(void);
void UpdateFanfare(void);
void DrawFanfare(void);
void FinalizeFanfare(void);

void SetFanfare(float px, float py, float sx, float sy);
void SetFanfareFever(void);
FANFARE* GetFanfare(void);

#endif