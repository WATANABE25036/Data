//===================================================
//�t�@���t�@�[������[fanfare.cpp]
//Author:�n� �C	Date:2023.1.16
//===================================================
#include <time.h>
#include "fanfare.h"
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
FANFARE g_fanfare[MAX_FANFARE]; //����(�v�[�����O)
float g_xLRandom;
float g_yLRandom;
float g_xRRandom;
float g_yRRandom;

//===================================================
//������
//===================================================
void InitializeFanfare(void)
{
	//�l�̏�����
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
//�X�V
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
			//�O�t���[���̍��W���i�[
			g_fanfare[i].oldXPos = g_fanfare[i].xPos;
			g_fanfare[i].oldYPos = g_fanfare[i].yPos;

			g_fanfare[i].xSpeed * 0.02f;
			g_fanfare[i].ySpeed += 0.02f;

			//�ړ�
			g_fanfare[i].xPos += g_fanfare[i].xSpeed;
			g_fanfare[i].yPos += g_fanfare[i].ySpeed;

			//�Ǐ���
			if (g_fanfare[i].xPos <= DRAWING_WIDTHW_MIN || g_fanfare[i].xPos >= DRAWING_WIDTHW_MAX ||
				 g_fanfare[i].yPos >= DRAWING_HEIGHT_MAX )
			{
				g_fanfare[i].isUse = false;
			}
		}
		else
		{
			//�g���I������珉����
			g_fanfare[i].xPos = g_fanfare[i].oldXPos = 0.0f;
			g_fanfare[i].yPos = g_fanfare[i].oldYPos = 0.0f;
			g_fanfare[i].xSpeed = 0.0f;
			g_fanfare[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//�`��
//===================================================
void DrawFanfare(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeFanfare(void)
{

}

//===================================================
//�t�@���t�@�[���̃Z�b�g(�Z�b�^�[)
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
//�t�@���t�@�[���t�B�[�o�[�̃Z�b�g
//===================================================
void SetFanfareFever(void)
{
	SetFanfare(DRAWING_WIDTHW_MAX, DRAWING_HEIGHT_MAX, -g_xRRandom, -g_yRRandom);
	SetFanfare(DRAWING_WIDTHW_MIN, DRAWING_HEIGHT_MAX, g_xLRandom, -g_yLRandom);
	SetFanfare(DRAWING_WIDTHW_MAX * 0.75, DRAWING_HEIGHT_MAX, -g_xRRandom, -g_yRRandom);
	SetFanfare(DRAWING_WIDTHW_MAX * 0.25, DRAWING_HEIGHT_MAX, g_xLRandom, -g_yLRandom);
}

//===================================================
//�t�@���t�@�[���̃A�h���X�擾
//===================================================
FANFARE* GetFanfare(void)
{
	return g_fanfare;
}