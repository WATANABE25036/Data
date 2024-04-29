//===================================================
//ブロック制御(block.h)
//Auhor:渡邉 修	Date:2023.2.7
//===================================================
#ifndef _BLOCK_H_ //インクルードガード
#define _BLOCK_H_

#include "drawing.h"

//===================================================
//マクロ定義
//===================================================
#define MAX_BLOCK (DRAWING_HEIGHT_MAX * DRAWING_WIDTHW_MAX)	//ブロックの数
#define MAX_BLOCK_WIDE (15)	//横のブロック数(101)
#define MAX_BLOCK_HEIGHT (6)	//縦のブロック数(30)
#define TURRET_RATE (2.5f)				//連射速度(低い = 速い)
#define TURRET_PRECISION (5)		//発射精度(低い = ばらつかない)
#define TURRET_BULLET_SPEED (1.0f)	//弾の速さ(高い = 速い)

//===================================================
//構造体宣言
//===================================================
typedef struct {	//ブロック構造体
	float xPos[MAX_BLOCK_WIDE];		//x座標
	float yPos[MAX_BLOCK_HEIGHT];		//y座標
	float oldXPos[MAX_BLOCK_WIDE];		//1フレーム前のx座標
	float oldYPos[MAX_BLOCK_HEIGHT];	//1フレーム前のy座標
	int mode;			//ブロックの種類
	bool untouch;		//触れられるか
	float speed;		//スピード
	int targetXS;		//このx座標に来たらX1に向かう(スタート地点)
	int targetYS;		//このy座標に来たらY1に向かう(スタート地点)
	int targetX1;		//このx座標に来たらX2に向かう
	int targetY1;		//このy座標に来たらY2に向かう
	int targetX2;		//このx座標に来たらX3に向かう
	int targetY2;		//このy座標に来たらY3に向かう
	int targetX3;		//このx座標に来たらXSに向かう
	int targetY3;		//このy座標に来たらYSに向かう
	int target;			//進むべきターゲット
	bool startTrigger;	//初めに一回だけ実行するとき用
	bool isUse;			//使用フラグ
	bool isUseWide[MAX_BLOCK_WIDE];		//横のブロックの使用フラグ
	bool isUseHeight[MAX_BLOCK_HEIGHT];	//縦のブロックの使用フラグ
	bool topBlock[MAX_BLOCK_HEIGHT];	//側面の見た目を変えるため
}BLOCK;

//===================================================
//列挙体宣言
//===================================================
typedef enum
{
	TARGET_START = 0,
	TARGET_1,
	TARGET_2,
	TARGET_3
}TARGET;

typedef enum
{
	AIR = 0,
	BLOCK_SIMPLE,
	BLOCK_MAGNET_PLUS,
	BLOCK_MAGNET_MINUS,
	BLOCK_TURRET_LEFT,
	BLOCK_TURRET_RIGHT,
	BLOCK_TURRET_TOP,
	BLOCK_TURRET_UNDER,
	BLOCK_START,
	BLOCK_GOAL
}BLOCK_MODE;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void FinalizeBlock(void);

void SetBlock(float px, float py, int mode = BLOCK_SIMPLE, bool topBlock = true, int wide = 1, int height = 1, float speed = 0.0f, int targetX1 = 0, int targetY1 = 0, int targetX2 = 0, int targetY2 = 0, int targetX3 = 0, int targetY3 = 0);
void allDeleteBlock(void);
BLOCK* GetBlock(void);

#endif
