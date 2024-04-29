//===================================================
//ブロック制御[block.cpp]
//Author:渡邉 修	Date:2023.2.7
//===================================================
#include <time.h>
#include "block.h"
#include "drawing.h"
#include "bullet.h"
#include "player.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//グローバル変数
//===================================================
BLOCK g_block[MAX_BLOCK];	//実体(プーリング)
int g_timeCntBlock;			//時間カウンター
float g_randomTurret;		//タレットの弾を乱れさせるのに使用
int g_randomTurretCnt;
bool g_oldInportSwitch;

//===================================================
//初期化
//===================================================
void InitializeBlock(void)
{
	//値の初期化
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		for (int j = 0; j < MAX_BLOCK_WIDE; j++)
		{
			g_block[i].xPos[j] = g_block[i].oldXPos[j] = 0.0f;
			g_block[i].isUseWide[j] = false;
		}
		for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
		{
			g_block[i].yPos[j] = g_block[i].oldYPos[j] = 0.0f;
			g_block[i].isUseHeight[j] = false;
			g_block[i].topBlock[j] = false;
		}
		g_block[i].mode = BLOCK_SIMPLE;
		g_block[i].speed = 0.0f;
		g_block[i].targetXS = 0;
		g_block[i].targetYS = 0;
		g_block[i].targetX1 = 0;
		g_block[i].targetY1 = 0;
		g_block[i].target = TARGET_1;
		g_block[i].startTrigger = false;
		g_block[i].isUse = false;
	}

	//allDeleteBlock();
	g_timeCntBlock = 0;
	srand((unsigned int)time(0));
	g_randomTurret = 0;
	g_randomTurretCnt = 0;
	g_oldInportSwitch = false;
}

//===================================================
//更新
//===================================================
void UpdateBlock(void)
{
	//マグネットブロックの切り替え処理
	PLAYER player = GetPlayer();

	if (player.inportSwitch != g_oldInportSwitch)
	{
		for (int i = 0; i < MAX_BLOCK; i++)
		{
			if (g_block[i].isUse)
			{
				if (g_block[i].mode == BLOCK_MAGNET_PLUS)
				{
					g_block[i].mode = BLOCK_MAGNET_MINUS;
				}
				else if (g_block[i].mode == BLOCK_MAGNET_MINUS)
				{
					g_block[i].mode = BLOCK_MAGNET_PLUS;
				}
			}
		}
	}
	g_oldInportSwitch = player.inportSwitch;

	g_randomTurretCnt++;

	
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_block[i].isUse)
		{
			if (g_block[i].targetX1 != 0 || g_block[i].targetY1 != 0)
			{
				//ブロックの移動
				//移動するブロックのスタート地点を記録
				if (g_block[i].startTrigger == false)
				{
					g_block[i].targetXS = (int)g_block[i].xPos[0];
					g_block[i].targetYS = (int)g_block[i].yPos[0];
					g_block[i].startTrigger = true;
				}

				//前フレームの座標を格納
				for (int j = 0; j < MAX_BLOCK_WIDE; j++)
				{
					if (g_block[i].isUseWide[j] == true)
					{
						g_block[i].oldXPos[j] = g_block[i].xPos[j];
					}
				}
				for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
				{
					if (g_block[i].isUseHeight[j] == true)
					{
						g_block[i].oldYPos[j] = g_block[i].yPos[j];
					}
				}

				//移動ブロック
				switch (g_block[i].target)
				{
				case TARGET_1:
					for (int j = 0; j < MAX_BLOCK_WIDE; j++)
					{
						if (g_block[i].isUseWide[j] == true)
						{
							if (g_block[i].targetX1 < g_block[i].targetXS)
							{
								g_block[i].xPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetX1 > g_block[i].targetXS)
							{
								g_block[i].xPos[j] += g_block[i].speed;
							}
						}
					}
					for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
					{
						if (g_block[i].isUseHeight[j] == true)
						{
							if (g_block[i].targetY1 < g_block[i].targetYS)
							{
								g_block[i].yPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetY1 > g_block[i].targetYS)
							{
								g_block[i].yPos[j] += g_block[i].speed;
							}
						}
					}
					break;
				case TARGET_2:
					for (int j = 0; j < MAX_BLOCK_WIDE; j++)
					{
						if (g_block[i].isUseWide[j] == true)
						{
							if (g_block[i].targetX2 < g_block[i].targetX1)
							{
								g_block[i].xPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetX2 > g_block[i].targetX1)
							{
								g_block[i].xPos[j] += g_block[i].speed;
							}
						}
					}
					for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
					{
						if (g_block[i].isUseHeight[j] == true)
						{
							if (g_block[i].targetY2 < g_block[i].targetY1)
							{
								g_block[i].yPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetY2 > g_block[i].targetY1)
							{
								g_block[i].yPos[j] += g_block[i].speed;
							}
						}
					}
					break;
				case TARGET_3:
					for (int j = 0; j < MAX_BLOCK_WIDE; j++)
					{
						if (g_block[i].isUseWide[j] == true)
						{
							if (g_block[i].targetX3 < g_block[i].targetX2)
							{
								g_block[i].xPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetX3 > g_block[i].targetX2)
							{
								g_block[i].xPos[j] += g_block[i].speed;
							}
						}
					}
					for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
					{
						if (g_block[i].isUseHeight[j] == true)
						{
							if (g_block[i].targetY3 < g_block[i].targetY2)
							{
								g_block[i].yPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetY3 > g_block[i].targetY2)
							{
								g_block[i].yPos[j] += g_block[i].speed;
							}
						}
					}
					break;
				case TARGET_START:
					for (int j = 0; j < MAX_BLOCK_WIDE; j++)
					{
						if (g_block[i].isUseWide[j] == true)
						{
							if (g_block[i].targetXS < g_block[i].targetX3)
							{
								g_block[i].xPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetXS > g_block[i].targetX3)
							{
								g_block[i].xPos[j] += g_block[i].speed;
							}
						}
					}
					for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
					{
						if (g_block[i].isUseHeight[j] == true)
						{
							if (g_block[i].targetYS < g_block[i].targetY3)
							{
								g_block[i].yPos[j] -= g_block[i].speed;
							}
							else if (g_block[i].targetYS > g_block[i].targetY3)
							{
								g_block[i].yPos[j] += g_block[i].speed;
							}
						}
					}
					break;
				default:
					break;
				}
			}

			//タレット
			for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
			{
				if (g_block[i].isUseHeight[j])
				{
					for (int k = 0; k < MAX_BLOCK_WIDE; k++)
					{
						if (g_block[i].isUseWide[k])
						{
							if (g_block[i].mode == BLOCK_TURRET_LEFT && g_randomTurretCnt >= TURRET_RATE)
							{
								g_randomTurret = rand() % TURRET_PRECISION;
								g_randomTurret -= TURRET_PRECISION / 2;
								g_randomTurret *= 0.01f;

								SetBullet(g_block[i].xPos[k] - 3, g_block[i].yPos[j], -TURRET_BULLET_SPEED, g_randomTurret);
							}

							if (g_block[i].mode == BLOCK_TURRET_RIGHT && g_randomTurretCnt >= TURRET_RATE)
							{
								g_randomTurret = rand() % TURRET_PRECISION;
								g_randomTurret -= TURRET_PRECISION / 2;
								g_randomTurret *= 0.01f;

								SetBullet(g_block[i].xPos[k] + 3, g_block[i].yPos[j], TURRET_BULLET_SPEED, g_randomTurret);
							}

							if (g_block[i].mode == BLOCK_TURRET_TOP && g_randomTurretCnt >= TURRET_RATE)
							{
								g_randomTurret = rand() % TURRET_PRECISION;
								g_randomTurret -= TURRET_PRECISION / 2;
								g_randomTurret *= 0.01f;

								SetBullet(g_block[i].xPos[k], g_block[i].yPos[j] - 1, g_randomTurret, -TURRET_BULLET_SPEED / 2);
							}

							if (g_block[i].mode == BLOCK_TURRET_UNDER && g_randomTurretCnt >= TURRET_RATE)
							{
								g_randomTurret = rand() % TURRET_PRECISION;
								g_randomTurret -= TURRET_PRECISION / 2;
								g_randomTurret *= 0.01f;

								SetBullet(g_block[i].xPos[k], g_block[i].yPos[j] + 1, g_randomTurret, TURRET_BULLET_SPEED / 2);
							}

							//移動ブロック
							if ((int)g_block[i].xPos[k] == g_block[i].targetXS && (int)g_block[i].yPos[j] == g_block[i].targetYS && g_block[i].target == TARGET_START)
							{
								//g_block[i].speed = g_block[i].speed * -1;
								g_block[i].target = TARGET_1;
							}
							if ((int)g_block[i].xPos[k] == g_block[i].targetX1 && (int)g_block[i].yPos[j] == g_block[i].targetY1 && g_block[i].target == TARGET_1)
							{
								//g_block[i].speed = g_block[i].speed * -1;
								g_block[i].target = TARGET_2;
							}
							if ((int)g_block[i].xPos[k] == g_block[i].targetX2 && (int)g_block[i].yPos[j] == g_block[i].targetY2 && g_block[i].target == TARGET_2)
							{
								g_block[i].target = TARGET_3;
							}
							if ((int)g_block[i].xPos[k] == g_block[i].targetX3 && (int)g_block[i].yPos[j] == g_block[i].targetY3 && g_block[i].target == TARGET_3)
							{
								g_block[i].target = TARGET_START;
							}
						}
					}
				}
			}
		}
		else
		{
			//使い終わったら初期化
			for (int j = 0; j < MAX_BLOCK_WIDE; j++)
			{
				g_block[i].xPos[j] = g_block[i].oldXPos[j] = 0.0f;
				g_block[i].isUseWide[j] = false;
			}
			for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
			{
				g_block[i].yPos[j] = g_block[i].oldYPos[j] = 0.0f;
				g_block[i].isUseHeight[j] = false;
			}
			g_block[i].speed = 0.0f;
			g_block[i].startTrigger = false;
		}
	}

	//射撃カウントのリセット
	if (g_randomTurretCnt >= TURRET_RATE)
	{
		g_randomTurretCnt = 0;
	}
}

//===================================================
//描画
//===================================================
void DrawBlock(void)
{

}

//===================================================
//終了処理
//===================================================
void FinalizeBlock(void)
{

}

//===================================================
//ブロックのセット[X (0→左端), Y (0→最下), ブロックのモード, 上面 or 側面 , 横幅, 高さ, スピード, 目標座標X1, Y1...Y3]
//===================================================
void SetBlock(float px, float py, int mode, bool topBlock, int wide, int height, float speed, int targetX1, int targetY1, int targetX2, int targetY2, int targetX3, int targetY3)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (!g_block[i].isUse)
		{//設置位置を設定
			for (int j = 0; j < height; j++)
			{
				for (int k = 0; k < wide; k++)
				{
					g_block[i].xPos[k] = g_block[i].oldXPos[k] = px + k;
					g_block[i].isUseWide[k] = true;
					g_block[i].yPos[j] = g_block[i].oldYPos[j] = py + j;
					g_block[i].isUseHeight[j] = true;
				}

				g_block[i].topBlock[j] = topBlock;

				if (j == 0 && speed != 0)
				{
					g_block[i].topBlock[j] = true;
				}
				else if(speed != 0)
				{
					g_block[i].topBlock[j] = false;
				}
			}

			//モードを設定
			g_block[i].mode = mode;

			//触れられるかの設定
			switch (mode)
			{
			case BLOCK_SIMPLE:
			case BLOCK_MAGNET_PLUS:
			case BLOCK_MAGNET_MINUS:
			case BLOCK_TURRET_LEFT:
			case BLOCK_TURRET_RIGHT:
			case BLOCK_TURRET_TOP:
			case BLOCK_TURRET_UNDER:
				g_block[i].untouch = false;
				break;
			case BLOCK_START:
			case BLOCK_GOAL:
				g_block[i].untouch = true;
				break;
			default:
				break;
			}

			//移動先の設定

			if (targetX2 == 0)
			{
				targetX2 = targetX1;
			}
			if (targetY2 == 0)
			{
				targetY2 = targetY1;
			}
			if (targetX3 == 0)
			{
				targetX3 = targetX2;
			}
			if (targetY3 == 0)
			{
				targetY3 = targetY2;
			}

			g_block[i].targetX1 = targetX1;
			g_block[i].targetY1 = targetY1;
			g_block[i].targetX2 = targetX2;
			g_block[i].targetY2 = targetY2;
			g_block[i].targetX3 = targetX3;
			g_block[i].targetY3 = targetY3;

			g_block[i].speed = speed;

			g_block[i].isUse = true;

			break;
		}
	}
}

//===================================================
//ブロックを一括削除
//===================================================
void allDeleteBlock(void)
{
	//初期化と同じ
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		for (int j = 0; j < MAX_BLOCK_WIDE; j++)
		{
			g_block[i].xPos[j] = g_block[i].oldXPos[j] = 0.0f;
			g_block[i].isUseWide[j] = false;
		}
		for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
		{
			g_block[i].yPos[j] = g_block[i].oldYPos[j] = 0.0f;
			g_block[i].isUseHeight[j] = false;
			g_block[i].topBlock[j] = false;
		}
		g_block[i].mode = BLOCK_SIMPLE;
		g_block[i].speed = 0.0f;
		g_block[i].targetXS = 0;
		g_block[i].targetYS = 0;
		g_block[i].targetX1 = 0;
		g_block[i].targetY1 = 0;
		g_block[i].target = TARGET_1;
		g_block[i].startTrigger = false;
		g_block[i].isUse = false;
	}
}

//===================================================
//ブロックのアドレス取得
//===================================================
BLOCK* GetBlock(void)
{
	return g_block;
}