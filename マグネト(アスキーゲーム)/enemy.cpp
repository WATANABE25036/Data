//===================================================
//�G����[enemy.cpp]
//Author:�n� �C	Date:2023.1.17
//===================================================
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "drawing.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
ENEMY g_enemy[MAX_ENEMY];	//����(�v�[�����O)
int g_timeCntEnemy;				//���ԃJ�E���^�[

//===================================================
//������
//===================================================
void InitializeEnemy(void)
{
	//�l�̏�����
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		g_enemy[i].xPos = g_enemy[i].oldXPos = 0.0f;
		g_enemy[i].yPos = g_enemy[i].oldYPos = 0.0f;
		g_enemy[i].xSpeed = 0.0f;
		g_enemy[i].ySpeed = 0.0f;
		g_enemy[i].moveTime = 0;
		g_enemy[i].isUse = false;
	}

	g_timeCntEnemy = 0;

	//SetEnemy(25.0f, 3.0f);
	//SetEnemy(25.0f, 4.0f);
	//SetEnemy(25.0f, 5.0f);
	//SetEnemy(25.0f, 6.0f);
	//SetEnemy(25.0f, 7.0f);
	//SetEnemy(25.0f, 8.0f);
	//SetEnemy(25.0f, 9.0f);
	//SetEnemy(25.0f, 10.0f);
	//SetEnemy(25.0f, 11.0f);

	//SetEnemy(28.0f, 3.0f);
	//SetEnemy(28.0f, 4.0f);
	//SetEnemy(28.0f, 5.0f);
	//SetEnemy(28.0f, 6.0f);
	//SetEnemy(28.0f, 7.0f);
	//SetEnemy(28.0f, 8.0f);
	//SetEnemy(28.0f, 9.0f);
	//SetEnemy(28.0f, 10.0f);
	//SetEnemy(28.0f, 11.0f);

	//SetEnemy(31.0f, 3.0f);
	//SetEnemy(31.0f, 4.0f);
	//SetEnemy(31.0f, 5.0f);
	//SetEnemy(31.0f, 6.0f);
	//SetEnemy(31.0f, 7.0f);
	//SetEnemy(31.0f, 8.0f);
	//SetEnemy(31.0f, 9.0f);
	//SetEnemy(31.0f, 10.0f);
	//SetEnemy(31.0f, 11.0f);

	//SetEnemy(34.0f, 3.0f);
	//SetEnemy(34.0f, 4.0f);
	//SetEnemy(34.0f, 5.0f);
	//SetEnemy(34.0f, 6.0f);
	//SetEnemy(34.0f, 7.0f);
	//SetEnemy(34.0f, 8.0f);
	//SetEnemy(34.0f, 9.0f);
	//SetEnemy(34.0f, 10.0f);
	//SetEnemy(34.0f, 11.0f);

	//SetEnemy(37.0f, 3.0f);
	//SetEnemy(37.0f, 4.0f);
	//SetEnemy(37.0f, 5.0f);
	//SetEnemy(37.0f, 6.0f);
	//SetEnemy(37.0f, 7.0f);
	//SetEnemy(37.0f, 8.0f);
	//SetEnemy(37.0f, 9.0f);
	//SetEnemy(37.0f, 10.0f);
	//SetEnemy(37.0f, 11.0f);

	//SetEnemy(40.0f, 3.0f);
	//SetEnemy(40.0f, 4.0f);
	//SetEnemy(40.0f, 5.0f);
	//SetEnemy(40.0f, 6.0f);
	//SetEnemy(40.0f, 7.0f);
	//SetEnemy(40.0f, 8.0f);
	//SetEnemy(40.0f, 9.0f);
	//SetEnemy(40.0f, 10.0f);
	//SetEnemy(40.0f, 11.0f);
}

//===================================================
//�X�V
//===================================================
void UpdateEnemy(void)
{
	//���Ԍo�߂œG���Z�b�g
	g_timeCntEnemy++;
	
	//switch (g_timeCntEnemy)
	//{
	//case 2:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 3:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 4:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 5:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 6:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 7:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//case 300:
	//	SetEnemy(50.0f, 10.0f, -0.1f, 1.0f);
	//	break;
	//default:
	//	break;
	//}

	//�G�̓���
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_enemy[i].isUse)
		{
			//�O�t���[���̍��W���i�[
			g_enemy[i].oldXPos = g_enemy[i].xPos;
			g_enemy[i].oldYPos = g_enemy[i].yPos;

			g_enemy[i].xSpeed = cosf(g_enemy[i].moveTime * 0.5f) * 2.0f;
			//g_enemy[i].xSpeed = sinf(g_enemy[i].moveTime * 0.1f) * 0.1f;
			g_enemy[i].moveTime++;

			//�ړ�
			g_enemy[i].xPos += g_enemy[i].xSpeed;
			g_enemy[i].yPos += g_enemy[i].ySpeed;
			//�O�ʒ[�ňړ��������]
			if (g_enemy[i].yPos > DRAWING_HEIGHT_MAX - 2)
			{
				g_enemy[i].ySpeed = -g_enemy[i].ySpeed;
			}

			if (g_enemy[i].yPos < 1 + 1)
			{
				g_enemy[i].ySpeed = -g_enemy[i].ySpeed;
			}

			//��ʊO�ɏo�������
			if (g_enemy[i].xPos <= DRAWING_WIDTHW_MIN || g_enemy[i].xPos >= DRAWING_WIDTHW_MAX||
				g_enemy[i].yPos <= DRAWING_HEIGHT_MIN || g_enemy[i].yPos >= DRAWING_HEIGHT_MAX)
			{
				g_enemy[i].isUse = false;
				continue;//����̃��[�v���X�L�b�v����
			}

			//�e�̓����蔻�菈��
			BULLET* pBullet = GetBullet(); //�e�̐擪�A�h���X���擾

			//�e�̃��[�v�J�E���^�[ �� j
			for (int j = 0; j < MAX_BULLET; j++)
			{
				if ((pBullet + j)->isUse)
				{
					//�e�ƓG��int�^�Ƃ��đO�̍��W�`���̍��W�ɏd�Ȃ�����
					if (g_enemy[i].xPos <= (pBullet + j)->xPos && g_enemy[i].xPos >= (pBullet + j)->oldXPos &&
						(int)g_enemy[i].yPos == (int)(pBullet + j)->yPos ||
						g_enemy[i].xPos >= (pBullet + j)->xPos && g_enemy[i].xPos <= (pBullet + j)->oldXPos &&
						(int)g_enemy[i].yPos == (int)(pBullet + j)->yPos)
					{
						//�ǂ��������
						//�G����
						g_enemy[i].isUse = false;

						//�e����
						(pBullet + j)->isUse = false;

						//�����A�j���[�V�����̃Z�b�g
						SetExplosion(g_enemy[i].xPos, g_enemy[i].yPos);

						//�X�R�A�����Z
						AddScore(50000);
					}
				}
			}
		}
		else
		{
			//�g���I������珉����
			g_enemy[i].xPos = g_enemy[i].oldXPos = 0.0f;
			g_enemy[i].yPos = g_enemy[i].oldYPos = 0.0f;
			g_enemy[i].xSpeed = 0.0f;
			g_enemy[i].ySpeed = 0.0f;
		}
	}
}

//===================================================
//�`��
//===================================================
void DrawEnemy(void)
{

}

//===================================================
//�I������
//===================================================
void FinalizeEnemy(void)
{

}

//===================================================
//�G�̃Z�b�g(�Z�b�^�[)
//===================================================
void SetEnemy(float px, float py, float sx, float sy)
{
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (!g_enemy[i].isUse)
		{
			g_enemy[i].xPos = g_enemy[i].oldXPos = px;
			g_enemy[i].yPos = g_enemy[i].oldYPos = py;
			g_enemy[i].xSpeed = sx;
			g_enemy[i].ySpeed = sy;
			g_enemy[i].isUse = true;

			break;
		}
	}
}

//===================================================
//�G�l�~�[�A�h���X�擾
//===================================================
ENEMY* GetEnemy(void)
{
	return g_enemy;
}