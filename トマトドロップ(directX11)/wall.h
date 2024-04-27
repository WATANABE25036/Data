//===================================================
//壁(wall.h)
//Auhor:渡邉 修	Date:2023.7.6
//===================================================
#pragma once
#include <string>
#include "main.h"
#include "renderer.h"
#include "barrier.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define WALL_WIDTH		(768)	//画像横幅
#define WALL_HEIGHT		(432)	//画像縦高さ
#define WALL_MAX		(300)	//キャラクターの数
#define WALL_FRAME_SPAN	(5)		//キャラクター間の間隔（フレーム）
#define WALL_SPEED		(0.1f)	//移動速度
#define WALL_SET_SPEED	(5)		//次の壁を出すスピード(-のほうがスピード速い)
#define WALL_BARRIER_SET_SPEED	(0)	//障壁設置スピード補正(-のほうがスピード速い)
#define WALL_ZOOM_SPEED	(0.01)	//手前に来る速さ
#define WALL_NORMAL		(-1)	//壁の種類(なし)
#define WALL_BARRIER	(0)		//壁の種類(障壁)
#define WALL_WIDTH_MAX	(SCREEN_WIDTH + 700)
#define WALL_HEIGHT_MAX	(SCREEN_HEIGHT + 700)
#define BASE_ZOOM_RATE	(0.01f)	//基本の手前に来る速さ
#define ADD_ZOOM_RATE	(8.5f)	//手前に来た時の速さの増加率
#define WALL_INIT_WIDTH		(WALL_WIDTH * 0.1f)	//最初の壁の横幅
#define WALL_INIT_HEIGHT	(WALL_HEIGHT * 0.1f)//最初の壁の縦幅
#define WALL_INIT_WIDTH_HALF	(WALL_INIT_WIDTH * 0.5f)//最初の壁の原点X
#define WALL_INIT_HEIGHT_HALF	(WALL_INIT_HEIGHT * 0.5f)//最初の壁の原点Y
#define WALL_INIT_WIDTH_HALFHALF	(WALL_INIT_HEIGHT_HALF * 0.5f)
#define WALL_INIT_HEIGHT_HALFHALF	(WALL_INIT_HEIGHT_HALF * 0.5f)
#define MAX_PATTERN_SCORE			(3000)
#define WALL_ALPHA_ADD				(0.05f)//壁設置からアルファを上げていく速度

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct WALL {
	D3DXVECTOR2		pos;	//位置ベクトル
	D3DXVECTOR2		vel;	//速度ベクトル
	D3DXCOLOR		color;	//頂点カラー
	bool			use;	//使用中フラグ
	D3DXVECTOR2		size;	//サイズ
	D3DXVECTOR2		oldSize;	//サイズ
	int				mode;	//壁の種類
	float			dis;	//遠近距離
	int				g_num;
	D3DXVECTOR2		initSize;	//初期サイズ
	float			disRate;	//0(最奥)～1(最前)
	float			zoomSpeed;
	D3DXVECTOR2		initPos;	//初期位置
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall();

WALL* GetWall();
void SetWall(int mode = -1, float posX = 0.0f, float posY = 0.0f, float sizeX = 0.0f, float sizeY = 0.0f, float rot = 0.0f, int color = BARRIER_COLOR_RANDOM, float speedX = 0.0f, float speedY = 0.0f, float rotSpeed = 0.0f);
void StopWall();