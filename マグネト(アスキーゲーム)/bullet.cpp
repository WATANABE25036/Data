//===================================================
//�e����[bullet.cpp]
//Author:�n� �C	Date:2023.1.16
//===================================================
#include "bullet.h"
#include "drawing.h"
#include "block.h"
#include "explosion.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
BULLET g_bullet[MAX_BULLET]; //����(�v�[�����O)
int g_bulletSe;

//===================================================
//������
//===================================================
void InitializeBullet(void)
{
	//�l�̏�����
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
//�X�V
//===================================================
void UpdateBullet(void)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (g_bullet[i].isUse)
		{
			//playsound(g_bulletSe, 1);
			//updatesound(g_bulletSe);

			//�O�t���[���̍��W���i�[
			g_bullet[i].oldXPos = g_bullet[i].xPos;
			g_bullet[i].oldYPos = g_bullet[i].yPos;

			//�ړ�
			g_bullet[i].xPos += g_bullet[i].xSpeed;
			g_bullet[i].yPos += g_bullet[i].ySpeed;

			//�u���b�N�̓����蔻��
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

			//��ʒ[����
			if (g_bullet[i].xPos <= DRAWING_WIDTHW_MIN || g_bullet[i].xPos >= DRAWING_WIDTHW_MAX ||
				g_bullet[i].yPos <= DRAWING_HEIGHT_MIN || g_bullet[i].yPos >= DRAWING_HEIGHT_MAX )
			{
				g_bullet[i].isUse = false;
			}
		}
		else
		{
			//�g���I������珉����
			g_bullet[i].xPos = g_bullet[i].oldXPos = 0.0f;
			g_bullet[i].yPos = g_bullet[i].oldYPos = 0.0f;
			g_bullet[i].xSpeed = 0.0f;
			g_bullet[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//�`��
//===================================================
void DrawBullet(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeBullet(void)
{

}

//===================================================
//�e�̃Z�b�g(�Z�b�^�[)
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
//�e�̃A�h���X�擾
//===================================================
BULLET* GetBullet(void)
{
	return g_bullet;
}