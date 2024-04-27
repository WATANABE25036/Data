//===================================================
//�����A�j���[�V��������[explosion.cpp]
//Author:�n� �C	Date:2023.1.19
//===================================================
#include "explosion.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
EXPLOSION g_explosion[MAX_EXPLOSION]; //����(�v�[�����O)

//===================================================
//������
//===================================================
void InitializeExplosion(void)
{
	//�l�̏�����
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		g_explosion[i].xPos = g_explosion[i].oldXPos = 0.0f;
		g_explosion[i].yPos = g_explosion[i].oldYPos = 0.0f;
		g_explosion[i].xSpeed = 0.0f;
		g_explosion[i].ySpeed = 0.0f;
		g_explosion[i].isUse = false;
		g_explosion[i].frameCut = 0;
	}
}

//===================================================
//�X�V
//===================================================
void UpdateExplosion(void)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (g_explosion[i].isUse)
		{
			//�O�t���[���̍��W���i�[
			g_explosion[i].oldXPos = g_explosion[i].xPos;
			g_explosion[i].oldYPos = g_explosion[i].yPos;

			//�ړ�
			g_explosion[i].xPos += g_explosion[i].xSpeed;
			g_explosion[i].yPos += g_explosion[i].ySpeed;

			//�t���[���J�E���^�[��i�߂�
			g_explosion[i].frameCut++;

			if (g_explosion[i].frameCut > ANIMATION_FRAME_EXPLOSION * ANIMATION_FRAME_MAX_EXPLOSION)
			{
				g_explosion[i].isUse = false;
			}
		}
		else
		{
			//�g���I������珉����
			g_explosion[i].frameCut = 0;
			g_explosion[i].xPos = g_explosion[i].oldXPos = 0.0f;
			g_explosion[i].yPos = g_explosion[i].oldYPos = 0.0f;
			g_explosion[i].xSpeed = 0.0f;
			g_explosion[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//�`��
//===================================================
void DrawExplosion(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeExplosion(void)
{

}

//===================================================
//�����A�j���[�V�����̃Z�b�g(�Z�b�^�[)
//===================================================
void SetExplosion(float px, float py, float sx, float sy)
{
	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		if (!g_explosion[i].isUse)
		{
			g_explosion[i].xPos = g_explosion[i].oldXPos = px;
			g_explosion[i].yPos = g_explosion[i].oldYPos = py;
			g_explosion[i].xSpeed = sx;
			g_explosion[i].ySpeed = sy;
			g_explosion[i].isUse = true;

			break;
		}
	}
}

//===================================================
//�����̃A�h���X���擾
//===================================================
EXPLOSION* GetExplosion(void)
{
	return g_explosion;
}