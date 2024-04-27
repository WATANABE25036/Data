//===================================================
//ヒットエフェクト(hit_spark.h)
//Auhor:渡邉 修	Date:2023.9.3
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define HIT_SPARK_MAX			(100)//キャラクターの数
#define HIT_SPARK_WIDTH		(80 *6)//画像横幅
#define HIT_SPARK_HEIGHT	(80 *6)//画像縦高さ
#define HIT_SPARK_HITBOX_WIDTH		(40)//ヒットエフェクトのヒットボックス横
#define HIT_SPARK_HITBOX_HEIGHT		(40)//ヒットエフェクトのヒットボックス縦
#define HIT_SPARK_WIDTH_PATTERN	(10)//横アニメパターン数
#define HIT_SPARK_HEIGHT_PATTERN	(11)//縦アニメパターン数
#define HIT_SPARK_FRAME_MAX	(HIT_SPARK_WIDTH_PATTERN * HIT_SPARK_HEIGHT_PATTERN)//フレーム数
#define HIT_SPARK_FRAME_SPAN	(5)//アニメーションのスパン
#define HIT_SPARK_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム
#define HIT_SPARK_SPEED		(8.0f)//ヒットエフェクトの移動速度

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct HIT_SPARK {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float rot;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	int animeFrameMax;
	int animeSpan;
	bool reverse;
};

enum class EFFECT
{
	NONE,		//エフェクトなし
	COMBAT,		//攻撃エフェクト
	SPLATTER,	//爆発するような
	RING,		//円が広がっていく
	LEAF,		//草が舞う
	COMBAT2,	//攻撃エフェクト(アニメーションなし)
	HIT_SPARK,	//弾ける
	BALL,		//ただの玉
	COMBAT3,	//切り下げ
	COMBAT4,	//突く
	LIGHT,		//後光
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitHitSpark(void);
void UninitHitSpark(void);
void UpdateHitSpark(void);
void DrawHitSpark(void);

HIT_SPARK* GetHitSpark();
void SetHitSpark(EFFECT name, float posX, float posY, bool reverse = false, float rot = 0.0f, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetHitSpark(EFFECT name, D3DXVECTOR2 pos, bool reverse = false, float rot = 0.0f, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetHitSparkAnime(EFFECT name, int i);