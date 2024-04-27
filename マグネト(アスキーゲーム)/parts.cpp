//===================================================
//�j�А���[parts.cpp]
//Author:�n� �C	Date:2023.2.28
//===================================================
#include <time.h>
#include "parts.h"
#include "drawing.h"
#include "player.h"
#include "bullet.h"
#include "gameControl.h"
#include "block.h"
#include "collision.h"
#include "explosion.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
PARTS g_parts[MAX_PARTS]; //����(�v�[�����O)
float g_xRandom;
float g_yRandom;
int isUseCnt;

//===================================================
//������
//===================================================
void InitializeParts(void)
{
	//�l�̏�����
	for (int i = 0; i < MAX_PARTS; i++)
	{
		g_parts[i].xPos = g_parts[i].oldXPos = 0.0f;
		g_parts[i].yPos = g_parts[i].oldYPos = 0.0f;
		g_parts[i].xSpeed = 0.0f;
		g_parts[i].ySpeed = 0.0f;
		g_parts[i].gravity = GRAVITY;
		g_parts[i].ground = false;
		g_parts[i].minusBlock = false;
		g_parts[i].isUse = false;
		g_parts[i].moveBlockTrigger = false;
		g_parts[i].xStackTrigger = false;
		g_parts[i].yStackTrigger = false;
		g_parts[i].ground = false;
		g_parts[i].partsNum = 0;
	}
	g_xRandom = 0;
	g_yRandom = 0;
	isUseCnt = 0;
	srand((unsigned int)time(0));
}

//===================================================
//�X�V
//===================================================
void UpdateParts(void)
{
	for (int l = 0; l < MAX_PARTS; l++)
	{
		if (g_parts[l].isUse)
		{
			//�O�t���[���̏����i�[
			g_parts[l].oldXPos = g_parts[l].xPos;
			g_parts[l].oldYPos = g_parts[l].yPos;

			//����
			g_parts[l].ySpeed = g_parts[l].ySpeed * DEC_Y;
			g_parts[l].xSpeed = g_parts[l].xSpeed * DEC_X;

			//�d��
			if (g_parts[l].ground)
			{
				g_parts[l].gravity = 0;
			}
			else
			{
				g_parts[l].gravity += GRAVITY;
			}

			//����������
			BLOCK* pBlock = GetBlock();
			g_parts[l].ground = false;
			g_parts[l].minusBlock = false;

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
									if (!(pBlock + i)->untouch)
									{
										//���̃u���b�N�����蔻��
										if ((int)(g_parts[l].xPos + g_parts[l].xSpeed) == (int)(pBlock + i)->xPos[k] && (int)g_parts[l].yPos == (int)(pBlock + i)->yPos[j])
										{
											g_parts[l].xSpeed = 0.0f;
										}

										//-�u���b�N�ׂ̗̎�
										if (((int)(g_parts[l].xPos + 1) == (int)(pBlock + i)->xPos[k] && (int)g_parts[l].yPos == (int)(pBlock + i)->yPos[j] ||
											(int)(g_parts[l].xPos - 1) == (int)(pBlock + i)->xPos[k] && (int)g_parts[l].yPos == (int)(pBlock + i)->yPos[j] ||
											(int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)(g_parts[l].yPos - 1) == (int)(pBlock + i)->yPos[j] ||
											(int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)(g_parts[l].yPos + 1) == (int)(pBlock + i)->yPos[j]) &&
											(pBlock + i)->mode == BLOCK_MAGNET_MINUS)
										{
											g_parts[l].minusBlock = true;
											g_parts[l].gravity = 0.0f;
										}
									}
								}
							}
						}
					}
				}
			}

			//�X�s�[�h�K�p
			g_parts[l].ySpeed += g_parts[l].gravity;
			g_parts[l].xPos += g_parts[l].xSpeed;
			g_parts[l].yPos += g_parts[l].ySpeed;

			//������
			g_parts[l].moveBlockTrigger = false;
			g_parts[l].xStackTrigger = false;
			g_parts[l].yStackTrigger = false;

			if (!g_parts[l].moveBlockTrigger)
			{
				for (int i = 0; i < MAX_BLOCK; i++)
				{
					if ((pBlock + i)->isUse && !(pBlock + i)->untouch)
					{
						for (int j = 0; j < MAX_BLOCK_HEIGHT; j++)
						{
							if ((pBlock + i)->isUseHeight[j])
							{
								for (int k = 0; k < MAX_BLOCK_WIDE; k++)
								{
									if ((pBlock + i)->isUseWide[k])
									{
										//���ɂ���u���b�N�Ɋђʂ�����
										if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)g_parts[l].yPos == (int)(pBlock + i)->yPos[j] && g_parts[l].oldYPos <= (pBlock + i)->yPos[j])
										{
											g_parts[l].yPos = g_parts[l].oldYPos;
											//�u���b�N�Ɠ������W�ɂȂ�����
											if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)(g_parts[l].yPos) + 1 != (int)(pBlock + i)->yPos[j])
											{
												g_parts[l].yPos = (pBlock + i)->yPos[j] - 1;//�u���b�N�̂ЂƂ�̍��W�Ɉړ�
											}
										}

										//��ɂ���u���b�N�Ɋђʂ�����
										if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)g_parts[l].yPos == (int)(pBlock + i)->yPos[j] && g_parts[l].oldYPos >= (pBlock + i)->yPos[j])
										{
											g_parts[l].yPos = g_parts[l].oldYPos;
											//�u���b�N�Ɠ������W�ɂȂ�����
											if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)(g_parts[l].yPos) - 1 != (int)(pBlock + i)->yPos[j])
											{
												g_parts[l].yPos = (pBlock + i)->yPos[j] + 1;//�u���b�N�̂ЂƂ��̍��W�Ɉړ�
											}

											if ((pBlock + i)->mode != BLOCK_MAGNET_MINUS)
											{
												g_parts[l].ySpeed += 1.5f;
											}
										}

										//�c�Ɉړ�����u���b�N�ɏ�邽�߂̏���
										if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)(g_parts[l].yPos) + 2 == (int)(pBlock + i)->yPos[j] &&
											(pBlock + i)->topBlock[j] && (pBlock + i)->yPos[j] > (pBlock + i)->oldYPos[j] && !inport(PK_W) && (pBlock + i)->mode != BLOCK_MAGNET_PLUS)
										{
											g_parts[l].yPos++;
										}
										//�����u���b�N�̎��̏���
										if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && ((int)(g_parts[l].yPos) + 1 == (int)(pBlock + i)->yPos[j]))
										{
											g_parts[l].ground = true;
											g_parts[l].ySpeed = 0;
											g_parts[l].xPos += (pBlock + i)->xPos[k] - (pBlock + i)->oldXPos[k];
											g_parts[l].yPos += (pBlock + i)->yPos[j] - (pBlock + i)->oldYPos[j];
											g_parts[l].moveBlockTrigger = true;//�u���b�N�ɏ��Ɗ����Ă��܂��̂�j�~
										}

										//�オ-�u���b�N�̎��̏���
										if ((int)g_parts[l].xPos == (int)(pBlock + i)->xPos[k] && (int)(g_parts[l].yPos) - 1 == (int)(pBlock + i)->yPos[j] &&
											(pBlock + i)->mode == BLOCK_MAGNET_MINUS)
										{
											g_parts[l].ground = true;
											g_parts[l].ySpeed = 0;
											g_parts[l].xPos += (pBlock + i)->xPos[k] - (pBlock + i)->oldXPos[k];
											g_parts[l].yPos += (pBlock + i)->yPos[j] - (pBlock + i)->oldYPos[j];
											g_parts[l].moveBlockTrigger = true;//�u���b�N�ɏ��Ɗ����Ă��܂��̂�j�~
										}
									}
								}
							}
						}
					}
				}
			}

			//�[����
			if (g_parts[l].xPos <= DRAWING_WIDTHW_MIN)
			{
				g_parts[l].isUse = false;
			}

			if (g_parts[l].xPos >= DRAWING_WIDTHW_MAX)
			{
				g_parts[l].isUse = false;
			}

			if (g_parts[l].yPos <= DRAWING_HEIGHT_MIN)
			{
				g_parts[l].yPos = DRAWING_HEIGHT_MIN;
			}

			if (g_parts[l].yPos >= DRAWING_HEIGHT_MAX)
			{
				g_parts[l].isUse = false;
			}
		}
		else
		{
			//�g���I������珉����
			g_parts[l].xPos = g_parts[l].oldXPos = 0.0f;
			g_parts[l].yPos = g_parts[l].oldYPos = 0.0f;
			g_parts[l].xSpeed = 0.0f;
			g_parts[l].ySpeed = 0.0f;
		}
	}
}

//===================================================
//�`��
//===================================================
void DrawParts(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeParts(void)
{

}

//===================================================
//�j�Ђ̃Z�b�g(�Z�b�^�[)
//===================================================
void SetParts(float px, float py)
{
	g_xRandom = rand() % 200;
	g_xRandom -= 100;
	g_xRandom *= 0.05f;
	g_yRandom = rand() % 200;
	g_yRandom -= 100;
	g_yRandom *= 0.05f;
	isUseCnt = 0;

	for (int i = 0; i < MAX_PARTS; i++)
	{
		//�g�p�����m�F����
		if (g_parts[i].isUse)
		{
			isUseCnt++;
		}
	}

	//���ׂĎg���Ă�����ŏ��̂�����
	if (isUseCnt == MAX_PARTS)
	{
		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (g_parts[i].partsNum == 1)
			{
				g_parts[i].isUse = false;
			}
			g_parts[i].partsNum--;
		}
	}

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (!g_parts[i].isUse)
		{
			g_parts[i].xPos = g_parts[i].oldXPos = px;
			g_parts[i].yPos = g_parts[i].oldYPos = py;
			g_parts[i].xSpeed = g_xRandom;
			g_parts[i].ySpeed = g_yRandom;
			g_parts[i].gravity = GRAVITY;
			g_parts[i].ground = false;
			g_parts[i].minusBlock = false;
			g_parts[i].isUse = true;
			g_parts[i].partsNum = isUseCnt;

			break;
		}
	}
}

//===================================================
//�j�Ѓt�B�[�o�[�̃Z�b�g
//===================================================
void SetPartsFever(void)
{
	PLAYER player = GetPlayer();

	for (int i = 0; i < PARTS_SPAWN_NUM; i++)
	{
		SetParts(player.xPos, player.yPos);
	}
}

//===================================================
//�j�Ђ̍폜
//===================================================
void allDeleteParts(void)
{
	//�l�̏�����
	for (int i = 0; i < MAX_PARTS; i++)
	{
		g_parts[i].xPos = g_parts[i].oldXPos = 0.0f;
		g_parts[i].yPos = g_parts[i].oldYPos = 0.0f;
		g_parts[i].xSpeed = 0.0f;
		g_parts[i].ySpeed = 0.0f;
		g_parts[i].gravity = GRAVITY;
		g_parts[i].ground = false;
		g_parts[i].minusBlock = false;
		g_parts[i].isUse = false;
		g_parts[i].moveBlockTrigger = false;
		g_parts[i].xStackTrigger = false;
		g_parts[i].yStackTrigger = false;
		g_parts[i].ground = false;
		g_parts[i].partsNum = 0;
	}
}

//===================================================
//�j�Ђ̃A�h���X�擾
//===================================================
PARTS* GetParts(void)
{
	return g_parts;
}