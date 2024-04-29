//===================================================
//�v���C���[(player.cpp)
//Auhor:�n� �C	Date:2023.7.6
//===================================================
#include <random>
#include "player.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "wall.h"
#include "barrier.h"
#include "dead.h"
#include "main.h"
#include "score.h"
#include "fade.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static int g_SE_crushed_tomato;
static int g_SE_move;
static int g_SE_drop;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static bool g_hit;
static bool g_dead;
static int g_ToResultCou;
static bool g_barrierRange;
static bool g_oldBarrierRange;
static bool g_control;
static int g_randomMoveCou;
static int g_scoreCou;
static int g_moveSeCou;
static bool g_invincible;
static PLAYER	g_Player[PLAYER_MAX];
static BARRIER* p_Barrier;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitPlayer(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/tmt.png");
	//���ʉ��쐬
	char se1[] =
	{
		"data\\SE\\crushed_tomato.wav"
	};
	g_SE_crushed_tomato = LoadSound(&se1[0]);

	char se2[] =
	{
		"data\\SE\\move.wav"
	};
	g_SE_move = LoadSound(&se2[0]);

	char se3[] =
	{
		"data\\SE\\drop.wav"
	};
	g_SE_drop = LoadSound(&se3[0]);

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		g_Player[i].pos.x = SCREEN_WIDTH / 2;
		g_Player[i].pos.y = SCREEN_HEIGHT / 2;
		g_Player[i].oldPos.x = g_Player[i].pos.x;
		g_Player[i].oldPos.y = g_Player[i].pos.y;
		g_Player[i].dir = 4;//������
		g_Player[i].vel.x = PLAYER_SPEED;
		g_Player[i].vel.y = PLAYER_SPEED;
		//�x�N�g���̐��K��
		D3DXVec2Normalize(&g_Player[i].vel, &g_Player[i].vel);
		g_Player[i].vel *= PLAYER_SPEED;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����
		g_Player[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Player[i].dis = PLAYER_START_DIS;
		g_Player[i].disRate = 1.0f;
		g_Player[i].initSize = D3DXVECTOR2(0.0f, 0.0f);
	}

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / PLAYER_WIDTH_PATTERN;
	g_VH = 1.0f / PLAYER_HEIGHT_PATTERN;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
	g_AnimeSkipFrameFloat = 0;
	g_hit = false;
	g_ToResultCou = 0;

	g_Player[0].size = D3DXVECTOR2(200.0f, 200.0f);
	g_Player[0].use = true;
	g_barrierRange = false;
	g_control = false;
	g_randomMoveCou = 0;
	g_dead = false;
	g_moveSeCou = 0;
	g_AnimeBasePattern = 0;

	//��������ʉ�
	PlaySound(g_SE_drop, 0);
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdatePlayer(void)
{
	//���Z�b�g
	if (GetKeyboardPress(DIK_R))
	{
		SetScene(SCENE_GAME);
	}

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use)
		{
			//UV�A�j���[�V����
			//      w             N % ���̃p�^�[����
			g_U = (1.0f / PLAYER_WIDTH_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) % PLAYER_WIDTH_PATTERN);	//���̍��W�v�Z
			//     H              N / ���̃p�^�[����
			g_V = (1.0f / PLAYER_HEIGHT_PATTERN) * ((g_AnimePattern + g_AnimeBasePattern) / PLAYER_WIDTH_PATTERN); //�c�̍��W�v�Z

			//�J�E���^�[�𐮐��ł��ꍇ�̗�1
			g_AnimeSkipFrame++;
			if (g_AnimeSkipFrame > PLAYER_FRAME_SPAN)
			{
				g_AnimeSkipFrame = 0;
				g_AnimePattern++;

				if (g_AnimePattern > PLAYER_FRAME_MAX)
				{
					g_AnimePattern = 0;
				}
			}

			//�O�t���[���̍��W������
			g_Player[0].oldPos.x = g_Player[0].pos.x;
			g_Player[0].oldPos.y = g_Player[0].pos.y;

			//�X�s�[�h����
			g_Player[0].vel.x = 0.0f;
			g_Player[0].vel.y = 0.0f;

			g_Player[0].speed = 1 + (PLAYER_SPEED * (g_Player[0].disRate * PLAYER_DIS_SPEED_RATE));

			//�L�[���͂ňړ��l�����߂�
			if (g_control)
			{
				g_moveSeCou--;
				if (GetKeyboardPress(DIK_A))
				{
					if (g_moveSeCou <= 0)
					{
						PlaySound(g_SE_move, 0);
						g_moveSeCou = PLAYER_MOVE_SE_SPZN;
					}
					g_Player[0].vel.x = -g_Player[0].speed;
				}

				if (GetKeyboardPress(DIK_D))
				{
					if (g_moveSeCou <= 0)
					{
						PlaySound(g_SE_move, 0);
						g_moveSeCou = PLAYER_MOVE_SE_SPZN;
					}
					g_Player[0].vel.x = g_Player[0].speed;
				}

				if (GetKeyboardPress(DIK_W))
				{
					if (g_moveSeCou <= 0)
					{
						PlaySound(g_SE_move, 0);
						g_moveSeCou = PLAYER_MOVE_SE_SPZN;
					}
					g_Player[0].vel.y = -g_Player[0].speed;
				}

				if (GetKeyboardPress(DIK_S))
				{
					if (g_moveSeCou <= 0)
					{
						PlaySound(g_SE_move, 0);
						g_moveSeCou = PLAYER_MOVE_SE_SPZN;
					}
					g_Player[0].vel.y = g_Player[0].speed;
				}

				//���G���[�h
				//{
				//	if (GetKeyboardTrigger(DIK_SPACE))
				//	{
				//		if (g_invincible)g_invincible = false;
				//		else if (!g_invincible)g_invincible = true;
				//	}
				//}

				//���߈ړ�
				//if (GetKeyboardPress(DIK_E))
				//{
				//	PlaySound(g_SE_move, 0);
				//	g_Player[0].dis += 0.01f;
				//}
				//if (GetKeyboardPress(DIK_Q))
				//{
				//	PlaySound(g_SE_move, 0);
				//	g_Player[0].dis -= 0.01f;
				//}

				//����������������
				g_randomMoveCou++;
				if (g_randomMoveCou >= RANDOM_MOVE_SPAN)
				{
					std::random_device rd;
					std::uniform_real_distribution<> dist1(-2.0f, 2.0f);
					float ran1 = dist1(rd);
					g_Player[0].vel.x += ran1;

					std::uniform_real_distribution<> dist2(-2.0f, 2.0f);
					float ran2 = dist2(rd);
					g_Player[0].vel.y += ran2;

					g_randomMoveCou = 0;
				}
			}

			//�X�^�[�g���̉��o
			if (g_Player[0].dis > PLAYER_DEFAULT_DIS)
			{
				g_Player[0].dis -= PLAYER_DEFAULT_DIS_MOVE_SPEED;
				//�ڕW�̋����ɒ�������
				if ((g_Player[0].dis - PLAYER_DEFAULT_DIS_MOVE_SPEED) < PLAYER_DEFAULT_DIS)
				{
					g_Player[0].dis = PLAYER_DEFAULT_DIS;
					g_control = true;
				}
			}

			//�L�����N�^�[�̈ړ�
			D3DXVec2Normalize(&g_Player[0].vel, &g_Player[0].vel);//�x�N�g���̐��K��
			g_Player[0].vel *= g_Player[0].speed;//���K���x�N�g�����X�s�[�h�l�ŃX�P�[�����O
			g_Player[0].pos += g_Player[0].vel;

			//�v���C���[�̉��ߋ���
			g_Player[0].disRate = PLAYER_BASE_ZOOM_RATE * pow(PLAYER_ADD_ZOOM_RATE, g_Player[0].dis);

			g_Player[0].size.x = g_Player[0].initSize.x + (PLAYER_WIDTH_MAX - g_Player[0].initSize.x) * g_Player[0].disRate;
			g_Player[0].size.y = g_Player[0].initSize.y + (PLAYER_HEIGHT_MAX - g_Player[0].initSize.y) * g_Player[0].disRate;

			//��ǂ̓����蔻��
			g_oldBarrierRange = g_barrierRange;
			g_barrierRange = false;
			p_Barrier = GetBarrier();
			for (int j = 0; j < BARRIER_MAX; j++)
			{
				if (p_Barrier[j].use == false) continue;

				//�w�苗�����ɂȂ�����
				if (g_Player[0].disRate < p_Barrier[j].disRate + PLAYER_HET_RANGE && g_Player[0].disRate > p_Barrier[j].disRate - 0.05f + PLAYER_HET_RANGE)
				{
					g_barrierRange = true;

					//�����蔻��
					if (CollisionRot(g_Player[0].pos, p_Barrier[j].pos, g_Player[0].size * PLAYER_HET_SIZE, p_Barrier[j].size, p_Barrier[j].rot) && !g_invincible)
					{
						g_hit = true;
					}
				}
			}

			//�q�b�g���̏���
			if (g_hit)
			{
				g_Player[0].use = false;
				SetDead(g_Player[0].pos);
				StopWall();
				StopBarrier();
				PlaySound(g_SE_crushed_tomato, 0);
				g_dead = true;
			}

			//��ǂƓ��������ɂȂ����Ƃ����݂̂̏���
			if (g_barrierRange == true && g_oldBarrierRange == false)
			{
				/*PlaySound(g_SE_move, 0);*/
			}

			//�X�R�A����
			g_scoreCou++;
			if (g_scoreCou == 6)
			{
				AddScore(1);
				g_scoreCou = 0;
			}

			//��O�ݒ�@�␳�l0.34f
			if (g_Player[0].pos.x > SCREEN_WIDTH * (g_Player[0].disRate + 0.34f) || g_Player[0].pos.x < SCREEN_WIDTH - (SCREEN_WIDTH * (g_Player[0].disRate + 0.34f)))
			{
				g_Player[0].pos.x = g_Player[0].oldPos.x;
			}

			if (g_Player[0].pos.y > SCREEN_HEIGHT * (g_Player[0].disRate + 0.34f) || g_Player[0].pos.y < SCREEN_HEIGHT - (SCREEN_HEIGHT * (g_Player[0].disRate + 0.34f)))
			{
				g_Player[0].pos.y = g_Player[0].oldPos.y;
			}
		}

		//�Q�[���I�[�o�[���̏���
		if (g_dead)
		{
			g_ToResultCou++;

			if (g_ToResultCou >= 60 * 2)
			{
				SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
				SetFadeTime(120.0f);//time:���t���[���Ńt�F�[�h�������������������H
				SetFade(FADE_STATE_OUT);//�t�F�[�h�A�E�g�J�n���N�G�X�g
				SceneTransition(SCENE_RESULT);
			}
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawPlayer(void)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (g_Player[i].use)
		{
			DrawSprite(g_TexNo,
				g_Player[i].pos.x,
				g_Player[i].pos.y,
				g_Player[i].size.x, g_Player[i].size.y,	//���A����
				g_U, g_V,		//���SUV���W
				g_UW, g_VH	//�e�N�X�`�����A����
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitPlayer(void)
{

}

//---------------------------------------------------
// �v���C���[�擾����
//---------------------------------------------------
PLAYER* GetPlayer()
{
	return &g_Player[0];
}