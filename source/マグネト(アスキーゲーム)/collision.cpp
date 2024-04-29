//===================================================
//当たり判定制御[collision.cpp]
//Author:渡邉 修	Date:2023.2.16
//===================================================
#include "collision.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "drawing.h"
#include "player.h"
#include "block.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
COLLISION g_collisionTopP;		//実体(プーリング)
COLLISION g_collisionUnderP;	//実体(プーリング)
COLLISION g_collisionRightP;	//実体(プーリング)
COLLISION g_collisionLeftP;		//実体(プーリング)

//===================================================
//初期化
//===================================================
void InitializeCollision(void)
{
	//値の初期化
	for (int i = 0; i < MAX_COLLISION_X; i++)
	{
		g_collisionTopP.xPos[i] = g_collisionTopP.oldXPos[i] = 0.0f;
		g_collisionUnderP.xPos[i] = g_collisionUnderP.oldXPos[i] = 0.0f;
		g_collisionRightP.xPos[i] = g_collisionRightP.oldXPos[i] = 0.0f;
		g_collisionLeftP.xPos[i] = g_collisionLeftP.oldXPos[i] = 0.0f;
	}
	for (int i = 0; i < MAX_COLLISION_Y; i++)
	{
		g_collisionTopP.yPos[i] = g_collisionTopP.oldYPos[i] = 0.0f;
		g_collisionUnderP.yPos[i] = g_collisionUnderP.oldYPos[i] = 0.0f;
		g_collisionRightP.yPos[i] = g_collisionRightP.oldYPos[i] = 0.0f;
		g_collisionLeftP.yPos[i] = g_collisionLeftP.oldYPos[i] = 0.0f;
	}
}

//===================================================
//更新
//===================================================
void UpdateCollision(void)
{
	//プレイヤー情報を取得
	PLAYER player = GetPlayer();
	BLOCK* pBlock = GetBlock();

	for (int i = 0; i < MAX_COLLISION_Y; i++)
	{
		for (int j = 0; j < MAX_COLLISION_X; j++)
		{
			g_collisionTopP.magSTrigger[i][j] = g_collisionTopP.magNTrigger[i][j] = false;
			g_collisionUnderP.magSTrigger[i][j] = g_collisionUnderP.magNTrigger[i][j] = false;
			g_collisionRightP.magSTrigger[i][j] = g_collisionRightP.magNTrigger[i][j] = false;
			g_collisionLeftP.magSTrigger[i][j] = g_collisionLeftP.magNTrigger[i][j] = false;
		}
	}

	g_collisionTopP.blockTrigger = false;
	g_collisionUnderP.blockTrigger = false;
	g_collisionRightP.blockTrigger = false;
	g_collisionLeftP.blockTrigger = false;

	//当たり判定の動作
	for (int i = 0; i < MAX_COLLISION_X; i++)
	{
		//前フレームの座標を格納
		g_collisionTopP.oldXPos[i] = g_collisionTopP.xPos[i];
		g_collisionUnderP.oldXPos[i] = g_collisionUnderP.xPos[i];
		g_collisionRightP.oldXPos[i] = g_collisionRightP.xPos[i];
		g_collisionLeftP.oldXPos[i] = g_collisionLeftP.xPos[i];

		//プレイヤーを追従させる
		g_collisionTopP.xPos[i] = player.xPos;

		g_collisionUnderP.xPos[i] = player.xPos;

		g_collisionRightP.xPos[i] = player.xPos - (i + 1);

		g_collisionLeftP.xPos[i] = player.xPos + (i + 1);
	}

	for (int i = 0; i < MAX_COLLISION_Y; i++)
	{
		//前フレームの座標を格納
		g_collisionTopP.oldYPos[i] = g_collisionTopP.yPos[i];
		g_collisionUnderP.oldYPos[i] = g_collisionUnderP.yPos[i];
		g_collisionRightP.oldYPos[i] = g_collisionRightP.yPos[i];
		g_collisionLeftP.oldYPos[i] = g_collisionLeftP.yPos[i];

		//プレイヤーを追従させる
		g_collisionTopP.yPos[i] = player.yPos - (i + 1);

		g_collisionUnderP.yPos[i] = player.yPos + (i + 1);

		g_collisionRightP.yPos[i] = player.yPos;

		g_collisionLeftP.yPos[i] = player.yPos;
	}

	//当たり判定処理
	for (int i = 0; i < MAX_COLLISION_Y; i++)
	{
		for (int j = 0; j < MAX_COLLISION_X; j++)
		{
			for (int k = 0; k < MAX_BLOCK; k++)
			{
				//シンプルブロックの時
				if ((pBlock + k)->isUse && (pBlock + k)->mode == BLOCK_SIMPLE)
				{
					for (int l = 0; l < MAX_BLOCK_HEIGHT; l++)
					{
						for (int n = 0; n < MAX_BLOCK_WIDE; n++)
						{
							if ((pBlock + k)->isUseWide[n] && (pBlock + k)->isUseHeight[l])
							{
								if ((int)g_collisionTopP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionTopP.yPos[i] == (int)(pBlock + k)->yPos[l])
								{
									g_collisionTopP.blockTrigger = true;
								}

								if ((int)g_collisionUnderP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionUnderP.yPos[i] == (int)(pBlock + k)->yPos[l])
								{
									g_collisionUnderP.blockTrigger = true;
								}

								if ((int)g_collisionRightP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionRightP.yPos[i] == (int)(pBlock + k)->yPos[l])
								{
									g_collisionRightP.blockTrigger = true;
								}

								if ((int)g_collisionLeftP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionLeftP.yPos[i] == (int)(pBlock + k)->yPos[l])
								{
									g_collisionLeftP.blockTrigger = true;
								}
							}
						}
					}
				}

				//ブロックが-の時
				if ((pBlock + k)->isUse && (pBlock + k)->mode == BLOCK_MAGNET_MINUS)
				{
					for (int l = 0; l < MAX_BLOCK_HEIGHT; l++)
					{
						for (int n = 0; n < MAX_BLOCK_WIDE; n++)
						{
							if ((pBlock + k)->isUseWide[n] && (pBlock + k)->isUseHeight[l])
							{
								if ((int)g_collisionTopP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionTopP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionTopP.blockTrigger == false)
								{
									g_collisionTopP.magSTrigger[i][j] = true;
								}

								if ((int)g_collisionUnderP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionUnderP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionUnderP.blockTrigger == false)
								{
									g_collisionUnderP.magSTrigger[i][j] = true;
								}

								if ((int)g_collisionRightP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionRightP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionRightP.blockTrigger == false)
								{
									g_collisionRightP.magSTrigger[i][j] = true;
								}

								if ((int)g_collisionLeftP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionLeftP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionLeftP.blockTrigger == false)
								{
									g_collisionLeftP.magSTrigger[i][j] = true;
								}
							}
						}
					}
				}

				//ブロックが+の時
				if ((pBlock + k)->isUse && (pBlock + k)->mode == BLOCK_MAGNET_PLUS)
				{
					for (int l = 0; l < MAX_BLOCK_HEIGHT; l++)
					{
						for (int n = 0; n < MAX_BLOCK_WIDE; n++)
						{
							if ((pBlock + k)->isUseWide[n] && (pBlock + k)->isUseHeight[l])
							{
								if ((int)g_collisionTopP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionTopP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionTopP.blockTrigger == false)
								{
									g_collisionTopP.magNTrigger[i][j] = true;
								}

								if ((int)g_collisionUnderP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionUnderP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionUnderP.blockTrigger == false)
								{
									g_collisionUnderP.magNTrigger[i][j] = true;
								}

								if ((int)g_collisionRightP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionRightP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionRightP.blockTrigger == false)
								{
									g_collisionRightP.magNTrigger[i][j] = true;
								}

								if ((int)g_collisionLeftP.xPos[j] == (int)(pBlock + k)->xPos[n] && (int)g_collisionLeftP.yPos[i] == (int)(pBlock + k)->yPos[l] && g_collisionLeftP.blockTrigger == false)
								{
									g_collisionLeftP.magNTrigger[i][j] = true;
								}
							}
						}
					}
				}
			}
		}
	}
}

//===================================================
//描画
//===================================================
void DrawCollision(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeCollision(void)
{

}

//===================================================
//当たり判定アドレス取得
//===================================================
COLLISION GetCollisionTopP(void)
{
	return g_collisionTopP;
}

COLLISION GetCollisionUnderP(void)
{
	return g_collisionUnderP;
}

COLLISION GetCollisionRightP(void)
{
	return g_collisionRightP;
}

COLLISION GetCollisionLeftP(void)
{
	return g_collisionLeftP;
}