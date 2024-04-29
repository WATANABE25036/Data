//===================================================
//�}�b�v����[drawing.cpp]
//Author:�n� �C	Date:2023.1.24
//===================================================
#include <time.h>
#include "drawing.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "block.h"
#include "collision.h"
#include "fade.h"
#include "fanfare.h"
#include "gameControl.h"
#include "parts.h"
#include "main.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
BUFFER g_bufferDraw[DRAWING_HEIGHT_MAX][DRAWING_WIDTHW_MAX];
BUFFER g_bufferDisp[DRAWING_HEIGHT_MAX][DRAWING_WIDTHW_MAX];
int g_random;
char g_stageNum[3];
char g_remain[3];
int g_len;

//===================================================
//������
//===================================================
void InitializeDrawing(void)
{
	for (int i = 0; i < DRAWING_HEIGHT_MAX; i++)
	{
		for (int j = 0; j < DRAWING_WIDTHW_MAX; j++)
		{
			strcpy(g_bufferDraw[i][j].moji, ".");
			g_bufferDraw[i][j].color = 0x02;
			strcpy(g_bufferDisp[i][j].moji, " ");
			g_bufferDraw[i][j].color = 0, 0;
		}
	}

	g_random = 0;
	srand((unsigned int)time(0));

	for (int i = 0; i < 3; i++)
	{
		g_stageNum[i] = 0;
		g_remain[i] = 0;
	}

	g_len = 0;
}

//===================================================
//�X�V
//===================================================
void UpdateDrawing(void)
{

}

//===================================================
//�`��
//===================================================
void DrawDrawing(void)
{
	//�e���W���擾
	PLAYER player = GetPlayer();
	ENEMY* pEnemy = GetEnemy();
	BULLET* pBullet = GetBullet();
	EXPLOSION* pExplosion = GetExplosion();
	BLOCK* pBlock = GetBlock();
	COLLISION collisionTopP = GetCollisionTopP();
	COLLISION collisionUnderP = GetCollisionUnderP();
	COLLISION collisionRightP = GetCollisionRightP();
	COLLISION collisionLeftP = GetCollisionLeftP();
	FADE* pFadeLeft = GetFadeLeft();
	FADE* pFadeRight = GetFadeRight();
	FANFARE* pFanfare = GetFanfare();
	int stageNum = GetStageNum();
	PARTS* pParts = GetParts();
	SCENE scene = GetScene();
	bool instructions = GetInstructions();

	//�c������(�w�i�F)
	for (int i = 0; i < DRAWING_HEIGHT_MAX; i++)
	{
		for (int j = 0; j < DRAWING_WIDTHW_MAX; j++)
		{
			BufferSet(&g_bufferDraw[0][0], j, i, " ", BACK_COLOR, BACK_COLOR);
		}
	}

	//�u���b�N(��)
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if ((pBlock + i)->isUse)
		{
			for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
			{
				if ((pBlock + i)->isUseHeight[j])
				{
					for (int k = 0; k < MAX_BLOCK_WIDE; k++)
					{
						if ((pBlock + i)->isUseWide[k])
						{
							switch ((pBlock + i)->mode)
							{
							case BLOCK_SIMPLE:
								if ((pBlock + i)->topBlock[j])
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], " ", LIGHTRED, LIGHTGRAY);
								}
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTRED, LIGHTGRAY);
								break;

							case BLOCK_MAGNET_PLUS:
								if ((pBlock + i)->topBlock[j])
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "+", LIGHTRED, LIGHTRED);
								}
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j] - 1, "+", LIGHTRED, LIGHTRED);
								break;

							case BLOCK_MAGNET_MINUS:
								if ((pBlock + i)->topBlock[j])
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "-", LIGHTBLUE, LIGHTBLUE);
								}
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j] - 1, "-", LIGHTBLUE, LIGHTBLUE);
								break;

							default:
								break;
							}
						}
					}
				}
			}
		}
	}

	//�X�^�[�g�ƃS�[��
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if ((pBlock + i)->isUse)
		{
			for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
			{
				if ((pBlock + i)->isUseHeight[j])
				{
					for (int k = 0; k < MAX_BLOCK_WIDE; k++)
					{
						if ((pBlock + i)->isUseWide[k])
						{
							switch ((pBlock + i)->mode)
							{
							case BLOCK_START://�X�^�[�g
								if (stageNum != 0)
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, START_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, START_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, START_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, WHITE);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, START_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, START_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, START_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, START_COLOR);

									//�h�A��
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, START_TOP_COLOR);
								}
								break;

							case BLOCK_GOAL://�S�[��
								if (scene != SCENE_TITLE || stageNum != 0)
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, GOAL_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, GOAL_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, GOAL_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, YELLOW);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 1, " ", LIGHTBLUE, GOAL_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 2, " ", LIGHTBLUE, GOAL_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 3, " ", LIGHTBLUE, GOAL_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 4, " ", LIGHTBLUE, GOAL_COLOR);

									//�h�A��
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 0, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j] - 5, " ", WHITE, GOAL_TOP_COLOR);
								}
								break;

							default:
								break;
							}
						}
					}
				}
			}
		}
	}

	//�G
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if ((pEnemy + i)->isUse)
		{
			BufferSet(&g_bufferDraw[0][0], (int)(pEnemy + i)->xPos, (int)(pEnemy + i)->yPos, "{", 1);
			BufferSet(&g_bufferDraw[0][0], (int)(pEnemy + i)->xPos + 1, (int)(pEnemy + i)->yPos, "}", 1);
		}
	}

	//�e
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if ((pBullet + i)->isUse)
		{
			BufferSet(&g_bufferDraw[0][0], (int)(pBullet + i)->xPos, (int)(pBullet + i)->yPos, "o", 4);
		}
	}

	//�j��(��)
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if ((pParts + i)->isUse)
		{
			if (i % PARTS_SPAWN_NUM == 3)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos, (int)(pParts + i)->yPos, "x", BLACK);
			}

			else if (i % PARTS_SPAWN_NUM == 5)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos, (int)(pParts + i)->yPos, "/", BLACK);
			}
			else if (i % PARTS_SPAWN_NUM >= 6)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos, (int)(pParts + i)->yPos, ".", BLACK);
			}
		}
	}

	//�v���C���[
	if (player.isUse && !player.dead)
	{
		if (player.state != APPEAL)
		{
			//�v���C���[�E����
			if (player.facing == RIGHT_FACING)
			{
				//�E������S
				if (player.state == MAGNET_S_TOP)
				{
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "-", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "-", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, ")", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "_", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "(", BLACK);

					BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);

					BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "|", BLACK);

				}
				else if (player.state == MAGNET_S_LEFT)
				{
					if (player.upDownfacing == UP_FACING)//�㏸��
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos + 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos + 1, "|", BLACK);
					}
					else if (player.upDownfacing == DOWN_FACING)//���~��
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "|", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "~", BLACK);
					}
				}
				else if (player.state == MAGNET_S_RIGHT)
				{
					if (player.upDownfacing == UP_FACING)//�㏸��
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos + 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos + 1, "|", BLACK);
					}
					else if (player.upDownfacing == DOWN_FACING)//���~��
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "|", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "~", BLACK);
					}
				}
				//�E�����㏸��
				else if (player.state == RISE)
				{
					PlayerMotionRightRise();
				}
				//�E�������~��
				else if (player.state == FALL)
				{
					PlayerMotionRightFall();
				}
				//�E��������
				else if (player.state == WALK)
				{
					if (player.motionCnt < MOTIONFRAME_PLAYER_WALK)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "L", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 2)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "L", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 3)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "/", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 4)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "/", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
				}
				//�E������~���
				else
				{
					if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 36)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else
					{
						PlayerMotionRightTurn(37);
					}
				}
			}

			//�v���C���[������
			else if (player.facing == LEFT_FACING)
			{
				//��������S
				if (player.state == MAGNET_S_TOP)
				{
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "-", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "_", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, ")", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "-", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "(", BLACK);

					BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);

					BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos + 1, "|", BLACK);
				}
				else if (player.state == MAGNET_S_LEFT)
				{
					if (player.upDownfacing == UP_FACING)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos + 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos + 1, "|", BLACK);
					}
					else if (player.upDownfacing == DOWN_FACING)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "|", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "~", BLACK);
					}
				}
				else if (player.state == MAGNET_S_RIGHT)
				{
					if (player.upDownfacing == UP_FACING)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos + 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos + 1, "|", BLACK);
					}
					else if (player.upDownfacing == DOWN_FACING)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, "-", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "|", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos + 1, "~", BLACK);
					}
				}
				//�������㏸��
				else if (player.state == RISE)
				{
					PlayerMotionLeftRise();
				}
				//���������~��
				else if (player.state == FALL)
				{
					PlayerMotionLeftFall();
				}
				//����������
				else if (player.state == WALK)
				{
					if (player.motionCnt < MOTIONFRAME_PLAYER_WALK)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "J", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 2)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "J", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "/", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 3)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "/", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 4)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
				}
				//��������~���
				else
				{
					if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 36)
					{
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

						BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
						BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
					}
					else
					{
						PlayerMotionLeftTurn(37);
					}
				}
			}
		}

		//�S�[���A�s�[��
		else if (player.state == APPEAL)
		{
			if (player.motionCnt < MOTIONFRAME_PLAYER_APPEAL)
			{
				PlayerMotionRightFall();
			}
			else if (player.motionCnt < MOTIONFRAME_PLAYER_APPEAL * 2)
			{
				PlayerMotionRightRise();
			}
			else if (player.motionCnt < MOTIONFRAME_PLAYER_APPEAL * 3)
			{
				PlayerMotionLeftFall();
			}
			else if (player.motionCnt < MOTIONFRAME_PLAYER_APPEAL * 4)
			{
				PlayerMotionLeftRise();
			}
		}
	}

	//�j��(�O)
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if ((pParts + i)->isUse)
		{
			if (i % PARTS_SPAWN_NUM == 1)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos, (int)(pParts + i)->yPos, "(", BLACK);
			}
			else if (i % PARTS_SPAWN_NUM == 4)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos, (int)(pParts + i)->yPos, "_", BLACK);
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos + 1, (int)(pParts + i)->yPos, "_", BLACK);
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos + 2, (int)(pParts + i)->yPos, ")", BLACK);
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos - 1, (int)(pParts + i)->yPos, "_", BLACK);
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos - 2, (int)(pParts + i)->yPos, "(", BLACK);
			}
			else if (i % PARTS_SPAWN_NUM == 2)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pParts + i)->xPos, (int)(pParts + i)->yPos, "x", BLACK);
			}
		}
	}

	//�u���b�N(�O)
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if ((pBlock + i)->isUse)
		{
			for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
			{
				if ((pBlock + i)->isUseHeight[j])
				{
					for (int k = 0; k < MAX_BLOCK_WIDE; k++)
					{
						if ((pBlock + i)->isUseWide[k])
						{
							switch ((pBlock + i)->mode)
							{
							case BLOCK_SIMPLE:
								if (!(pBlock + i)->topBlock[j])
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], " ", LIGHTRED, DARKGRAY);
								}
								break;

							case BLOCK_MAGNET_PLUS:
								if (!(pBlock + i)->topBlock[j])
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "+", LIGHTRED, RED);
								}
								break;

							case BLOCK_MAGNET_MINUS:
								if (!(pBlock + i)->topBlock[j])
								{
									BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "-", LIGHTBLUE, BLUE);
								}
								break;

							case BLOCK_TURRET_LEFT:
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "_", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j], "[", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j], "O", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 3, (int)(pBlock + i)->yPos[j], "|", BLACK);

								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j] - 1, "_", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 2, (int)(pBlock + i)->yPos[j] - 1, "_", BLACK);

								break;

							case BLOCK_TURRET_RIGHT:
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "_", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j], "]", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j], "O", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 3, (int)(pBlock + i)->yPos[j], "|", BLACK);

								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j] - 1, "_", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 2, (int)(pBlock + i)->yPos[j] - 1, "_", BLACK);

								break;

							case BLOCK_TURRET_TOP:
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j] + 1, "'", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j] + 1, "\"", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j] + 1, "'", BLACK);

								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "O", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j], "]", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j], "[", BLACK);

								break;

							case BLOCK_TURRET_UNDER:

								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k], (int)(pBlock + i)->yPos[j], "o", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] + 1, (int)(pBlock + i)->yPos[j], "]", BLACK);
								BufferSet(&g_bufferDraw[0][0], (int)(pBlock + i)->xPos[k] - 1, (int)(pBlock + i)->yPos[j], "[", BLACK);

								break;

							default:
								break;
							}
						}
					}
				}
			}
		}
	}

	//����
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if ((pExplosion + i)->isUse)
		{
			//�A�j���[�V����
			if ((pExplosion + i)->frameCut < ANIMATION_FRAME_EXPLOSION * 1)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos, (int)(pExplosion + i)->yPos, "*", YELLOW);
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos + 1, (int)(pExplosion + i)->yPos, "-", RED);
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos - 1, (int)(pExplosion + i)->yPos, "-", RED);
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos, (int)(pExplosion + i)->yPos + 1, "'", RED);
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos, (int)(pExplosion + i)->yPos - 1, ",", RED);
			}
			else if ((pExplosion + i)->frameCut < ANIMATION_FRAME_EXPLOSION * 2)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos, (int)(pExplosion + i)->yPos, "O", RED);
			}
			else if ((pExplosion + i)->frameCut < ANIMATION_FRAME_EXPLOSION * 3)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos, (int)(pExplosion + i)->yPos, "*", YELLOW);
			}
			else if ((pExplosion + i)->frameCut < ANIMATION_FRAME_EXPLOSION * 4)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pExplosion + i)->xPos, (int)(pExplosion + i)->yPos, "+", YELLOW);
			}
		}
	}

	//�t�@���t�@�[��
	g_random = rand() % 5;
	for (int i = 0; i < MAX_FANFARE; i++)
	{
		if ((pFanfare + i)->isUse)
		{
			if (g_random == 1)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pFanfare + i)->xPos, (int)(pFanfare + i)->yPos, "*", 9);
			}
			if (g_random == 2)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pFanfare + i)->xPos, (int)(pFanfare + i)->yPos, "@", 10);
			}
			if (g_random == 3)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pFanfare + i)->xPos, (int)(pFanfare + i)->yPos, "*", 12);
			}
			if (g_random == 4)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pFanfare + i)->xPos, (int)(pFanfare + i)->yPos, "#", 13);
			}
			if (g_random == 5)
			{
				BufferSet(&g_bufferDraw[0][0], (int)(pFanfare + i)->xPos, (int)(pFanfare + i)->yPos, "*", 14);
			}
			BufferSet(&g_bufferDraw[0][0], (int)(pFanfare + i)->oldXPos, (int)(pFanfare + i)->oldYPos, "+", 15);
		}
	}

	//�v���C���[�����蔻��
	/*
	//	//�v���C���[�́������蔻��
	//	for (int i = 0; i < MAX_COLLISION_Y; i++)
	//	{
	//		for (int j = 0; j < MAX_COLLISION_X; j++)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)collisionTopP.xPos[j], (int)collisionTopP.yPos[i], "*", 0x0C);
	//		}
	//	}

	//	//�v���C���[�́������蔻��
	//	for (int i = 0; i < MAX_COLLISION_Y; i++)
	//	{
	//		for (int j = 0; j < MAX_COLLISION_X; j++)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)collisionUnderP.xPos[j], (int)collisionUnderP.yPos[i], "*", 0x0C);
	//		}
	//	}

	//	//�v���C���[�́������蔻��
	//	for (int i = 0; i < MAX_COLLISION_Y; i++)
	//	{
	//		for (int j = 0; j < MAX_COLLISION_X; j++)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)collisionRightP.xPos[j], (int)collisionRightP.yPos[i], "*", 0x0C);
	//		}
	//	}

	//	//�v���C���[�́������蔻��
	//	for (int i = 0; i < MAX_COLLISION_Y; i++)
	//	{
	//		for (int j = 0; j < MAX_COLLISION_X; j++)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)collisionLeftP.xPos[j], (int)collisionLeftP.yPos[i], "*", 0x0C);
	//		}
	//	}
	*/

	//UI
	{
		if (scene != SCENE_TITLE)
		{
			//�X�e�[�W
			snprintf(g_stageNum, 3, "%d", stageNum);
			g_len = strlen(g_stageNum);

			if (stageNum >= 0)
			{
				BufferSet(&g_bufferDraw[0][0], 138, 1, "[", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 139, 1, "�X", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 141, 1, "�e", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 143, 1, "�[", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 145, 1, "�W", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 147, 1, " ", ASCLl_COLOR, ASCLl_BACK_COLOR);
				if (g_len == 1)
				{
					BufferSet(&g_bufferDraw[0][0], 148, 1, "0", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], 149, 1, &g_stageNum[0], ASCLl_COLOR, ASCLl_BACK_COLOR);
				}
				if (g_len == 2)
				{
					BufferSet(&g_bufferDraw[0][0], 148, 1, &g_stageNum[0], ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], 149, 1, &g_stageNum[1], ASCLl_COLOR, ASCLl_BACK_COLOR);
				}

				BufferSet(&g_bufferDraw[0][0], 150, 1, "]", ASCLl_COLOR, ASCLl_BACK_COLOR);
			}

			//�c�@
			snprintf(g_remain, 3, "%d", player.remain);
			g_len = strlen(g_remain);

			if (stageNum >= 0)
			{
				BufferSet(&g_bufferDraw[0][0], 42, 1, "[", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 43, 1, "�c", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 45, 1, "�@", ASCLl_COLOR, ASCLl_BACK_COLOR);
				BufferSet(&g_bufferDraw[0][0], 47, 1, " ", ASCLl_COLOR, ASCLl_BACK_COLOR);
				if (g_len == 1)
				{
					BufferSet(&g_bufferDraw[0][0], 48, 1, "0", LIGHTRED, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], 49, 1, &g_remain[0], LIGHTRED, ASCLl_BACK_COLOR);
				}
				if (g_len == 2)
				{
					BufferSet(&g_bufferDraw[0][0], 48, 1, &g_remain[0], ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], 49, 1, &g_remain[1], ASCLl_COLOR, ASCLl_BACK_COLOR);
				}
				BufferSet(&g_bufferDraw[0][0], 50, 1, "]", ASCLl_COLOR, ASCLl_BACK_COLOR);
			}

			if (instructions)
			{
				if (inport(PJ1_XPOS) == -1)
				{
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 9, DRAWING_HEIGHT_MAX - 42, "�m", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 7, DRAWING_HEIGHT_MAX - 42, "s", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 6, DRAWING_HEIGHT_MAX - 42, "p", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 5, DRAWING_HEIGHT_MAX - 42, "a", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 4, DRAWING_HEIGHT_MAX - 42, "c", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 3, DRAWING_HEIGHT_MAX - 42, "e", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 2, DRAWING_HEIGHT_MAX - 42, "�n", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 2, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 4, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 6, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 8, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 10, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 12, DRAWING_HEIGHT_MAX - 42, " ", ASCLl_COLOR, ASCLl_BACK_COLOR);
				}
				else
				{
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 9, DRAWING_HEIGHT_MAX - 42, "�m", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 7, DRAWING_HEIGHT_MAX - 42, "L", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 6, DRAWING_HEIGHT_MAX - 42, "]", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 5, DRAWING_HEIGHT_MAX - 42, " ", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 4, DRAWING_HEIGHT_MAX - 42, "[", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 3, DRAWING_HEIGHT_MAX - 42, "R", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 2, DRAWING_HEIGHT_MAX - 42, "�n", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 2, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 4, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 6, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 8, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 10, DRAWING_HEIGHT_MAX - 42, "��", ASCLl_COLOR, ASCLl_BACK_COLOR);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 12, DRAWING_HEIGHT_MAX - 42, " ", ASCLl_COLOR, ASCLl_BACK_COLOR);
				}
			}
		}

		//�^�C�g�����
		{
			if (stageNum >= 0 && scene == SCENE_TITLE)
			{

				for (int i = 0; i < DRAWING_WIDTHW_MAX; i++)
				{
					BufferSet(&g_bufferDraw[0][0], i, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
				}
				if (inport(PJ1_XPOS) == -1)
				{
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 11, DRAWING_HEIGHT_MAX - 5, "�m", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 9, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 8, DRAWING_HEIGHT_MAX - 5, "e", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 7, DRAWING_HEIGHT_MAX - 5, "n", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 6, DRAWING_HEIGHT_MAX - 5, "t", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 5, DRAWING_HEIGHT_MAX - 5, "e", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 4, DRAWING_HEIGHT_MAX - 5, "r", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 3, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 2, DRAWING_HEIGHT_MAX - 5, "�n", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 2, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 4, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 6, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 8, DRAWING_HEIGHT_MAX - 5, "�n", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 10, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 12, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 14, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
				}
				else
				{
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 11, DRAWING_HEIGHT_MAX - 5, "�m", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 9, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 8, DRAWING_HEIGHT_MAX - 5, "s", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 7, DRAWING_HEIGHT_MAX - 5, "t", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 6, DRAWING_HEIGHT_MAX - 5, "a", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 5, DRAWING_HEIGHT_MAX - 5, "r", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 4, DRAWING_HEIGHT_MAX - 5, "t", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 3, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 - 2, DRAWING_HEIGHT_MAX - 5, "�n", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 2, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 4, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 6, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 8, DRAWING_HEIGHT_MAX - 5, "�n", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 10, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 12, DRAWING_HEIGHT_MAX - 5, "��", ASCLl_COLOR, BLACK);
					BufferSet(&g_bufferDraw[0][0], DRAWING_WIDTHW_MAX / 2 + 14, DRAWING_HEIGHT_MAX - 5, " ", ASCLl_COLOR, BLACK);
				}
			}
		}
	}

	//�Ó]
	for (int i = 0; i < MAX_FADE; i++)
	{
		if ((pFadeLeft + i)->isUse)
		{
			BufferSet(&g_bufferDraw[0][0], (int)(pFadeLeft + i)->xPos, (int)(pFadeLeft + i)->yPos, " ", BLACK, BLACK);
		}
	}

	for (int i = 0; i < MAX_FADE; i++)
	{
		if ((pFadeRight + i)->isUse)
		{
			BufferSet(&g_bufferDraw[0][0], (int)(pFadeRight + i)->xPos, (int)(pFadeRight + i)->yPos, " ", BLACK, BLACK);
		}
	}

	//�v���C���[����O�ɕ\��(�f�o�b�O�p)
	/*
	//if (player.isUse)
	//{
	//	//�v���C���[�E����
	//	if (player.facing == RIGHT_FACING)
	//	{
	//		//�E�����㏸��
	//		if (player.state == RISE)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "/", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "/", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "+", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "+", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//		}
	//		//�E�������~��
	//		else if (player.state == FALL)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "-", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "-", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, ")", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "(", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, ")", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, " ", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, " ", BLACK);
	//		}
	//		//�E��������
	//		else if (player.state == WALK)
	//		{
	//			if (player.motionCnt < MOTIONFRAME_PLAYER_WALK)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "L", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 2)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "L", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 3)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 4)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//		}
	//		//�E������~���
	//		else
	//		{
	//			if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 36)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 37)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 38)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 39)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 40)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//		}
	//	}

	//	//�v���C���[������
	//	else if (player.facing == LEFT_FACING)
	//	{
	//		//�������㏸��
	//		if (player.state == RISE)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "+", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "+", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, "(", BLACK);
	//		}
	//		//���������~��
	//		else if (player.state == FALL)
	//		{
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "-", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, ")", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "-", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "(", BLACK);

	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, " ", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//			BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);
	//		}
	//		//����������
	//		else if (player.state == WALK)
	//		{
	//			if (player.motionCnt < MOTIONFRAME_PLAYER_WALK)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "J", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 2)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "J", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 3)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_WALK * 4)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//		}
	//		//��������~���
	//		else
	//		{
	//			if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 36)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 37)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "|", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 38)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 39)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//			else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * 40)
	//			{
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "/", BLACK);
	//				BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	//			}
	//		}
	//	}
	//}*/

	BufferPrint(&g_bufferDisp[0][0], &g_bufferDraw[0][0]);
}

//===================================================
//�I������
//===================================================
void FinalizeDrawing(void)
{

}

//===================================================
//�o�b�t�@�Ƀf�[�^���������ފ֐�
//===================================================
void BufferSet(BUFFER* p, int x, int y, char* moji, int color, int backColor)
{
	if ((x > DRAWING_WIDTHW_MIN) && (x < DRAWING_WIDTHW_MAX) && (y > DRAWING_HEIGHT_MIN) && (y < DRAWING_HEIGHT_MAX))
	{
		strcpy((p + (y * DRAWING_WIDTHW_MAX) + x)->moji, moji);
		(p + (y * DRAWING_WIDTHW_MAX) + x)->color = color;

		if (backColor != NOT_COLOR)
		{
			(p + (y * DRAWING_WIDTHW_MAX) + x)->backColor = backColor;
		}
	}
}

//===================================================
//�\�������֐�
//===================================================
void BufferPrint(BUFFER* p0, BUFFER* p1)
{
	BUFFER* w0, * w1;

	for (int i = 0; i < DRAWING_HEIGHT_MAX; i++)
	{
		for (int j = 0; j < DRAWING_WIDTHW_MAX; j++)
		{
			w0 = p0 + (i * DRAWING_WIDTHW_MAX) + j;
			w1 = p1 + (i * DRAWING_WIDTHW_MAX) + j;

			if (strcmp (w0->moji , w1->moji) || w0->color != w1->color || w0->backColor != w1->backColor)
			{
				gotoxy(j, i);

				textattr(w1->backColor * 16 + w1->color);
				printf("%s", w1);

				*w0 = *w1;
			}
		}
	}
}

//===================================================
//�v���C���[�A�j���[�V�����֐�
//===================================================
void PlayerMotionRightTurn(int startFrame)
{
	PLAYER player = GetPlayer();

	if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * startFrame)
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
	else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * (startFrame + 1))
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "/", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
	else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * (startFrame + 2))
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "|", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
	else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * (startFrame + 3))
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "<", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "|", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
}

void PlayerMotionRightRise(void)
{
	PLAYER player = GetPlayer();
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "/", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "/", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "+", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "+", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "(", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
}

void PlayerMotionRightFall(void)
{
	PLAYER player = GetPlayer();
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "-", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "-", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, ")", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "(", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, ")", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, " ", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, " ", BLACK);
}

void PlayerMotionLeftTurn(int startFrame)
{
	PLAYER player = GetPlayer();
	if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * startFrame)
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "|", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
	else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * (startFrame + 1))
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
	else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * (startFrame + 2))
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "/", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
	else if (player.motionCnt < MOTIONFRAME_PLAYER_IDLE * (startFrame + 3))
	{
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, ">", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "+", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

		BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "/", BLACK);
		BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, " ", BLACK);
	}
}

void PlayerMotionLeftRise(void)
{
	PLAYER player = GetPlayer();
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, " ", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "|", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, " ", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "|", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, " ", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, ")", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 2, "+", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 2, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 2, " ", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 2, "+", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 2, "(", BLACK);
}

void PlayerMotionLeftFall(void)
{
	PLAYER player = GetPlayer();
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos, "-", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos, ")", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos, "-", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos, "(", BLACK);

	BufferSet(&g_bufferDraw[0][0], (int)player.xPos, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos + 2, (int)player.yPos - 1, " ", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 1, (int)player.yPos - 1, "_", BLACK);
	BufferSet(&g_bufferDraw[0][0], (int)player.xPos - 2, (int)player.yPos - 1, "(", BLACK);
}