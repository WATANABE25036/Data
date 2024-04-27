//===================================================
//プレイヤー制御(player.h)
//Auhor:渡邉 修	Date:2023.1.13
//===================================================
#ifndef _PLAYER_H_ //インクルードガード(二重定義の防止)
#define _PLAYER_H_

//===================================================
//マクロ定義
//===================================================
#define MAX_SPEED (0.5f)		//左右の最大スピード
#define DEC_X (0.9f)		//減速X(0.**で記入)
#define DEC_Y (0.9f)		//減速Y(0.**で記入)
#define ACC (0.02f)			//加速
#define JUMP_POWER (0.2f)	//ジャンプ力
#define JUMP_MAX (5.0f)		//ジャンプ高さ
#define MINUS_JUMP_POWER (JUMP_POWER / 3)	//マイナスマグネットの隣の時の移動速度
#define RIGHT_FACING (1)	//右向き
#define LEFT_FACING (-1)	//左向き
#define UP_FACING (1)		//上向き
#define DOWN_FACING (-1)	//下向き
#define MOTIONFRAME_MAX_PLAYER_WALK (4)	//歩きモーションの絵の枚数
#define MOTIONFRAME_PLAYER_WALK (3)		//歩きモーション速度(一枚当たりの表示時間)
#define MOTIONFRAME_MAX_PLAYER_IDLE (40)//待機モーションの絵の枚数
#define MOTIONFRAME_PLAYER_IDLE (5)		//待機モーション速度(一枚当たりの表示時間)
#define MOTIONFRAME_MAX_PLAYER_APPEAL (4)//アピールモーションの絵の枚数
#define MOTIONFRAME_PLAYER_APPEAL (20)	//アピールモーション速度(一枚当たりの表示時間)
#define RESPAWN_TIMER (60 * 2)			//リスポーンまでの待機時間
#define REMAIN (10)	//残機

//===================================================
//列挙体宣言
//===================================================
typedef enum
{
	RISE = 0,		//上昇中
	FALL,			//下降中
	IDLE,			//動いていない
	WALK,			//歩く
	APPEAL,			//ゴールした
	MAGNET_S_TOP,	//くっついている
	MAGNET_S_RIGHT,	//くっついている
	MAGNET_S_LEFT	//くっついている
}STATE;

//===================================================
//構造体宣言
//===================================================
typedef struct { //プレイヤー構造体
	float xPos;		//x座標
	float yPos;		//y座標
	float oldXPos;	//1フレーム前のx座標
	float oldYPos;	//1フレーム前のy座標
	float xSpeed;	//xスピード
	float ySpeed;	//yスピード
	int facing;		//左右の向き
	int upDownfacing;	//磁石にくっついてるときの上下の向き
	int state;		//状態
	int oldState;	//1フレーム前の状態
	int chargCnt;	//チャージショット用カウンター
	float gravity;	//重力
	bool dead;		//死亡判定
	int stageNum;	//現在のステージナンバー
	bool goal;		//ゴール判定
	int motionCnt;	//モーションのカウント
	bool minusBlock;//マイナスブロックにくっついているかの判定
	bool plusBlock;//プラスブロックの影響を受けているかの判定
	bool isUse;		//使用フラグ
	bool respawn;	//リスポーンできるかどうか
	bool inportSwitch;	//マグネットの切り替え操作管理
	int remain;		//残機
}PLAYER;

//===================================================
//プロトタイプ宣言
//===================================================
void InitializePlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void FinalizePlayer(void);

void SetPlayer(float px = 1.0f, float py = 1.0f);
PLAYER GetPlayer(void);
#endif