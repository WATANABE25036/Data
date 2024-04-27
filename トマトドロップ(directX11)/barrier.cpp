//===================================================
//���(barrier.cpp)
//Auhor:�n� �C	Date:2023.7.11
//===================================================
#include <stdlib.h>
#include <random>
#include "barrier.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "wall.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static float g_U;
static float g_V;
static float g_add;//��ǂ��߂Â�����
static BARRIER	g_Barrier[BARRIER_MAX];
static PLAYER* p_Player;
static WALL* p_Wall;

//�N�C�b�N�\�[�g�Ŏg�p
int cmpBarrierSize(const void* n1, const void* n2)
{
	if (((BARRIER*)n1)->size.x > ((BARRIER*)n2)->size.x)
	{
		return 1;
	}
	else if (((BARRIER*)n1)->size.x < ((BARRIER*)n2)->size.x)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

//---------------------------------------------------
//������
//---------------------------------------------------
void InitBarrier(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/barrier.png");

	//������
	for (int i = 0; i < BARRIER_MAX; i++)
	{
		g_Barrier[i].pos = D3DXVECTOR2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
		g_Barrier[i].oldPos = g_Barrier[i].pos;
		g_Barrier[i].vel = D3DXVECTOR2(WALL_SPEED, WALL_SPEED);
		g_Barrier[i].speed = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrier[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, BARRIER_DEFAULT_ALPHA);
		g_Barrier[i].use = false;
		g_Barrier[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrier[i].oldSize = g_Barrier[i].size;
		g_Barrier[i].dis = 0.0f;
		g_Barrier[i].disRate = 0.0f;
		g_Barrier[i].g_num = 0;
		g_Barrier[i].rot = 0;
		g_Barrier[i].initSize = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrier[i].initPos = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrier[i].maxSize = D3DXVECTOR2(0.0f, 0.0f);
		g_Barrier[i].rotSpeed = 0.0f;
		g_Barrier[i].adjVel = D3DXVECTOR2(0.0f, 0.0f);
	}

	//�O���[�o���ϐ�������
	g_U = BARRIER_WIDTH * 0.5f;
	g_V = BARRIER_HEIGHT * 0.5f;
	g_add = WALL_ZOOM_SPEED;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateBarrier(void)
{
	for (int i = 0; i < BARRIER_MAX; i++)
	{
		if (g_Barrier[i].use)//�g�p���Ȃ珈������
		{
			p_Player = GetPlayer();
			p_Wall = GetWall();
			//g_Barrier[i].vel = { 0,0 };
			g_Barrier[i].oldSize = g_Barrier[i].size;
			g_Barrier[i].oldPos = g_Barrier[i].pos;

			for (int j = 0; j < WALL_MAX; j++)
			{
				//��O�Ɉړ����铮���̏���
				if (g_Barrier[i].g_num == p_Wall[j].g_num)
				{
					//�ǂ̋�������ǂ̋����ɂ���
					g_Barrier[i].dis = p_Wall[j].dis;
					g_Barrier[i].disRate = p_Wall[j].disRate;

					//���Ԋu�ő傫�����Ă���
					g_Barrier[i].size.x = g_Barrier[i].maxSize.x * g_Barrier[i].disRate;
					g_Barrier[i].size.y = g_Barrier[i].maxSize.y * g_Barrier[i].disRate;

					//�ǂ̑傫���ɍ��킹�đ傫�����Ă���
					//g_Barrier[i].size.x = g_Barrier[i].initSize.x * (p_Wall[j].size.x / p_Wall[j].initSize.x);
					//g_Barrier[i].size.y = g_Barrier[i].initSize.y * (p_Wall[j].size.y / p_Wall[j].initSize.y);

					//���W��ǂɍ��킹�Ĉړ�������
					g_Barrier[i].pos.x += ((p_Wall[j].size.x * 0.5f) * ((g_Barrier[i].initPos.x - p_Wall[j].initPos.x) / (p_Wall[j].initSize.x * 0.5f))) - ((p_Wall[j].oldSize.x * 0.5f) * ((g_Barrier[i].initPos.x - p_Wall[j].initPos.x) / (p_Wall[j].initSize.x * 0.5f)));
					g_Barrier[i].pos.y += ((p_Wall[j].size.y * 0.5f) * ((g_Barrier[i].initPos.y - p_Wall[j].initPos.y) / (p_Wall[j].initSize.y * 0.5f))) - ((p_Wall[j].oldSize.y * 0.5f) * ((g_Barrier[i].initPos.y - p_Wall[j].initPos.y) / (p_Wall[j].initSize.y * 0.5f)));

					//�ړ�����
					g_Barrier[i].vel.x += g_Barrier[i].speed.x * g_Barrier[i].disRate;
					g_Barrier[i].vel.y += g_Barrier[i].speed.y * g_Barrier[i].disRate;

					g_Barrier[i].pos += g_Barrier[i].vel;

					break;
				}
			}

			//�v���C���[�̈ʒu�ɑ΂��铮���̏���
			if (p_Player->use)
			{
				//			 �T�C�Y���傫���قǑ傫���ړ�����	�v���C���[�̈ʒu�ɍ��킹�ē�����
				g_Barrier[i].adjVel.x = g_Barrier[i].disRate * ((SCREEN_WIDTH_HALF - p_Player->pos.x) * WALL_SPEED);
				g_Barrier[i].adjVel.y = g_Barrier[i].disRate * ((SCREEN_HEIGHT_HALF - p_Player->pos.y) * WALL_SPEED);
				//�����������͐؂�̂Ă�
				g_Barrier[i].adjVel.x = floor(g_Barrier[i].adjVel.x * 10) / 10;
				g_Barrier[i].adjVel.y = floor(g_Barrier[i].adjVel.y * 10) / 10;

				g_Barrier[i].pos += g_Barrier[i].adjVel;
			}

			//��]����
			g_Barrier[i].rot += g_Barrier[i].rotSpeed;

			//��ʊO�ɂȂ��������
			if (g_Barrier[i].disRate > 1.0f)//1��0.6(�g�}�g���߂���Ƃ���������)
			{
				g_Barrier[i].color.a = g_Barrier[i].color.a - 0.1f;

				if (g_Barrier[i].color.a <= 0)
				{
					g_Barrier[i].use = false;
				}
			}
			else
			{
				//�ǐݒu����A���t�@���グ�Ă���
				if (g_Barrier[i].color.a < BARRIER_DEFAULT_ALPHA)
				{
					g_Barrier[i].color.a += WALL_ALPHA_ADD;
					if (g_Barrier[i].color.a > BARRIER_DEFAULT_ALPHA)g_Barrier[i].color.a = BARRIER_DEFAULT_ALPHA;
				}
			}
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawBarrier(int g_num)
{
	for (int i = 0; i < BARRIER_MAX; i++)
	{
		if (g_Barrier[i].use)
		{
			if (g_Barrier[i].g_num == g_num)
			{
				DrawSpriteColorRotate(g_TexNo,
					g_Barrier[i].pos.x,
					g_Barrier[i].pos.y,
					g_Barrier[i].size.x, g_Barrier[i].size.y,	//���A����
					g_U, g_V,	//���SUV���W
					1, 1,		//�e�N�X�`�����A����
					g_Barrier[i].color.r, g_Barrier[i].color.g, g_Barrier[i].color.b, g_Barrier[i].color.a,
					g_Barrier[i].rot	//�p�x
				);
				break;
			}
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitBarrier(void)
{

}

//---------------------------------------------------
// ��ǎ擾����
//---------------------------------------------------
BARRIER* GetBarrier()
{
	return g_Barrier;
}

//---------------------------------------------------
// ��ǂ��Z�b�g
// �ǂ̔ԍ�, �|�W�V����(�ǂɑ΂��銄���Ŏw�� ��:0�Ő^��, 1�ŉE�[), �T�C�Y(�ő�T�C�Y)
//---------------------------------------------------
void SetBarrier(int wallNum, float posX, float posY, float sizeX, float sizeY, float rot, int color, float speedX, float speedY, float rotSpeed)
{
	for (int i = 0; i < BARRIER_MAX; i++)
	{
		if (g_Barrier[i].use == false)//���g�p�̔z�������
		{
			p_Wall = GetWall();

			g_Barrier[i].size.x = sizeX;
			g_Barrier[i].size.y = sizeY;
			g_Barrier[i].oldSize = g_Barrier[i].size;
			g_Barrier[i].initSize = g_Barrier[i].size;
			g_Barrier[i].maxSize.x = sizeX;
			g_Barrier[i].maxSize.y = sizeY;
			g_Barrier[i].dis = 0.0f;
			g_Barrier[i].disRate = 0.0f;
			g_Barrier[i].g_num = wallNum;
			g_Barrier[i].rot = rot;
			g_Barrier[i].speed = D3DXVECTOR2(speedX, speedY);
			g_Barrier[i].rotSpeed = rotSpeed;
			g_Barrier[i].vel = D3DXVECTOR2(0.0f, 0.0f);
			g_Barrier[i].adjVel = D3DXVECTOR2(0.0f, 0.0f);

			g_Barrier[i].pos.x = posX;
			g_Barrier[i].pos.y = posY;
			for (int j = 0; j < WALL_MAX; j++)
			{
				if (p_Wall[j].g_num == g_Barrier[i].g_num)
				{
					g_Barrier[i].pos += p_Wall[j].pos;
					break;
				}
			}

			g_Barrier[i].initPos = g_Barrier[i].pos;
			g_Barrier[i].oldPos = g_Barrier[i].pos;

			if (color == BARRIER_COLOR_RANDOM)
			{
				std::random_device rd;
				std::uniform_real_distribution<> dist1(0.0, 1.0);
				float ran1 = dist1(rd);
				g_Barrier[i].color.r = ran1;

				std::uniform_real_distribution<> dist2(0.0, 1.0);
				float ran2 = dist2(rd);
				g_Barrier[i].color.g = ran2;

				std::uniform_real_distribution<> dist3(0.0, 1.0);
				float ran3 = dist3(rd);
				g_Barrier[i].color.b = ran3;
			}
			else if (color == BARRIER_COLOR_RED)
			{
				g_Barrier[i].color.r = 1.0f;
				g_Barrier[i].color.g = 0.2f;
				g_Barrier[i].color.b = 0.2f;
			}
			else if (color == BARRIER_COLOR_GREEN)
			{
				g_Barrier[i].color.r = 0.2f;
				g_Barrier[i].color.g = 1.0f;
				g_Barrier[i].color.b = 0.2f;
			}
			else if (color == BARRIER_COLOR_BLUE)
			{
				g_Barrier[i].color.r = 0.2f;
				g_Barrier[i].color.g = 0.2f;
				g_Barrier[i].color.b = 1.0f;
			}
			else if (color == BARRIER_COLOR_YELLOW)
			{
				g_Barrier[i].color.r = 1.0f;
				g_Barrier[i].color.g = 1.0f;
				g_Barrier[i].color.b = 0.2f;
			}
			else if (color == BARRIER_COLOR_MAGENTA)
			{
				g_Barrier[i].color.r = 1.0f;
				g_Barrier[i].color.g = 0.2f;
				g_Barrier[i].color.b = 1.0f;
			}
			else if (color == BARRIER_COLOR_CYAN)
			{
				g_Barrier[i].color.r = 0.2f;
				g_Barrier[i].color.g = 1.0f;
				g_Barrier[i].color.b = 1.0f;
			}

			g_Barrier[i].color.a = 0.0f;
			g_Barrier[i].use = true;//�g�p���ɂ���

			break;
		}
	}
		qsort(g_Barrier, BARRIER_MAX, sizeof(BARRIER), cmpBarrierSize);//�N�C�b�N�\�[�g�Ŏ�O�̏�ǂ��ɕ\������
}

//---------------------------------------------------
// ��ǂ��~�߂�
//---------------------------------------------------
void StopBarrier()
{
	for (int i = 0; i < BARRIER_MAX; i++)
	{
		if (g_Barrier[i].use == true)
		{
			g_Barrier[i].dis = 0.0f;
			g_Barrier[i].vel = D3DXVECTOR2(0.0f, 0.0f);
			g_Barrier[i].speed = D3DXVECTOR2(0.0f, 0.0f);
			g_Barrier[i].rotSpeed = 0.0f;
		}
	}
}