//===================================================
//爆発アニメーション制御[explosion.cpp]
//Author:渡邉 修	Date:2023.1.19
//===================================================
#include "explosion.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
EXPLOSION g_explosion[MAX_EXPLOSION]; //実体(プーリング)

//===================================================
//初期化
//===================================================
void InitializeExplosion(void)
{
	//値の初期化
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_explosion[i].xPos = g_explosion[i].oldXPos = 0.0f;
		g_explosion[i].yPos = g_explosion[i].oldYPos = 0.0f;
		g_explosion[i].xSpeed = 0.0f;
		g_explosion[i].ySpeed = 0.0f;
		g_explosion[i].isUse = false;
		g_explosion[i].frameCut = 0;
	}
}

//===================================================
//更新
//===================================================
void UpdateExplosion(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (g_explosion[i].isUse)
		{
			//前フレームの座標を格納
			g_explosion[i].oldXPos = g_explosion[i].xPos;
			g_explosion[i].oldYPos = g_explosion[i].yPos;

			//移動
			g_explosion[i].xPos += g_explosion[i].xSpeed;
			g_explosion[i].yPos += g_explosion[i].ySpeed;

			//フレームカウンターを進める
			g_explosion[i].frameCut++;

			if (g_explosion[i].frameCut > ANIMATION_FRAME_EXPLOSION * ANIMATION_FRAME_MAX_EXPLOSION)
			{
				g_explosion[i].isUse = false;
			}
		}
		else
		{
			//使い終わったら初期化
			g_explosion[i].frameCut = 0;
			g_explosion[i].xPos = g_explosion[i].oldXPos = 0.0f;
			g_explosion[i].yPos = g_explosion[i].oldYPos = 0.0f;
			g_explosion[i].xSpeed = 0.0f;
			g_explosion[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//描画
//===================================================
void DrawExplosion(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeExplosion(void)
{

}

//===================================================
//爆発アニメーションのセット(セッター)
//===================================================
void SetExplosion(float px, float py, float sx, float sy)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (!g_explosion[i].isUse)
		{
			g_explosion[i].xPos = g_explosion[i].oldXPos = px;
			g_explosion[i].yPos = g_explosion[i].oldYPos = py;
			g_explosion[i].xSpeed = sx;
			g_explosion[i].ySpeed = sy;
			g_explosion[i].isUse = true;

			break;
		}
	}
}

//===================================================
//爆発のアドレスを取得
//===================================================
EXPLOSION* GetExplosion(void)
{
	return g_explosion;
}