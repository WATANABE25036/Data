//===================================================
//障壁(barrier.h)
//Auhor:渡邉 修	Date:2023.7.11
//===================================================
#pragma once
#include <string>
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define BARRIER_WIDTH		(16)	//画像横幅
#define BARRIER_HEIGHT		(16)	//画像縦高さ
#define BARRIER_MAX			(200)		//キャラクターの数
#define BARRIER_FRAME_SPAN	(5)		//キャラクター間の間隔（フレーム）
#define BARRIER_WIDTH_MAX	(SCREEN_WIDTH + 700)/4
#define BARRIER_HEIGHT_MAX	(SCREEN_HEIGHT + 700)/4
#define BARRIER_DEFAULT_ALPHA	(0.85f)

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct BARRIER {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		oldPos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXVECTOR2		speed;	//速度
	D3DXCOLOR		color;	//頂点カラー
	bool			use;	//使用中フラグ
	D3DXVECTOR2		size;	//サイズ
	D3DXVECTOR2		oldSize;	//サイズ
	float			dis;	//遠近距離
	float			disRate;
	int				g_num;
	float			rot;	//角度
	D3DXVECTOR2		initSize;//初期サイズ
	D3DXVECTOR2		initPos;//初期ポジション
	D3DXVECTOR2		maxSize;//最も手前に来た時の大きさ
	float			rotSpeed;//回転速度
	D3DXVECTOR2		adjVel;	//プレイヤーの位置に対するベクトル
};

//---------------------------------------------------
//列挙体宣言
//---------------------------------------------------
typedef enum
{
	BARRIER_COLOR_RANDOM,
	BARRIER_COLOR_RED,
	BARRIER_COLOR_GREEN,
	BARRIER_COLOR_BLUE,
	BARRIER_COLOR_YELLOW,
	BARRIER_COLOR_MAGENTA,
	BARRIER_COLOR_CYAN,
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitBarrier();
void UninitBarrier();
void UpdateBarrier();
void DrawBarrier(int g_num);

BARRIER* GetBarrier();
void SetBarrier(int wallNum, float posX, float posY, float sizeX, float sizeY, float rot = 0.0f, int color = BARRIER_COLOR_RANDOM, float speedX = 0.0f, float speedY = 0.0f, float rotSpeed = 0.0f);
void StopBarrier();