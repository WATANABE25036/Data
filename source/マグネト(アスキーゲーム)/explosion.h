//===================================================
//爆発アニメーション制御(explosion.h)
//Auhor:渡邉 修	Date::2023.1.19
//===================================================
#ifndef _EXPLOSION_H_ //インクルードガード
#define _EXPLOSION_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_EXPLOSION (100)					//爆発アニメーションの数
#define ANIMATION_FRAME_EXPLOSION (2)		//1アニメの表示フレーム
#define ANIMATION_FRAME_MAX_EXPLOSION (4)	//アニメーションの枚数

//===================================================
//構造体宣言
//===================================================
typedef struct {	//爆発アニメーション構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;	//xスピード
	float ySpeed;	//yスピード
	int frameCut;	//アニメーションカウント
	bool isUse;		//使用フラグ
}EXPLOSION;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void FinalizeExplosion(void);

void SetExplosion(float px, float py, float sx = 0.0f, float sy = 0.0f);//初期引数を省略する書き方
EXPLOSION* GetExplosion(void);

#endif