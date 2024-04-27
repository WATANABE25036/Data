//===================================================
//破片制御(parts.h)
//Auhor:渡邉 修	Date:2023.2.28
//===================================================
#ifndef _PARTS_H_ //インクルードガード
#define _PARTS_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_PARTS (300)
#define MAX_SPEED (0.5f)		//左右の最大スピード
#define DEC_X (0.9f)		//減速X(0.**で記入)
#define DEC_Y (0.9f)		//減速Y(0.**で記入)
#define ACC (0.02f)			//加速
#define JUMP_POWER (0.2f)	//ジャンプ力
#define JUMP_MAX (5.0f)		//ジャンプ高さ
#define PARTS_SPAWN_NUM (10)//プレイヤーがやられたときに出るパーツの数

//===================================================
//構造体宣言
//===================================================
typedef struct { //破片構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;	//xスピード
	float ySpeed;	//yスピード
	float gravity;	//重力
	bool ground;	//地面に面しているか
	bool minusBlock;	//マイナスブロックにくっついているかの判定
	bool isUse;		//使用フラグ
	bool moveBlockTrigger;
	bool xStackTrigger;
	bool yStackTrigger;
	int partsNum;	//いくつ目に作られた記録する
}PARTS;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializeParts(void);
void UpdateParts(void);
void DrawParts(void);
void FinalizeParts(void);

void SetParts(float px, float py);
void SetPartsFever(void);
PARTS* GetParts(void);
void allDeleteParts(void);

#endif