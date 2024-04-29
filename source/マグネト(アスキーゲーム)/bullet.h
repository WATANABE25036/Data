//===================================================
//弾制御(bullet.h)
//Auhor:渡邉 修	Date:2023.1.16
//===================================================
#ifndef _BULLET_H_ //インクルードガード
#define _BULLET_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_BULLET (200) //弾の数

//===================================================
//構造体宣言
//===================================================
typedef struct {	//弾構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;	//xスピード
	float ySpeed;	//yスピード
	bool isUse;		//使用フラグ
}BULLET;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void FinalizeBullet(void);

void SetBullet(float px, float py, float sx, float sy);
BULLET* GetBullet(void);

#endif