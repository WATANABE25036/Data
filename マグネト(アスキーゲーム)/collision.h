//===================================================
//当たり判定制御(collision.h)
//Auhor:渡邉 修	Date::2023.2.16
//===================================================
#ifndef _COLLISION_H_ //インクルードガード
#define _COLLISION_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_COLLISION_X (8)	//当たり判定の横文字数(判定の大きさ)
#define MAX_COLLISION_Y (4)	//当たり判定の縦文字数(判定の大きさ)

//===================================================
//構造体宣言
//===================================================
typedef struct {	//当たり判定構造体
	float xPos[MAX_COLLISION_X];	//x座標
	float yPos[MAX_COLLISION_Y];	//y座標
	float oldXPos[MAX_COLLISION_X];	//1フレーム前のx座標
	float oldYPos[MAX_COLLISION_Y];	//1フレーム前のy座標
	bool magSTrigger[MAX_COLLISION_Y][MAX_COLLISION_X];//S極磁場の影響の判定
	bool magNTrigger[MAX_COLLISION_Y][MAX_COLLISION_X];//N極磁場の影響の判定
	bool blockTrigger;				//シンプルブロック判定
}COLLISION;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeCollision(void);
void UpdateCollision(void);
void DrawCollision(void);
void FinalizeCollision(void);

COLLISION GetCollisionTopP(void);
COLLISION GetCollisionUnderP(void);
COLLISION GetCollisionRightP(void);
COLLISION GetCollisionLeftP(void);

#endif