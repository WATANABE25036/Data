//===================================================
//粒子(particle.h)
//Auhor:渡邉 修	Date:2023.9.9
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "hit_spark.h"

//---------------------------------------------------
//マクロ定義
//---------------------------------------------------
#define PARTICLE_MAX			(1000)//キャラクターの数
#define PARTICLE_WIDTH		(20)//画像横幅
#define PARTICLE_HEIGHT		(20)//画像縦高さ
#define PARTICLE_HITBOX_WIDTH		(20 * 0.3f)//粒子のヒットボックス横
#define PARTICLE_HITBOX_HEIGHT	(20 * 0.3f)//粒子のヒットボックス縦
#define PARTICLE_FRAME_SPAN	(2)//アニメーションのスパン
#define PARTICLE_FOLLOW_SPAN	(5)//キャラクター間の間隔（フレーム）

//---------------------------------------------------
//構造体宣言
//---------------------------------------------------
struct PARTICLE {
	D3DXVECTOR2	pos;	//位置ベクトル
	D3DXVECTOR2	spd;	//速度ベクトル
	D3DXCOLOR color;	//頂点カラー
	bool use;			//使用中フラグ
	D3DXVECTOR2 size;	//サイズ
	float rot;
	float sp;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	int animeFrameMax;
	bool reverse;
	float releaseX;
	float releaseY;
	float grv;
	D3DXVECTOR2 scale;
	D3DXCOLOR color255;
	bool loop;
	EFFECT hit;
};

//---------------------------------------------------
//プロトタイプ宣言
//---------------------------------------------------
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

PARTICLE* GetParticle();
void SetParticle(EFFECT name, float posX, float posY, int num, float minPower = 0.5f, float maxPower = 20.0f, bool loop = false, bool reverse = false, EFFECT hit = EFFECT::NONE, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetParticle(EFFECT name, D3DXVECTOR2 pos, int num, float minPower = 0.5f, float maxPower = 20.0f, bool loop = false, bool reverse = false, EFFECT hit = EFFECT::NONE, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetParticleRelease(int index, float power, float radian);
void SetParticleAnime(EFFECT name, int i);

