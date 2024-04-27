//===================================================
//敵制御(enemy.h)
//Auhor:渡邉 修	Date::2023.1.17
//===================================================
#ifndef _ENEMY_H_ //インクルードガード
#define _ENEMY_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_ENEMY (100) //敵の数

//===================================================
//構造体宣言
//===================================================
typedef struct {	//敵構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;	//xスピード
	float ySpeed;	//yスピード
	int moveTime;	//移動時間
	bool isUse;		//使用フラグ
}ENEMY;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void FinalizeEnemy(void);

void SetEnemy(float px, float py, float sx = 0.0f, float sy = 0.0f);//初期引数を省略する書き方
ENEMY* GetEnemy(void);

#endif