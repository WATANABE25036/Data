//===================================================
//粒子(particle.cpp)
//Auhor:渡邉 修	Date:2023.9.9
//===================================================
#include "particle.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "dead.h"
#include "main.h"
#include "tile.h"
#include "camera.h"
#include "tile.h"
#include "hit_spark.h"

//---------------------------------------------------
//グローバル変数
//---------------------------------------------------
//staticを付けるとファイルの中のグローバル変数になる
static int g_TexNo;
static int g_SE_particleHit;
static int g_SE_move;
static int g_SE_drop;
static float g_UW;
static float g_VH;
static float g_AnimeSkipFrameFloat;
static PARTICLE g_Particle[PARTICLE_MAX];
static TILE_DATA* p_Tile;
static CAMERA* p_Camera;
static bool g_Reverse;
static bool g_soundDupCheck;
static int g_soundDupCheckCou;

//---------------------------------------------------
//初期化
//---------------------------------------------------
void InitParticle(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Effect.png");
	//効果音作成
	//char se1[] =
	//{
	//	"data\\SE\\se_particleHit.wav"
	//};
	//g_SE_particleHit = LoadSound(&se1[0]);

	//char se2[] =
	//{
	//	"data\\SE\\move.wav"
	//};
	//g_SE_move = LoadSound(&se2[0]);

	//char se3[] =
	//{
	//	"data\\SE\\drop.wav"
	//};
	//g_SE_drop = LoadSound(&se3[0]);

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		g_Particle[i].use = false;
		g_Particle[i].pos.x = SCREEN_WIDTH / 2;
		g_Particle[i].pos.y = SCREEN_HEIGHT * 1.5f;
		g_Particle[i].spd.x = 0;
		g_Particle[i].spd.y = 0;
		g_Particle[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Particle[i].size = D3DXVECTOR2(PARTICLE_WIDTH, PARTICLE_HEIGHT);
		g_Particle[i].rot = 0.0f;
		g_Particle[i].sp = 0;
		g_Particle[i].uv = D3DXVECTOR2(0, 0);
		g_Particle[i].animePattern = 0;
		g_Particle[i].animeWidthPattern = HIT_SPARK_WIDTH_PATTERN;
		g_Particle[i].animeBasePattern = 1;
		g_Particle[i].animeSkipFrame = 0;
		g_Particle[i].animeFrameMax = 0;
		g_Particle[i].reverse = false;
		g_Particle[i].releaseX = 0;
		g_Particle[i].releaseY = 0;
		g_Particle[i].grv = 0.3f;
		g_Particle[i].scale = D3DXVECTOR2(1.0f, 1.0f);
		g_Particle[i].color255 = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f);
		g_Particle[i].loop = false;
		g_Particle[i].hit = EFFECT::NONE;
	}

	//グローバル変数初期化
	g_UW = 1.0f / HIT_SPARK_WIDTH_PATTERN;
	g_VH = 1.0f / HIT_SPARK_HEIGHT_PATTERN;
	g_Reverse = false;
	g_soundDupCheck = false;
	g_soundDupCheckCou = 0;
}

//---------------------------------------------------
//更新
//---------------------------------------------------
void UpdateParticle(void)
{
	g_soundDupCheckCou = Counter(g_soundDupCheckCou, 10);
	if(g_soundDupCheckCou == 0)g_soundDupCheck = false;
	
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (g_Particle[i].use)
		{
			g_Particle[i].spd.x = g_Particle[i].releaseX;
			g_Particle[i].spd.y = g_Particle[i].releaseY;
			g_Particle[i].pos += g_Particle[i].spd;

			g_Particle[i].releaseY += 0.5f;

			//ベクトルの正規化
			D3DXVec2Normalize(&g_Particle[i].spd, &g_Particle[i].spd);
			g_Particle[i].spd *= g_Particle[i].sp;//目的のスピードにするためにスピードを乗算する

			g_Particle[i].color.a -= 0.001f;

			if (g_Particle[i].color.a <= 0)
			{
				g_Particle[i].use = false;
			}

			//壁の衝突判定
			TILE_DATA* dir = GetMapInfo(g_Particle[i].pos + g_Particle[i].spd, { PARTICLE_HITBOX_WIDTH, PARTICLE_HITBOX_HEIGHT });
			if (dir[4].attrib == MAP_ATTRIB_STOP)
			{
				SetHitSpark(g_Particle[i].hit, g_Particle[i].pos, false, 0.0f, g_Particle[i].color255.r, g_Particle[i].color255.g, g_Particle[i].color255.b);
				g_Particle[i].use = false;
				if (!g_soundDupCheck)
				{
					//PlaySound(g_SE_particleHit, 0);
					g_soundDupCheck = true;
				}
			}

			//画面から出たら消す
			if (OffScreenJudge(g_Particle[i].pos.x, g_Particle[i].pos.y, PARTICLE_WIDTH, PARTICLE_HEIGHT))
			{
				g_Particle[i].use = false;
			}
		}
	}
}

//---------------------------------------------------
//描画
//---------------------------------------------------
void DrawParticle(void)
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (g_Particle[i].use)
		{
			//アニメーション
			g_Particle[i].uv = SetAnimation(g_Particle[i].animeBasePattern, g_Particle[i].animePattern, HIT_SPARK_WIDTH_PATTERN, HIT_SPARK_HEIGHT_PATTERN, g_Particle[i].animeWidthPattern, g_Particle[i].reverse);

			g_Particle[i].animeSkipFrame = Counter(g_Particle[i].animeSkipFrame, PARTICLE_FRAME_SPAN);

			if (g_Particle[i].animeSkipFrame == 0)
			{
				g_Particle[i].animePattern = Counter(g_Particle[i].animePattern, g_Particle[i].animeFrameMax);
				if (g_Particle[i].animePattern == 0 && !g_Particle[i].loop)g_Particle[i].animeWidthPattern = 1;//アニメをループさせない
			}


			DrawSpriteColorRotateScaleCamera(g_TexNo,
				g_Particle[i].pos.x, g_Particle[i].pos.y,
				g_Particle[i].size.x, g_Particle[i].size.y,	//幅、高さ
				0, 0,
				g_Particle[i].uv.x, g_Particle[i].uv.y,		//中心UV座標
				g_UW, g_VH,		//テクスチャ幅、高さ
				g_Particle[i].color.r, g_Particle[i].color.g, g_Particle[i].color.b, g_Particle[i].color.a,
				g_Particle[i].rot,
				g_Particle[i].scale.x, g_Particle[i].scale.y
			);
		}
	}
}

//---------------------------------------------------
//終了処理
//---------------------------------------------------
void UninitParticle(void)
{
	delete[] p_Tile;
}

//---------------------------------------------------
// 粒子取得処理
//---------------------------------------------------
PARTICLE* GetParticle()
{
	return &g_Particle[0];
}

//---------------------------------------------------
// 粒子配置処理
//---------------------------------------------------
void SetParticle(EFFECT name, float posX, float posY, int num, float minPower, float maxPower, bool loop, bool reverse, EFFECT hit, float r, float g, float b)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < PARTICLE_MAX; j++)
		{
			if (!g_Particle[j].use)
			{
				float R = r / 255;
				float G = g / 255;
				float B = b / 255;
				g_Particle[j].color = D3DXCOLOR(R, G, B, 1.0f);
				g_Particle[j].color255 = D3DXCOLOR(r, g, b, 1.0f);

				SetParticleAnime(name, j);

				g_Particle[j].pos = D3DXVECTOR2(posX, posY);
				g_Particle[j].spd = D3DXVECTOR2(0, 0);
				g_Particle[j].rot = 0;
				float ranSp = GetRandomFloat(0.5f, 10.0f);
				g_Particle[j].sp = ranSp;
				g_Particle[j].uv = D3DXVECTOR2(0, 0);
				g_Particle[j].animePattern = 0;
				g_Particle[j].animeSkipFrame = 0;
				g_Particle[j].reverse = reverse;
				g_Particle[j].loop = loop;
				g_Particle[j].hit = hit;
				g_Particle[j].use = true;

				float ranSc = GetRandomFloat(3.0f, 10.0f);
				g_Particle[j].scale = D3DXVECTOR2(ranSc, ranSc);

				float ranDeg = GetRandomFloat(0.0f, 180.0f);
				float radian = ranDeg * 3.14159f / 180.0f;

				float ranPower = GetRandomFloat(minPower, maxPower);

				SetParticleRelease(j, ranPower, radian);

				break;
			}
		}
	}
}

void SetParticle(EFFECT name, D3DXVECTOR2 pos, int num, float minPower, float maxPower, bool loop, bool reverse, EFFECT hit, float r, float g, float b)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < PARTICLE_MAX; j++)
		{
			if (!g_Particle[j].use)
			{
				float R = r / 255;
				float G = g / 255;
				float B = b / 255;
				g_Particle[j].color = D3DXCOLOR(R, G, B, 1.0f);
				g_Particle[j].color255 = D3DXCOLOR(r, g, b, 1.0f);

				SetParticleAnime(name, j);

				g_Particle[j].pos = pos;
				g_Particle[j].spd = D3DXVECTOR2(0, 0);
				g_Particle[j].rot = 0;
				float ranSp = GetRandomFloat(0.5f, 10.0f);
				g_Particle[j].sp = ranSp;
				g_Particle[j].uv = D3DXVECTOR2(0, 0);
				g_Particle[j].animePattern = 0;
				g_Particle[j].animeSkipFrame = 0;
				g_Particle[j].reverse = reverse;
				g_Particle[j].loop = loop;
				g_Particle[j].hit = hit;
				g_Particle[j].use = true;

				float ranSc = GetRandomFloat(3.0f, 10.0f);
				g_Particle[j].scale = D3DXVECTOR2(ranSc, ranSc);

				float ranDeg = GetRandomFloat(0.0f, 180.0f);
				float radian = ranDeg * 3.14159f / 180.0f;

				float ranPower = GetRandomFloat(minPower, maxPower);

				SetParticleRelease(j, ranPower, radian);



				break;
			}
		}
	}
}

//---------------------------------------------------
// ノックバック設定 [引数]index: 配列番号
//---------------------------------------------------
void SetParticleRelease(int index, float power, float radian)
{
	D3DXVECTOR2 vector = CalculateVector(-power, radian);

	if (g_Particle[index].use)
	{
		g_Particle[index].releaseX = vector.x;
		g_Particle[index].releaseY = vector.y;
	}
}

//エフェクトが増えたらここに追加
void SetParticleAnime(EFFECT name, int i)
{
	switch (name)
	{
	case EFFECT::NONE:
		g_Particle[i].animeWidthPattern = 0;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::NONE;
		break;
	case EFFECT::COMBAT:
		g_Particle[i].animeWidthPattern = 6;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::COMBAT;
		break;
	case EFFECT::SPLATTER:
		g_Particle[i].animeWidthPattern = 7;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::SPLATTER;
		break;
	case EFFECT::RING:
		g_Particle[i].animeWidthPattern = 5;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::RING;
		break;
	case EFFECT::LEAF:
		g_Particle[i].animeWidthPattern = 3;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::LEAF;
		break;
	case EFFECT::COMBAT2:
		g_Particle[i].animeWidthPattern = 1;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::COMBAT2;
		break;
	case EFFECT::HIT_SPARK:
		g_Particle[i].animeWidthPattern = 5;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::HIT_SPARK;
		break;
	case EFFECT::BALL:
		g_Particle[i].animeWidthPattern = 1;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::BALL;
		break;
	case EFFECT::COMBAT3:
		g_Particle[i].animeWidthPattern = 7;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::COMBAT3;
		break;
	case EFFECT::COMBAT4:
		g_Particle[i].animeWidthPattern = 7;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::COMBAT4;
		break;
	case EFFECT::LIGHT:
		g_Particle[i].animeWidthPattern = 5;
		g_Particle[i].animeFrameMax = g_Particle[i].animeWidthPattern;
		g_Particle[i].animeBasePattern = HIT_SPARK_WIDTH_PATTERN * (int)EFFECT::LIGHT;
		g_Particle[i].color.a = 0.5f;
		break;
	default:
		break;
	}
}
