//===================================================
//プレイヤー(player.h)
//Auhor:渡邉 修	Date:2023.7.6
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PLAYER_WIDTH		(27.0f * 4.0f)//画像横幅(元画像27ピクセルの画像を4倍にして使用)
#define PLAYER_HEIGHT		(27.0f * 4.0f)//画像縦高さ
#define PLAYER_WIDTH_PATTERN	(10)//横アニメパターン数
#define PLAYER_HEIGHT_PATTERN	(1)//縦アニメパターン数
#define PLAYER_MAX			(1)//キャラクターの数
#define PLAYER_FRAME_MAX	((PLAYER_WIDTH_PATTERN * PLAYER_HEIGHT_PATTERN) -1)//フレーム数
#define PLAYER_FRAME_SPAN	(8)//アニメーションのスパン
#define PLAYER_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）
#define PLAYER_SPEED		(1.0f)//プレイヤーの移動速度
#define PLAYER_WIDTH_MAX	(PLAYER_WIDTH * 4)
#define PLAYER_HEIGHT_MAX	(PLAYER_HEIGHT * 4)
#define PLAYER_BASE_ZOOM_RATE	(0.01f)	//基本の手前に来る速さ
#define PLAYER_ADD_ZOOM_RATE	(8.5f)	//手前に来た時の速さの増加率
#define PLAYER_DIS_SPEED_RATE	(10)	//距離によるスピードの増減
#define PLAYER_HET_RANGE				(-0.3f)	//壁と実際に当たる距離(マイナスが大きいほどぶつかるのが遅くなる)
#define PLAYER_DEFAULT_DIS		(1.5f)	//通常時のプレイヤーの奥行
#define PLAYER_DEFAULT_DIS_MOVE_SPEED	(0.01f)	//PLAYER_DEFAULT_DISに移動する速さ
#define PLAYER_START_DIS	(3.0f)	//一番最初のトマトの奥行
#define RANDOM_MOVE_SPAN	(5)	//落下中のプルプルする速さ
#define PLAYER_MOVE_SE_SPZN	(10)	//SEを鳴らすスパン
#define PLAYER_HET_SIZE		(0.3f)	//ヒットボックスにこの値を掛ける

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct PLAYER {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		oldPos;	//前フレームの位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	int				dir;	//向き
	bool			use;	//使用中フラグ
	D3DXVECTOR2		size;	//サイズ
	float			dis;	//遠近距離
	int				BufferIndex;//リングバッファの参照インデクス
	D3DXVECTOR2		initSize;	//初期サイズ
	float			disRate;	//0(最奥)～1(最前)
	float			speed;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer();
