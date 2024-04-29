//===================================================
//����(dead.cpp)
//Auhor:�n� �C	Date:2023.8.1
//===================================================
#include "dead.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "wall.h"
#include "barrier.h"
#include "player.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static bool g_hit;
static DEAD	g_Dead[DEAD_MAX];
static BARRIER* p_Barrier;
static PLAYER* p_Player;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitDead(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/crushed_tomato.png");

	//������
	for (int i = 0; i <DEAD_MAX; i++)
	{
		g_Dead[i].pos.x = SCREEN_WIDTH / 2;
		g_Dead[i].pos.y = SCREEN_HEIGHT / 2;
		g_Dead[i].oldPos.x = g_Dead[i].pos.x;
		g_Dead[i].oldPos.y = g_Dead[i].pos.y;
		g_Dead[i].dir = 4;//������
		g_Dead[i].vel.x =DEAD_SPEED;
		g_Dead[i].vel.y =DEAD_SPEED;
		//�x�N�g���̐��K��
		D3DXVec2Normalize(&g_Dead[i].vel, &g_Dead[i].vel);
		g_Dead[i].vel *=DEAD_SPEED;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����
		g_Dead[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Dead[i].dis = 1.0f;
		g_Dead[i].BufferIndex = i *DEAD_FOLLOW_SPAN;//�����O�o�b�t�@�̎Q�Əꏊ��������
		g_Dead[i].disRate = 1.0f;
		g_Dead[i].initSize = D3DXVECTOR2(0.0f, 0.0f);
		g_Dead[i].size = D3DXVECTOR2(200.0f, 200.0f);
		g_Dead[i].use = false;
	}

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / DEAD_WIDTH_PATTERN;
	g_VH = 1.0f / DEAD_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
	g_AnimeSkipFrameFloat = 0;
	g_hit = false;
	g_AnimeBasePattern = 0;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateDead(void)
{
	for (int i = 0; i < DEAD_MAX; i++)
	{
		if (g_Dead[i].use)
		{
			p_Player = GetPlayer();

			//UV�A�j���[�V����
			//      w             N % ���̃p�^�[����
			g_U = (1.0f / DEAD_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % DEAD_WIDTH_PATTERN);	//���̍��W�v�Z
			//     H              N / ���̃p�^�[����
			g_V = (1.0f / DEAD_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / DEAD_WIDTH_PATTERN); //�c�̍��W�v�Z

			//�J�E���^�[�𐮐��ł��ꍇ�̗�1
			g_AnimeSkipFrame++;

			if (g_AnimeSkipFrame > DEAD_FRAME_SPAN)
			{
				g_AnimeSkipFrame = 0;
				g_AnimePattern++;

				if (g_AnimePattern > DEAD_FRAME_MAX)
				{
					g_AnimePattern = DEAD_FRAME_MAX;
				}
			}

			//�O�t���[���̍��W������
			g_Dead[i].oldPos.x = g_Dead[i].pos.x;
			g_Dead[i].oldPos.y = g_Dead[i].pos.y;

			//�X�s�[�h����
			g_Dead[i].vel.x = 0.0f;
			g_Dead[i].vel.y = 0.0f;

			g_Dead[i].speed = 1 + (DEAD_SPEED * (g_Dead[i].disRate * DEAD_DIS_SPEED_RATE));

			//�L�����N�^�[�̈ړ�
			D3DXVec2Normalize(&g_Dead[i].vel, &g_Dead[i].vel);//�x�N�g���̐��K��
			g_Dead[i].vel *= g_Dead[i].speed;//���K���x�N�g�����X�s�[�h�l�ŃX�P�[�����O
			g_Dead[i].pos += g_Dead[i].vel;

			//���̂̉��ߋ���
			g_Dead[i].dis = p_Player[0].dis;
			g_Dead[i].disRate = DEAD_BASE_ZOOM_RATE * pow(DEAD_ADD_ZOOM_RATE, g_Dead[i].dis);

			g_Dead[i].size.x = g_Dead[i].initSize.x + (DEAD_WIDTH_MAX - g_Dead[i].initSize.x) * g_Dead[i].disRate;
			g_Dead[i].size.y = g_Dead[i].initSize.y + (DEAD_HEIGHT_MAX - g_Dead[i].initSize.y) * g_Dead[i].disRate;

			//�����蔻��
			//���
			p_Barrier = GetBarrier();
			g_hit = false;
			for (int j = 0; j < BARRIER_MAX; j++)
			{
				if (p_Barrier[j].use == false) continue;

				//�w�苗�����ɂȂ�����
				if (g_Dead[i].disRate < p_Barrier[j].disRate + PLAYER_HET_RANGE && g_Dead[i].disRate > p_Barrier[j].disRate - 0.05f + PLAYER_HET_RANGE)
				{
					if (CollisionRot(g_Dead[i].pos, p_Barrier[j].pos, g_Dead[i].size / 3, p_Barrier[j].size, p_Barrier[j].rot))
					{
						g_hit = true;
					}
				}
			}

			//��O�ݒ�
			if (g_Dead[i].pos.x > SCREEN_WIDTH * (g_Dead[i].disRate + 0.5f) || g_Dead[i].pos.x < SCREEN_WIDTH - (SCREEN_WIDTH * (g_Dead[i].disRate + 0.5f)))
			{
				g_Dead[i].pos.x = g_Dead[i].oldPos.x;
			}

			if (g_Dead[i].pos.y > SCREEN_HEIGHT * (g_Dead[i].disRate + 0.5f) || g_Dead[i].pos.y < SCREEN_HEIGHT - (SCREEN_HEIGHT * (g_Dead[i].disRate + 0.5f)))
			{
				g_Dead[i].pos.y = g_Dead[i].oldPos.y;
			}			
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawDead(void)
{
	for (int i = 0; i <DEAD_MAX; i++)
	{
		if (g_Dead[i].use)
		{
			DrawSprite(g_TexNo,
				g_Dead[i].pos.x,
				g_Dead[i].pos.y,
				g_Dead[i].size.x * 2, g_Dead[i].size.y * 2,	//���A����
				g_U, g_V,		//���SUV���W
				g_UW, g_VH		//�e�N�X�`�����A����
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitDead(void)
{

}

//---------------------------------------------------
// ���̎擾����
//---------------------------------------------------
DEAD* GetDead()
{
	return &g_Dead[0];
}

//---------------------------------------------------
// ���̐ݒu
//---------------------------------------------------
void SetDead(D3DXVECTOR2 pos)
{
	for (int i = 0; i < DEAD_MAX; i++)
	{
		if (g_Dead[i].use != TRUE)//���g�p�̔z�������
		{
			g_Dead[i].pos = pos;//�\�����W
			g_Dead[i].use = TRUE;//�g�p���ɂ���
			break;//�I��
		}
	}
}