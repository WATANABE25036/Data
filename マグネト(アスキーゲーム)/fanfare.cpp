//===================================================
//ファンファーレ制御[fanfare.cpp]
//Author:渡邉 修	Date:2023.1.16
//===================================================
#include <time.h>
#include "fanfare.h"
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
FANFARE g_fanfare[MAX_FANFARE]; //実体(プーリング)
float g_xLRandom;
float g_yLRandom;
float g_xRRandom;
float g_yRRandom;

//===================================================
//初期化
//===================================================
void InitializeFanfare(void)
{
	//値の初期化
	for (int i = 0; i < MAX_FANFARE; i++)
	{
		g_fanfare[i].xPos = g_fanfare[i].oldXPos = 0.0f;
		g_fanfare[i].yPos = g_fanfare[i].oldYPos = 0.0f;
		g_fanfare[i].xSpeed = 0.0f;
		g_fanfare[i].ySpeed = 0.0f;
		g_fanfare[i].isUse = false;
	}
	g_xLRandom = 0;
	g_yLRandom = 0;
	g_xRRandom = 0;
	g_yRRandom = 0;
	srand((unsigned int)time(0));
}

//===================================================
//更新
//===================================================
void UpdateFanfare(void)
{
	g_xRRandom = rand() % 200 * 0.01f;
	g_yRRandom = rand() % 100 * 0.01f + 0.5f;

	g_xLRandom = rand() % 200 * 0.01f;
	g_yLRandom = rand() % 100 * 0.01f + 0.5f;

	for (int i = 0; i < MAX_FANFARE; i++)
	{
		if (g_fanfare[i].isUse)
		{
			//前フレームの座標を格納
			g_fanfare[i].oldXPos = g_fanfare[i].xPos;
			g_fanfare[i].oldYPos = g_fanfare[i].yPos;

			g_fanfare[i].xSpeed * 0.02f;
			g_fanfare[i].ySpeed += 0.02f;

			//移動
			g_fanfare[i].xPos += g_fanfare[i].xSpeed;
			g_fanfare[i].yPos += g_fanfare[i].ySpeed;

			//壁処理
			if (g_fanfare[i].xPos <= DRAWING_WIDTHW_MIN || g_fanfare[i].xPos >= DRAWING_WIDTHW_MAX ||
				 g_fanfare[i].yPos >= DRAWING_HEIGHT_MAX )
			{
				g_fanfare[i].isUse = false;
			}
		}
		else
		{
			//使い終わったら初期化
			g_fanfare[i].xPos = g_fanfare[i].oldXPos = 0.0f;
			g_fanfare[i].yPos = g_fanfare[i].oldYPos = 0.0f;
			g_fanfare[i].xSpeed = 0.0f;
			g_fanfare[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//描画
//===================================================
void DrawFanfare(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeFanfare(void)
{

}

//===================================================
//ファンファーレのセット(セッター)
//===================================================
void SetFanfare(float px, float py, float sx, float sy)
{
	for (int i = 0; i < MAX_FANFARE; i++)
	{
		if (!g_fanfare[i].isUse)
		{
			g_fanfare[i].xPos = g_fanfare[i].oldXPos = px;
			g_fanfare[i].yPos = g_fanfare[i].oldYPos = py;
			g_fanfare[i].xSpeed = sx;
			g_fanfare[i].ySpeed = sy;
			g_fanfare[i].isUse = true;

			break;
		}
	}
}

//===================================================
//ファンファーレフィーバーのセット
//===================================================
void SetFanfareFever(void)
{
	SetFanfare(DRAWING_WIDTHW_MAX, DRAWING_HEIGHT_MAX, -g_xRRandom, -g_yRRandom);
	SetFanfare(DRAWING_WIDTHW_MIN, DRAWING_HEIGHT_MAX, g_xLRandom, -g_yLRandom);
	SetFanfare(DRAWING_WIDTHW_MAX * 0.75, DRAWING_HEIGHT_MAX, -g_xRRandom, -g_yRRandom);
	SetFanfare(DRAWING_WIDTHW_MAX * 0.25, DRAWING_HEIGHT_MAX, g_xLRandom, -g_yLRandom);
}

//===================================================
//ファンファーレのアドレス取得
//===================================================
FANFARE* GetFanfare(void)
{
	return g_fanfare;
}