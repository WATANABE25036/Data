//===================================================
//�u���b�N����[block.cpp]
//Author:�n� �C	Date:2023.2.7
//===================================================
#include <time.h>
#include "block.h"
#include "drawing.h"
#include "bullet.h"
#include "player.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
BLOCK g_block[MAX_BLOCK];	//����(�v�[�����O)
int g_timeCntBlock;			//���ԃJ�E���^�[
float g_randomTurret;		//�^���b�g�̒e�𗐂ꂳ����̂Ɏg�p
int g_randomTurretCnt;
bool g_oldInportSwitch;

//===================================================
//������
//===================================================
void InitializeBlock(void)
{
	//�l�̏�����
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
//�X�V
//===================================================
void UpdateBlock(void)
{
	//�}�O�l�b�g�u���b�N�̐؂�ւ�����
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
				//�u���b�N�̈ړ�
				//�ړ�����u���b�N�̃X�^�[�g�n�_���L�^
				if (g_block[i].startTrigger == false)
				{
					g_block[i].targetXS = (int)g_block[i].xPos[0];
					g_block[i].targetYS = (int)g_block[i].yPos[0];
					g_block[i].startTrigger = true;
				}

				//�O�t���[���̍��W���i�[
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

				//�ړ��u���b�N
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

			//�^���b�g
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

							//�ړ��u���b�N
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
			//�g���I������珉����
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

	//�ˌ��J�E���g�̃��Z�b�g
	if (g_randomTurretCnt >= TURRET_RATE)
	{
		g_randomTurretCnt = 0;
	}
}

//===================================================
//�`��
//===================================================
void DrawBlock(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeBlock(void)
{

}

//===================================================
//�u���b�N�̃Z�b�g[X (0�����[), Y (0���ŉ�), �u���b�N�̃��[�h, ��� or ���� , ����, ����, �X�s�[�h, �ڕW���WX1, Y1...Y3]
//===================================================
void SetBlock(float px, float py, int mode, bool topBlock, int wide, int height, float speed, int targetX1, int targetY1, int targetX2, int targetY2, int targetX3, int targetY3)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (!g_block[i].isUse)
		{//�ݒu�ʒu��ݒ�
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

			//���[�h��ݒ�
			g_block[i].mode = mode;

			//�G����邩�̐ݒ�
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

			//�ړ���̐ݒ�

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
//�u���b�N���ꊇ�폜
//===================================================
void allDeleteBlock(void)
{
	//�������Ɠ���
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
//�u���b�N�̃A�h���X�擾
//===================================================
BLOCK* GetBlock(void)
{
	return g_block;
}