//===================================================
//�Ó]����[fade.cpp]
//Author:�n� �C	Date:2023.2.25
//===================================================
#include "fade.h"
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
FADE g_fadeLeft[MAX_FADE];	//����(�v�[�����O)
FADE g_fadeRight[MAX_FADE];	//����(�v�[�����O)
int g_timeCntIn;			//���ԃJ�E���^�[
int g_timeCntOut;			//���ԃJ�E���^�[
bool g_inTrigger;
bool g_outTrigger;
bool g_blacKOut;			//��ʂ��B��Ă��邩�ǂ���
int g_fadeInSe;
int g_fadeOutSe;

//===================================================
//������
//===================================================
void InitializeFade(void)
{
	//�l�̏�����
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
//�X�V
//===================================================
void UpdateFade(void)
{
	//�t�F�[�h�A�E�g�̏���
	if (g_outTrigger && g_timeCntIn == 0)
	{
		g_timeCntOut++;
		//����
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
		//�E��
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
	//�t�F�[�h�C������
	else if(g_inTrigger && g_timeCntOut == 0)
	{
		g_blacKOut = false;
		g_timeCntIn++;
		//����
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
		//�E��
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
//�`��
//===================================================
void DrawFade(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeFade(void)
{
	closesound(g_fadeInSe);
	closesound(g_fadeOutSe);
}

//===================================================
//�t�F�[�h�A�E�g�̃Z�b�g
//===================================================
void SetFadeOut(void)
{//��ʊO�ɔz�u
	if (!g_outTrigger && !g_blacKOut)//���s����Â��Ȃ��Ă�Ƃ��͎��s���Ȃ�
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
//�t�F�[�h�C���̃Z�b�g
//===================================================
void SetFadeIn(void)
{
	playsound(g_fadeInSe, 0);
	g_timeCntIn = 0;
	g_inTrigger = true;
}

//===================================================
//�Ó]�̃A�h���X�擾
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