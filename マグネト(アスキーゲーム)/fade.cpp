//===================================================
//暗転制御[fade.cpp]
//Author:渡邉 修	Date:2023.2.25
//===================================================
#include "fade.h"
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
FADE g_fadeLeft[MAX_FADE];	//実体(プーリング)
FADE g_fadeRight[MAX_FADE];	//実体(プーリング)
int g_timeCntIn;			//時間カウンター
int g_timeCntOut;			//時間カウンター
bool g_inTrigger;
bool g_outTrigger;
bool g_blacKOut;			//画面が隠れているかどうか
int g_fadeInSe;
int g_fadeOutSe;

//===================================================
//初期化
//===================================================
void InitializeFade(void)
{
	//値の初期化
	for (int i = 0; i < MAX_FADE; i++)
	{
		g_fadeLeft[i].xPos = g_fadeLeft[i].oldXPos = 0.0f;
		g_fadeLeft[i].yPos = g_fadeLeft[i].oldYPos = 0.0f;
		g_fadeLeft[i].xSpeed = 0.0f;
		g_fadeLeft[i].ySpeed = 0.0f;
		g_fadeLeft[i].isUse = false;
	}

	for (int i = 0; i < MAX_FADE; i++)
	{
		g_fadeRight[i].xPos = g_fadeRight[i].oldXPos = 0.0f;
		g_fadeRight[i].yPos = g_fadeRight[i].oldYPos = 0.0f;
		g_fadeRight[i].xSpeed = 0.0f;
		g_fadeRight[i].ySpeed = 0.0f;
		g_fadeRight[i].isUse = false;
	}

	g_timeCntIn = 0;
	g_timeCntOut = 0;
	g_inTrigger = false;
	g_outTrigger = false;
	g_blacKOut = false;
	g_fadeInSe = opensound("Data\\fadeIn.mp3");
	g_fadeOutSe = opensound("Data\\fadeOut.mp3");
}

//===================================================
//更新
//===================================================
void UpdateFade(void)
{
	//フェードアウトの処理
	if (g_outTrigger && g_timeCntIn == 0)
	{
		g_timeCntOut++;
		//左幕
		for (int i = 0; i < MAX_FADE; i++)
		{
			if (g_fadeLeft[i].isUse)
			{
				g_fadeLeft[i].xSpeed = sinf(g_timeCntOut * 0.04f) * 1.9f;
				g_fadeLeft[i].xPos += g_fadeLeft[i].xSpeed;
				g_fadeLeft[i].yPos += g_fadeLeft[i].ySpeed;

				if (g_fadeLeft[i].xSpeed <= 0)
				{
					g_blacKOut = true;
					g_outTrigger = false;
					g_timeCntOut = 0;
				}
			}
		}
		//右幕
		for (int i = 0; i < MAX_FADE; i++)
		{
			if (g_fadeRight[i].isUse)
			{
				g_fadeRight[i].xSpeed = sinf(g_timeCntOut * 0.04f) * -1.9f;
				g_fadeRight[i].xPos += g_fadeRight[i].xSpeed;
				g_fadeRight[i].yPos += g_fadeRight[i].ySpeed;

				if (g_fadeRight[i].xSpeed >= 0)
				{
					g_blacKOut = true;
					g_outTrigger = false;
					g_timeCntOut = 0;
				}
			}
		}
	}
	//フェードイン処理
	else if(g_inTrigger && g_timeCntOut == 0)
	{
		g_blacKOut = false;
		g_timeCntIn++;
		//左幕
		for (int i = 0; i < MAX_FADE; i++)
		{
			if (g_fadeLeft[i].isUse)
			{
				g_fadeLeft[i].xSpeed = sinf(g_timeCntIn * 0.04f) * -1.9f;

				g_fadeLeft[i].xPos += g_fadeLeft[i].xSpeed;
				g_fadeLeft[i].yPos += g_fadeLeft[i].ySpeed;

				if (g_fadeLeft[i].xSpeed >= 0)
				{
					g_fadeLeft[i].isUse = false;
					g_inTrigger = false;
					g_timeCntIn = 0;
				}
			}
		}
		//右幕
		for (int i = 0; i < MAX_FADE; i++)
		{
			if (g_fadeRight[i].isUse)
			{
				g_fadeRight[i].xSpeed = sinf(g_timeCntIn * 0.04f) * 1.9f;

				g_fadeRight[i].xPos += g_fadeRight[i].xSpeed;
				g_fadeRight[i].yPos += g_fadeRight[i].ySpeed;

				if (g_fadeRight[i].xSpeed <= 0)
				{
					g_fadeRight[i].isUse = false;
					g_inTrigger = false;
					g_timeCntIn = 0;
				}
			}
		}
	}
}

//===================================================
//描画
//===================================================
void DrawFade(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeFade(void)
{
	closesound(g_fadeInSe);
	closesound(g_fadeOutSe);
}

//===================================================
//フェードアウトのセット
//===================================================
void SetFadeOut(void)
{//画面外に配置
	if (!g_outTrigger && !g_blacKOut)//実行中や暗くなってるときは実行しない
	{
		playsound(g_fadeOutSe, 0);
		g_timeCntOut = 0;

		int cntL = 0;
		int cntR = 0;

		for (int i = 0; i < DRAWING_HEIGHT_MAX; i++)
		{
			for (int j = 0; j < DRAWING_WIDTHW_MAX / 2; j++)
			{
				if (!g_fadeLeft[cntL].isUse)
				{
					g_fadeLeft[cntL].xPos = -j;
					g_fadeLeft[cntL].yPos = i;
					g_fadeLeft[cntL].isUse = true;
				}
				cntL++;
			}

			for (int j = 0; j < DRAWING_WIDTHW_MAX / 2; j++)
			{
				if (!g_fadeRight[cntR].isUse)
				{
					g_fadeRight[cntR].xPos = j + 1 + DRAWING_WIDTHW_MAX;
					g_fadeRight[cntR].yPos = i;
					g_fadeRight[cntR].isUse = true;
				}
				cntR++;
			}
		}
		g_outTrigger = true;
	}
}

//===================================================
//フェードインのセット
//===================================================
void SetFadeIn(void)
{
	playsound(g_fadeInSe, 0);
	g_timeCntIn = 0;
	g_inTrigger = true;
}

//===================================================
//暗転のアドレス取得
//===================================================
FADE* GetFadeLeft(void)
{
	return g_fadeLeft;
}

FADE* GetFadeRight(void)
{
	return g_fadeRight;
}

bool GetBlacKOutTrigger(void)
{
	return g_blacKOut;
}