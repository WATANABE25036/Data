//===================================================
//弾制御[bullet.cpp]
//Author:渡邉 修	Date:2023.1.16
//===================================================
#include "bullet.h"
#include "drawing.h"
#include "block.h"
#include "explosion.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
BULLET g_bullet[MAX_BULLET]; //実体(プーリング)
int g_bulletSe;

//===================================================
//初期化
//===================================================
void InitializeBullet(void)
{
	//値の初期化
	for (int i = 0; i < MAX_BULLET; i++)
	{
		g_bullet[i].xPos = g_bullet[i].oldXPos = 0.0f;
		g_bullet[i].yPos = g_bullet[i].oldYPos = 0.0f;
		g_bullet[i].xSpeed = 0.0f;
		g_bullet[i].ySpeed = 0.0f;
		g_bullet[i].isUse = false;
	}
	//g_bulletSe = opensound("bullet.wav");
}

//===================================================
//更新
//===================================================
void UpdateBullet(void)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].isUse)
		{
			//playsound(g_bulletSe, 1);
			//updatesound(g_bulletSe);

			//前フレームの座標を格納
			g_bullet[i].oldXPos = g_bullet[i].xPos;
			g_bullet[i].oldYPos = g_bullet[i].yPos;

			//移動
			g_bullet[i].xPos += g_bullet[i].xSpeed;
			g_bullet[i].yPos += g_bullet[i].ySpeed;

			//ブロックの当たり判定
			BLOCK* pBlock = GetBlock();

			for (int j = 0; j < MAX_BLOCK; j++)
			{
				if ((pBlock + j)->isUse && !(pBlock + j)->untouch)
				{
					for (int k = 0; k < MAX_BLOCK_HEIGHT; k++)
					{
						if ((pBlock + j)->isUseHeight[k])
						{
							for (int l = 0; l < MAX_BLOCK_WIDE; l++)
							{
								if ((pBlock + j)->isUseWide[l])
								{
									if ((int)(pBlock + j)->xPos[l] == (int)g_bullet[i].xPos && (int)(pBlock + j)->yPos[k] == (int)g_bullet[i].yPos)
									{
										SetExplosion(g_bullet[i].oldXPos, g_bullet[i].oldYPos);
										g_bullet[i].isUse = false;
									}
								}
							}
						}
					}
				}
			}

			//画面端処理
			if (g_bullet[i].xPos <= DRAWING_WIDTHW_MIN || g_bullet[i].xPos >= DRAWING_WIDTHW_MAX ||
				g_bullet[i].yPos <= DRAWING_HEIGHT_MIN || g_bullet[i].yPos >= DRAWING_HEIGHT_MAX )
			{
				g_bullet[i].isUse = false;
			}
		}
		else
		{
			//使い終わったら初期化
			g_bullet[i].xPos = g_bullet[i].oldXPos = 0.0f;
			g_bullet[i].yPos = g_bullet[i].oldYPos = 0.0f;
			g_bullet[i].xSpeed = 0.0f;
			g_bullet[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//描画
//===================================================
void DrawBullet(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeBullet(void)
{

}

//===================================================
//弾のセット(セッター)
//===================================================
void SetBullet(float px, float py, float sx, float sy)
{	
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (!g_bullet[i].isUse)
		{
			g_bullet[i].xPos = g_bullet[i].oldXPos = px;
			g_bullet[i].yPos = g_bullet[i].oldYPos = py;
			g_bullet[i].xSpeed = sx;
			g_bullet[i].ySpeed = sy;
			g_bullet[i].isUse = true;

			break;
		}
	}
}

//===================================================
//弾のアドレス取得
//===================================================
BULLET* GetBullet(void)
{
	return g_bullet;
}