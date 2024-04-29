//===================================================
//��(wall.cpp)
//Auhor:�n� �C	Date:2023.7.6
//===================================================
#include <stdlib.h>
#include <random>
#include "wall.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "barrier.h"
#include "fog.h"
#include "score.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static float g_U;
static float g_V;
static int g_wallSetCou;
static int g_num;
static int g_setLimit;
static bool g_move;
static int g_score;
static int g_oldBarrierRan;
static int g_barrierSetCou;
static int g_barrierSetCouPlus;
static int g_barrierCou;
static bool g_barrierCouTrigger;
static int g_ScoreAdd;
static int g_barrierSetCorrection;
static int g_barrierSetSpeedCou;
static bool g_allPatternClear;
static bool g_patternChange;
static WALL	g_Wall[WALL_MAX];
static PLAYER* p_Player;

//�N�C�b�N�\�[�g�Ŏg�p
int cmpWallSize(const void* n1, const void* n2)
{
	if (((WALL*)n1)->size.x > ((WALL*)n2)->size.x)
	{
		return 1;
	}
	else if (((WALL*)n1)->size.x < ((WALL*)n2)->size.x)
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
void InitWall(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/wall.png");

	//������
	for (int i = 0; i < WALL_MAX; i++)
	{
		g_Wall[i].pos = D3DXVECTOR2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
		g_Wall[i].vel = D3DXVECTOR2(WALL_SPEED, WALL_SPEED);
		g_Wall[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Wall[i].use = false;
		g_Wall[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Wall[i].oldSize = g_Wall[i].size;
		g_Wall[i].mode = WALL_NORMAL;
		g_Wall[i].dis = 0.0f;
		g_Wall[i].g_num = 0;
		g_Wall[i].initSize = D3DXVECTOR2(0.0f, 0.0f);
		g_Wall[i].disRate = 0;
		g_Wall[i].zoomSpeed = WALL_ZOOM_SPEED;
		g_Wall[i].initPos = D3DXVECTOR2(0.0f, 0.0f);
	}

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_move = true;
	g_barrierSetCou = 0;
	g_num = 0;
	g_wallSetCou = 0;
	g_score = 0;
	g_oldBarrierRan = 0;
	g_barrierSetCouPlus = 0;
	g_barrierCou = 0;
	g_barrierCouTrigger = false;
	g_ScoreAdd = 0;
	g_barrierSetCorrection = WALL_BARRIER_SET_SPEED;
	g_barrierSetSpeedCou = 0;
	g_allPatternClear = false;
	g_patternChange = false;
	g_setLimit = WALL_SET_SPEED;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateWall(void)
{
	if (g_move)
	{
		for (int i = 0; i < WALL_MAX; i++)
		{
			if (g_Wall[i].use)//�g�p���Ȃ珈������
			{
				g_Wall[i].oldSize = g_Wall[i].size;
				g_Wall[i].dis += g_Wall[i].zoomSpeed;

				g_Wall[i].disRate = BASE_ZOOM_RATE * pow(ADD_ZOOM_RATE, g_Wall[i].dis);

				g_Wall[i].size.x = g_Wall[i].initSize.x + (WALL_WIDTH_MAX - g_Wall[i].initSize.x) * g_Wall[i].disRate;
				g_Wall[i].size.y = g_Wall[i].initSize.y + (WALL_HEIGHT_MAX - g_Wall[i].initSize.y) * g_Wall[i].disRate;

				p_Player = GetPlayer();

				//�T�C�Y���傫���قǑ傫���ړ�����	�v���C���[�̈ʒu�ɍ��킹�ē�����
				if (p_Player->use)
				{
					g_Wall[i].vel.x = g_Wall[i].disRate * ((SCREEN_WIDTH_HALF - p_Player->pos.x) * WALL_SPEED);
					g_Wall[i].vel.y = g_Wall[i].disRate * ((SCREEN_HEIGHT_HALF - p_Player->pos.y) * WALL_SPEED);
					//�����������͐؂�̂Ă�
					g_Wall[i].vel.x = floor(g_Wall[i].vel.x * 10) / 10;
					g_Wall[i].vel.y = floor(g_Wall[i].vel.y * 10) / 10;

					g_Wall[i].pos += g_Wall[i].vel;
				}

				//�ǐݒu����A���t�@���グ�Ă���
				if (g_Wall[i].color.a < 1.0f)
				{
					g_Wall[i].color.a += WALL_ALPHA_ADD;
				}

				//��ʊO�ɂȂ��������
				if (g_Wall[i].disRate > 2)
				{
					g_Wall[i].use = false;
				}
			}
		}

		//�ǂ�z�u
		g_wallSetCou++;
		g_score = GetScore() % MAX_PATTERN_SCORE;
		g_score += g_ScoreAdd;//�p�^�[�������_����
		std::random_device rd;

		//3000�ȏ�Ŏ��s
		if ((GetScore() >= MAX_PATTERN_SCORE))
		{
			g_allPatternClear = true;
		}

		//���X�R�A���ƂɈ����s
		if (g_score % SCORE_FANFARE_SCORE == 0 && g_patternChange == false)
		{
			g_patternChange = true;
		}
		else if(g_score % SCORE_FANFARE_SCORE != 0)
		{
			g_patternChange = false;
		}

		if (g_patternChange == true)
		{
			g_barrierCou = 0;
			g_barrierCouTrigger = false;
			g_barrierSetCouPlus = 0;
			//�S�p�^�[���N���A��
			if (g_allPatternClear)
			{
				g_barrierSetSpeedCou++;

				//��ǔz�u��������
				if (g_barrierSetSpeedCou == 2)
				{
					g_barrierSetCorrection--;
					if (g_barrierSetCorrection < -10)g_barrierSetCorrection = -10;
					g_barrierSetSpeedCou = 0;
				}

				//�p�^�[�������_����
				std::uniform_int_distribution<> dist1(0, 3000);
				g_ScoreAdd = dist1(rd);
			}
			//SetScore(2800);//�e�X�g�p
		}
		//SetScore(2801);//�X�R�A�Œ肵�ăe�X�g�p

		if (g_wallSetCou > g_setLimit)
		{
			//�l���l�p
			if (g_score < 200)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 15 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					int ran = 0;
					while (1)
					{
						std::uniform_int_distribution<> dist(0, 3);
						ran = dist(rd);
						if (g_oldBarrierRan != ran)break;
					}

					if (ran == 0)
					{
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_RED);
					}
					if (ran == 1)
					{
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_GREEN);
					}
					if (ran == 2)
					{
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_BLUE);
					}
					if (ran == 3)
					{
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_YELLOW);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_oldBarrierRan = ran;
					g_barrierSetCou = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�����_��(�ړ���])
			else if (g_score < 400)//�X�R�A���`�̎�
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 20 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//�����_���ʒu��]
					int ram;
					std::uniform_real_distribution<> dist1(0, 360);
					float rot = dist1(rd);

					float posX = 0;
					float posY = 0;
					std::uniform_int_distribution<> dist2(0, 1);
					ram = dist2(rd);
					if (ram == 0)
					{
						std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALF, WALL_INIT_WIDTH_HALF);
						posX = dist2(rd);
						std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALF, WALL_INIT_HEIGHT_HALF);
						posY = dist3(rd);
					}
					else
					{
						std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALFHALF, WALL_INIT_WIDTH_HALFHALF);
						posX = dist2(rd);
						std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALFHALF, WALL_INIT_HEIGHT_HALFHALF);
						posY = dist3(rd);
					}

					std::uniform_real_distribution<> dist4((SCREEN_WIDTH + 700) / 4, (SCREEN_WIDTH + 700) / 2);
					float sizeX = dist4(rd);
					std::uniform_real_distribution<> dist5((SCREEN_HEIGHT + 700) / 4, (SCREEN_HEIGHT + 700) / 2);
					float sizeY = dist5(rd);

					std::uniform_int_distribution<> dist6(0, 1);
					ram = dist6(rd);
					float spX = 0.0f;
					if (ram == 1)
					{
						std::uniform_real_distribution<> dist6(-0.5f, 0.5f);
						spX = dist6(rd);
					}

					std::uniform_int_distribution<> dist7(0, 1);
					ram = dist7(rd);
					float spY = 0.0f;
					if (ram == 1)
					{
						std::uniform_real_distribution<> dist7(-0.5f, 0.5f);
						spY = dist7(rd);
					}

					std::uniform_int_distribution<> dist8(0, 1);
					ram = dist8(rd);
					float rotSp = 0.0f;
					if (ram == 1)
					{
						std::uniform_real_distribution<> dist8(-0.1f, 0.1f);
						rotSp = dist8(rd);
					}

					SetWall(WALL_BARRIER, posX, posY, sizeX, sizeY, rot, BARRIER_COLOR_RANDOM, spX, spY, rotSp);
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�O��
			else if (g_score < 600)//�X�R�A���`�̎�
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 20 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					std::uniform_int_distribution<> dist(0, 3);
					int ran = dist(rd);
					if (ran == 0)
					{
						//�c�O�����
						SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_RED);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_BLUE);
					}
					if (ran == 1)
					{
						//���O�����
						SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_YELLOW);
					}
					if (ran == 2)
					{
						//�c�O��
						SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF + 10, 0, 200, 5000, 0, BARRIER_COLOR_RED);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF - 10, 0, 200, 5000, 0, BARRIER_COLOR_BLUE);
					}
					if (ran == 3)
					{
						//���O��
						SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF + 10, 5000, 150, 0, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF - 10, 5000, 150, 0, BARRIER_COLOR_YELLOW);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�V���b�^�[
			else if (g_score < 800)//�X�R�A���`�̎�
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 20 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					std::uniform_int_distribution<> dist(0, 2);
					int ran = dist(rd);
					if (ran == 0)
					{
						//�V���b�^�[���E
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 750, 5000, 0, BARRIER_COLOR_RED, -0.3f, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 750, 5000, 0, BARRIER_COLOR_RED, 0.3f, 0.0f, 0.00f);
					}
					if (ran == 1)
					{
						//�V���b�^�[�㉺
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 750 * 1, 0, BARRIER_COLOR_BLUE, 0.0f, -0.15f, 0.00f);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 750 * 1, 0, BARRIER_COLOR_BLUE, 0.0f, 0.15f, 0.00f);
					}
					if (ran >= 2)
					{
						//�����_���ʒu��]
						int ram;
						std::uniform_real_distribution<> dist1(0, 360);
						float rot = dist1(rd);

						std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALFHALF - 2, WALL_INIT_WIDTH_HALFHALF + 2);
						float posX = dist2(rd);
						std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALFHALF - 2, WALL_INIT_HEIGHT_HALFHALF + 2);
						float posY = dist3(rd);

						std::uniform_real_distribution<> dist4((SCREEN_WIDTH + 700) / 4, (SCREEN_WIDTH + 700) / 1.5);
						float sizeX = dist4(rd);
						std::uniform_real_distribution<> dist5((SCREEN_HEIGHT + 700) / 4, (SCREEN_HEIGHT + 700) / 1.5);
						float sizeY = dist5(rd);

						std::uniform_int_distribution<> dist6(0, 1);
						ram = dist6(rd);
						float spX = 0.0f;
						if (ram == 1)
						{
							std::uniform_real_distribution<> dist6(-0.5f, 0.5f);
							spX = dist6(rd);
						}

						std::uniform_int_distribution<> dist7(0, 1);
						ram = dist7(rd);
						float spY = 0.0f;
						if (ram == 1)
						{
							std::uniform_real_distribution<> dist7(-0.5f, 0.5f);
							spY = dist7(rd);
						}

						std::uniform_int_distribution<> dist8(0, 1);
						ram = dist8(rd);
						float rotSp = 0.0f;
						if (ram == 1)
						{
							std::uniform_real_distribution<> dist8(-0.05f, 0.05f);
							rotSp = dist8(rd);
						}

						SetWall(WALL_BARRIER, posX, posY, sizeX, sizeY, rot, BARRIER_COLOR_RANDOM, spX, spY, rotSp);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = 0;
				}
				else
				{
					SetWall();
				}
			}//�X���C�h�h�A���E
			//�_�C�������h
			else if (g_score < 1000)//�X�R�A���`�̎�
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 18 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					int ran = 0;
					while (1)
					{
						std::uniform_int_distribution<> dist(0, 3);
						ran = dist(rd);
						if (g_oldBarrierRan != ran)break;
					}
					g_oldBarrierRan = ran;
					if (ran == 0)
					{
						//�^�񒆃_�C�������h
						SetWall(WALL_BARRIER, 0, 0, WALL_HEIGHT * 3, WALL_HEIGHT * 3, 45, BARRIER_COLOR_RED);
					}
					if (ran == 1)
					{
						//�΂ߎl���_�C�������h
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, -WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, -WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
					}
					if (ran == 2)
					{
						//�^�񒆋󂫃_�C�������h
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
					}
					if (ran == 3)
					{
						SetWall();
						g_barrierSetCouPlus = 10;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//��]
			else if (g_score < 1200)
			{
			g_barrierSetCou++;
			g_barrierCou++;
			int setCou = 20 + g_barrierSetCorrection;
			if (g_barrierCou > SCORE_FANFARE_SCORE * 0.5f)setCou = 10;
			if (g_barrierSetCou >= setCou)//�`��Ɉ���ǐݒu
			{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					std::uniform_int_distribution<> dist(0, 6);
					int ran = dist(rd);
					if (ran <= 2)
					{
						std::uniform_int_distribution<> dist(1, 360);
						int ran = dist(rd);
						//�����`�E��]
						SetWall(WALL_BARRIER, 0, 0, (WALL_HEIGHT) * 0.8, (WALL_HEIGHT) * 8, ran, BARRIER_COLOR_YELLOW, 0.0f, 0.0f, 0.01f);

					}
					if (ran >= 3 && ran != 6)
					{
						std::uniform_int_distribution<> dist(1, 360);
						int ran = dist(rd);
						//�����`����]
						SetWall(WALL_BARRIER, 0, 0, (WALL_HEIGHT) * 0.8, (WALL_HEIGHT) * 8, ran, BARRIER_COLOR_CYAN, 0.0f, 0.0f, -0.01f);

					}
					if (ran == 6)
					{
						SetWall();
						g_barrierSetCouPlus = 2;
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�����_��(�����`��])
			else if (g_score < 1400)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 15 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//�����_�������`��]
					int ram;
					std::uniform_real_distribution<> dist1(0, 360);
					float rot = dist1(rd);

					std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALFHALF - 1, WALL_INIT_WIDTH_HALFHALF + 1);
					float posX = dist2(rd);
					std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALFHALF - 1, WALL_INIT_HEIGHT_HALFHALF + 1);
					float posY = dist3(rd);

					std::uniform_real_distribution<> dist4((SCREEN_WIDTH + 700) / 4, (SCREEN_WIDTH + 700) / 1.5f);
					float sizeX = dist4(rd);
					std::uniform_real_distribution<> dist5((SCREEN_HEIGHT + 700) / 6, (SCREEN_HEIGHT + 700) / 4);
					float sizeY = dist5(rd);

					std::uniform_int_distribution<> dist6(0, 1);
					ram = dist6(rd);
					float spX = 0.0f;
					if (ram == 1)
					{
						std::uniform_real_distribution<> dist6(-0.8f, 0.8f);
						spX = dist6(rd);
					}

					std::uniform_int_distribution<> dist7(0, 1);
					ram = dist7(rd);
					float spY = 0.0f;
					if (ram == 1)
					{
						std::uniform_real_distribution<> dist7(-0.4f, 0.4f);
						spY = dist7(rd);
					}

					std::uniform_int_distribution<> dist8(0, 1);
					ram = dist8(rd);
					float rotSp = 0.0f;
					if (ram == 1)
					{
						std::uniform_real_distribution<> dist8(-0.05f, 0.05f);
						rotSp = dist8(rd);
					}

					SetWall(WALL_BARRIER, posX, posY, sizeX, sizeY, rot, BARRIER_COLOR_RANDOM, spX, spY, rotSp);
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�l���l�p(�i�X�����Ȃ�)
			else if (g_score < 1600)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 15)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					int ran = 0;
					while (1)
					{
						std::uniform_int_distribution<> dist(0, 3);
						ran = dist(rd);
						if (g_oldBarrierRan != ran)break;
					}

					if (ran == 0)
					{
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF+10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_RED);
					}
					if (ran == 1)
					{
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF-10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_GREEN);
					}
					if (ran == 2)
					{
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF-10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_BLUE);
					}
					if (ran == 3)
					{
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF+10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_YELLOW);
					}
					g_barrierSetCouPlus++;
					g_barrierSetCouPlus += abs(g_barrierSetCorrection);
					if (g_barrierSetCouPlus > 7)g_barrierSetCouPlus = 7;
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_oldBarrierRan = ran;
					g_barrierSetCou = g_barrierSetCouPlus;
				}
				else
				{
					SetWall();
				}
			}
			//�z�[���C���������C���{�[
			else if (g_score < 1800)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 2 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//�z�[���C���������C���{�[
					if (g_barrierCou > 0)
					{
						if (g_barrierCou % 6 == 0)
						{
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_RED);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_RED);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_RED);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_RED);
						}
						if (g_barrierCou % 6 == 1)
						{
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_MAGENTA);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_MAGENTA);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_MAGENTA);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_MAGENTA);
						}
						if (g_barrierCou % 6 == 2)
						{
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_BLUE);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_BLUE);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_BLUE);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_BLUE);
						}
						if (g_barrierCou % 6 == 3)
						{
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_CYAN);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_CYAN);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_CYAN);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_CYAN);
						}
						if (g_barrierCou % 6 == 4)
						{
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_GREEN);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_GREEN);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_GREEN);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_GREEN);
						}
						if (g_barrierCou % 6 == 5)
						{
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_YELLOW);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 1000 + g_barrierCou * 10, 0, BARRIER_COLOR_YELLOW);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_YELLOW);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 1000 + g_barrierCou * 10, 5000, 0, BARRIER_COLOR_YELLOW);
						}
					}
					else
					{
						SetWall();
					}

					if (g_barrierCou > 50)g_barrierCouTrigger = true;
					else if (g_barrierCou < -15)g_barrierCouTrigger = false;

					if (!g_barrierCouTrigger)g_barrierCou++;
					else if (g_barrierCouTrigger)g_barrierCou--;
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�V���b�^�[(�E�F�[�u)
			else if (g_score < 2000)
			{
				g_barrierSetCou++;
				g_barrierCou++;
				int setCou = 25 + g_barrierSetCorrection;
				if (g_barrierCou > SCORE_FANFARE_SCORE * 0.8f)setCou = 10;
				if (g_barrierSetCou >= setCou)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//�����_����ʊO
					float L = 0.0f;
					float R = 0.0f;

					std::uniform_int_distribution<> dist(0, 1);
					int ran = dist(rd);
					if (ran == 0)
					{
						std::uniform_int_distribution<> dist(0, 3);
						float ran = dist(rd);
						if (ran == 0)
						{
							std::uniform_real_distribution<> dist(0, 0.4f);
							float ran = dist(rd);
							L = ran;
							R = 0.4f - ran;
						}
						else
						{
							std::uniform_real_distribution<> dist(0, 0.35f);
							float ran = dist(rd);
							L = ran;
							R = 0.35f - ran;
						}

						std::uniform_real_distribution<> dist1(-10, 10);
						ran = dist1(rd);
						float P = ran;
						////�V���b�^�[�E�F�[�u���E
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 23, 0 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 20.5f, 6 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 18, 12 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 15.5f, 18 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 13, 24 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);

						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 20.5f, -6 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 18, -12 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 15.5f, -18 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 13, -24 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);

						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 23, 0 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 20.5f, 6 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 18, 12 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 15.5f, 18 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 13, 24 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);

						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 20.5f, -6 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 18, -12 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 15.5f, -18 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 13, -24 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
					}
					if (ran == 1)
					{
						float T = 0.0f;
						float U = 0.0f;

						std::uniform_int_distribution<> dist(0, 3);
						float ran = dist(rd);
						if (ran == 0)
						{
							std::uniform_real_distribution<> dist(0, 0.2f);
							float ran = dist(rd);
							T = ran;
							U = 0.2f - ran;
						}
						else
						{
							std::uniform_real_distribution<> dist(0, 0.15f);
							float ran = dist(rd);
							T = ran;
							U = 0.15f - ran;
						}

						std::uniform_real_distribution<> dist1(-12, 12);
						ran = dist1(rd);
						float P = ran;
						////�V���b�^�[�E�F�[�u�㉺
						SetWall(WALL_BARRIER, 0 + P, WALL_INIT_HEIGHT_HALF + 23, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 6 + P, WALL_INIT_HEIGHT_HALF + 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 12 + P, WALL_INIT_HEIGHT_HALF + 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 18 + P, WALL_INIT_HEIGHT_HALF + 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 24 + P, WALL_INIT_HEIGHT_HALF + 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 30 + P, WALL_INIT_HEIGHT_HALF + 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 36 + P, WALL_INIT_HEIGHT_HALF + 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 42 + P, WALL_INIT_HEIGHT_HALF + 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);

						SetWall(WALL_BARRIER, -6 + P, WALL_INIT_HEIGHT_HALF + 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -12 + P, WALL_INIT_HEIGHT_HALF + 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -18 + P, WALL_INIT_HEIGHT_HALF + 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -24 + P, WALL_INIT_HEIGHT_HALF + 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -30 + P, WALL_INIT_HEIGHT_HALF + 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -36 + P, WALL_INIT_HEIGHT_HALF + 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -42 + P, WALL_INIT_HEIGHT_HALF + 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);

						SetWall(WALL_BARRIER, 0 + P, -WALL_INIT_HEIGHT_HALF - 23, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 6 + P, -WALL_INIT_HEIGHT_HALF - 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 12 + P, -WALL_INIT_HEIGHT_HALF - 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 18 + P, -WALL_INIT_HEIGHT_HALF - 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 24 + P, -WALL_INIT_HEIGHT_HALF - 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 30 + P, -WALL_INIT_HEIGHT_HALF - 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 36 + P, -WALL_INIT_HEIGHT_HALF - 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 42 + P, -WALL_INIT_HEIGHT_HALF - 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);

						SetWall(WALL_BARRIER, -6 + P, -WALL_INIT_HEIGHT_HALF - 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -12 + P, -WALL_INIT_HEIGHT_HALF - 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -18 + P, -WALL_INIT_HEIGHT_HALF - 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -24 + P, -WALL_INIT_HEIGHT_HALF - 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -30 + P, -WALL_INIT_HEIGHT_HALF - 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -36 + P, -WALL_INIT_HEIGHT_HALF - 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -42 + P, -WALL_INIT_HEIGHT_HALF - 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
					}


					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�����_��(����)
			else if (g_score < 2200)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 2 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					{
						//�����_���ʒu��]
						int ram;
						std::uniform_real_distribution<> dist1(0, 360);
						float rot = dist1(rd);

						std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALFHALF - 6, WALL_INIT_WIDTH_HALFHALF + 6);
						float posX = dist2(rd);
						std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALFHALF - 4, WALL_INIT_HEIGHT_HALFHALF + 4);
						float posY = dist3(rd);

						std::uniform_real_distribution<> dist4((SCREEN_WIDTH + 700) / 6, (SCREEN_WIDTH + 700) / 4);
						float sizeX = dist4(rd);
						std::uniform_real_distribution<> dist5((SCREEN_HEIGHT + 700) / 6, (SCREEN_HEIGHT + 700) / 4);
						float sizeY = dist5(rd);

						std::uniform_int_distribution<> dist6(0, 1);
						ram = dist6(rd);
						float spX = 0.0f;
						if (ram == 1)
						{
							std::uniform_real_distribution<> dist6(-0.5f, 0.5f);
							spX = dist6(rd);
						}

						std::uniform_int_distribution<> dist7(0, 1);
						ram = dist7(rd);
						float spY = 0.0f;
						if (ram == 1)
						{
							std::uniform_real_distribution<> dist7(-0.5f, 0.5f);
							spY = dist7(rd);
						}

						std::uniform_int_distribution<> dist8(0, 1);
						ram = dist8(rd);
						float rotSp = 0.0f;
						if (ram == 1)
						{
							std::uniform_real_distribution<> dist8(-0.05f, 0.05f);
							rotSp = dist8(rd);
						}

						SetWall(WALL_BARRIER, posX, posY, sizeX, sizeY, rot, BARRIER_COLOR_RANDOM, spX, spY, rotSp);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�O��(��)
			else if (g_score < 2400)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 15 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//�O����
					int ran = 0;
					while (1)
					{
						std::uniform_int_distribution<> dist(0, 1);
						ran = dist(rd);
						if (g_oldBarrierRan != ran)break;
					}
					g_oldBarrierRan = ran;
					if (ran == 0)
					{
						std::uniform_int_distribution<> dist(0, 1);
						ran = dist(rd);
						if (ran == 0)
						{
							//�c�O�����
							SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_RED, 0.5f, 0.0f);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_BLUE, -0.5f, 0.0f);
						}
						if (ran == 1)
						{
							//�c�O��
							SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF + 10, 0, 200, 5000, 0, BARRIER_COLOR_RED, 0.8f, 0.0f);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF - 10, 0, 200, 5000, 0, BARRIER_COLOR_BLUE, -0.8f, 0.0f);
						}
					}
					else
					{
						std::uniform_int_distribution<> dist(0, 1);
						ran = dist(rd);
						if (ran == 0)
						{
							//���O�����
							SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_CYAN, 0.0f, 0.5f);
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_YELLOW, 0.0f, -0.5f);
						}

						if (ran == 1)
						{
							//���O��
							SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
							SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF + 10, 5000, 150, 0, BARRIER_COLOR_CYAN, 0.0f, 0.4f);
							SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF - 10, 5000, 150, 0, BARRIER_COLOR_YELLOW, 0.0f, -0.4f);
						}
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�����_��(��ʊO����ړ�)
			else if (g_score < 2600)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 5)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//�����_���ʒu��]
					for (int i = 0; i < 4; i++)
					{
						std::uniform_int_distribution<> dist1(0, 1);
						int ran = 0;
						ran = dist1(rd);
						float posX = 0.0f;
						float posY = 0.0f;

						if (!(g_barrierCou > SCORE_FANFARE_SCORE * 0.5f))
						{
							if (ran == 0)
							{
								std::uniform_int_distribution<> dist1(0, 1);
								ran = dist1(rd);
								if (ran == 0)
								{
									std::uniform_real_distribution<> dist2(WALL_INIT_WIDTH_HALF, WALL_INIT_WIDTH_HALF + 5);
									posX = dist2(rd);
								}
								else
								{
									std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALF - 5, -WALL_INIT_WIDTH_HALF);
									posX = dist2(rd);
								}
								std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALFHALF, WALL_INIT_HEIGHT_HALFHALF);
								posY = dist3(rd);
							}
							else
							{
								std::uniform_int_distribution<> dist1(0, 1);
								ran = dist1(rd);
								if (ran == 0)
								{
									std::uniform_real_distribution<> dist3(WALL_INIT_HEIGHT_HALF, WALL_INIT_HEIGHT_HALF + 5);
									posY = dist3(rd);
								}
								else
								{
									std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALF - 5, -WALL_INIT_HEIGHT_HALF);
									posY = dist3(rd);
								}
								std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALFHALF, WALL_INIT_WIDTH_HALFHALF);
								posX = dist2(rd);
							}
						}

						if (g_barrierCou > SCORE_FANFARE_SCORE * 0.5f)
						{
							std::uniform_int_distribution<> dist1(0, 1);
							ran = dist1(rd);
							if (ran == 0)
							{
								std::uniform_real_distribution<> dist2(WALL_INIT_WIDTH_HALF, WALL_INIT_WIDTH_HALF + 5);
								posX = dist2(rd);
							}
							else
							{
								std::uniform_real_distribution<> dist2(-WALL_INIT_WIDTH_HALF - 5, -WALL_INIT_WIDTH_HALF);
								posX = dist2(rd);
							}

							std::uniform_int_distribution<> dist2(0, 1);
							ran = dist2(rd);
							if (ran == 0)
							{
								std::uniform_real_distribution<> dist3(WALL_INIT_HEIGHT_HALF, WALL_INIT_HEIGHT_HALF + 5);
								posY = dist3(rd);
							}
							else
							{
								std::uniform_real_distribution<> dist3(-WALL_INIT_HEIGHT_HALF - 5, -WALL_INIT_HEIGHT_HALF);
								posY = dist3(rd);
							}
						}

						std::uniform_real_distribution<> dist4((SCREEN_WIDTH + 700) / 6, (SCREEN_WIDTH + 700) / 4);
						float sizeX = dist4(rd);
						std::uniform_real_distribution<> dist5((SCREEN_HEIGHT + 700) / 6, (SCREEN_HEIGHT + 700) / 4);
						float sizeY = dist5(rd);

						float spX = 0.0f;
						float spY = 0.0f;
						float rot = 0;

						if (!(g_barrierCou > SCORE_FANFARE_SCORE * 0.5f))
						{
							std::uniform_int_distribution<> dist1(0, 1);
							ran = dist1(rd);

							if (ran == 0)
							{
								if (posX > 0)
								{
									std::uniform_real_distribution<> dist6(-2.0f, 0.0f);
									spX = dist6(rd);
								}
								else
								{
									std::uniform_real_distribution<> dist6(0.0f, 2.0f);
									spX = dist6(rd);
								}
							}
							else
							{
								if (posY > 0)
								{
									std::uniform_real_distribution<> dist7(-2.0f, 0.0f);
									spY = dist7(rd);
								}
								else
								{
									std::uniform_real_distribution<> dist7(0.0f, 2.0f);
									spY = dist7(rd);
								}
							}
						}

						if (g_barrierCou > SCORE_FANFARE_SCORE * 0.5f)
						{
							if (posX > 0)
							{
								std::uniform_real_distribution<> dist6(-2.0f, 0.0f);
								spX = dist6(rd);
							}
							else
							{
								std::uniform_real_distribution<> dist6(0.0f, 2.0f);
								spX = dist6(rd);
							}

							if (posY > 0)
							{
								std::uniform_real_distribution<> dist7(-2.0f, 0.0f);
								spY = dist7(rd);
							}
							else
							{
								std::uniform_real_distribution<> dist7(0.0f, 2.0f);
								spY = dist7(rd);
							}


							std::uniform_real_distribution<> dist8(-2.0f, 2.0f);
							rot = dist8(rd);
						}

						SetWall(WALL_BARRIER, posX, posY, sizeX, sizeY, 0, BARRIER_COLOR_RANDOM, spX, spY, rot);
						g_barrierCou++;

					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
				}
				else
				{
					SetWall();
				}
			}
			//�{�~�ƕ���
			else if (g_score < 2800)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 10)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					int ran = 0;
					float ranf = 0;
					while (1)
					{
						std::uniform_int_distribution<> dist(0, 3);
						ran = dist(rd);
						if (g_oldBarrierRan != ran)break;
					}
					g_oldBarrierRan = ran;
					if (ran == 0)
					{
						//����]
						std::uniform_real_distribution<> dist(-0.01, 0.01);
						ranf = dist(rd);
						for (int i = 0; i < 5; i++)
						{
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_BLUE, 0.0f, 0.0f, ranf);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_GREEN, 0.0f, 0.0f, ranf);
						}
					}
					if (ran == 1)
					{
						//����]
						std::uniform_real_distribution<> dist(-0.01, 0.01);
						ranf = dist(rd);
						for (int i = 0; i < 5; i++)
						{
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_RED, 0.0f, 0.0f, ranf);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_YELLOW, 0.0f, 0.0f, ranf);
						}
					}
					if (ran == 2)
					{
						//�{
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
					}
					if (ran == 3)
					{
						//X
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, (WALL_HEIGHT) * 3, (WALL_HEIGHT) * 3, 45, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, (WALL_HEIGHT) * 3, (WALL_HEIGHT) * 3, 45, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 2.5f, (WALL_HEIGHT) * 2.5f, 45, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 2.5f, (WALL_HEIGHT) * 2.5f, 45, BARRIER_COLOR_CYAN);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
					g_barrierSetCouPlus = 0;
					//SetWall();
				}
				else
				{
					SetWall();
				}
			}
			//�l���l�p(��)
			else if (g_score < 3000)
			{
				g_barrierSetCou++;
				if (g_barrierSetCou >= 25 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					int ran = 0;
					float ranf = 0;
					std::uniform_int_distribution<> dist1(0, 2);
					ran = dist1(rd);
					//���Y���ړ�
					if (ran == 0)
					{
						std::uniform_real_distribution<> dist1(0.8f, 1.2f);
						ranf = dist1(rd);
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_RED, -0.7f * ranf, 0.0f);
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_GREEN, 0.0f, 0.4f * ranf);
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_BLUE, 0.7f * ranf, 0.0f);
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_YELLOW, 0.0f, -0.4f * ranf);
					}
					//�E�Y���ړ�
					if (ran == 1)
					{
						std::uniform_real_distribution<> dist1(0.8f, 1.2f);
						ranf = dist1(rd);
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_RED, 0.0f, 0.4f * ranf);
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_GREEN, 0.7f * ranf, 0.0f);
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_BLUE, 0.0f, -0.4f * ranf);
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_YELLOW, -0.7f * ranf, 0.0f);
					}
					//�N���X�ړ�
					if (ran == 2)
					{
						std::uniform_real_distribution<> dist1(0.3f, 1.2f);
						ranf = dist1(rd);
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_RED, -0.7f * ranf, 0.4f * ranf);
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_YELLOW, -0.7f * ranf, -0.4f * ranf);
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_GREEN, 0.7f * ranf, 0.4f * ranf);
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_BLUE, 0.7f * ranf, -0.4f * ranf);
					}
					g_barrierSetCouPlus++;
					if (g_barrierSetCouPlus > 12)g_barrierSetCouPlus = 12;
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = g_barrierSetCouPlus;
				}
				else
				{
					SetWall();
				}
			}
			//���~�b�N�X
			else
			{
			g_barrierSetCou++;
				if (g_barrierSetCou >= 20 + g_barrierSetCorrection)//�`��Ɉ���ǐݒu
				{
					/////////////////////////////////////�����ɏ�ǂ̏o�����L��////////////////////////////////////////////////////////
					//���~�b�N�X
					int ran = 0;
					float ranf = 0;
					float L = 0.0f;
					float R = 0.0f;
					float T = 0.0f;
					float U = 0.0f;

					std::uniform_int_distribution<> dist1(0, 28);
					ran = dist1(rd);

					if (ran == 0)
					{
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_RED);
					}
					else if (ran == 1)
					{
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_GREEN);
					}
					else if (ran == 2)
					{
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_BLUE);
					}
					else if (ran == 3)
					{
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 2.0f, WALL_HEIGHT * 2.0f, 0, BARRIER_COLOR_YELLOW);
					}
					else if (ran == 4)
					{
						//�c�O�����
						SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_RED);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_BLUE);
					}
					else if (ran == 5)
					{
						//���O�����
						SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_YELLOW);
					}
					else if (ran == 6)
					{
						//�c�O��
						SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF + 10, 0, 200, 5000, 0, BARRIER_COLOR_RED);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF - 10, 0, 200, 5000, 0, BARRIER_COLOR_BLUE);
					}
					else if (ran == 7)
					{
						//���O��
						SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF + 10, 5000, 150, 0, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF - 10, 5000, 150, 0, BARRIER_COLOR_YELLOW);
					}
					else if (ran == 8)
					{
						//�V���b�^�[���E
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, 750, 5000, 0, BARRIER_COLOR_RED, -0.3f, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, 750, 5000, 0, BARRIER_COLOR_RED, 0.3f, 0.0f, 0.00f);
					}
					else if (ran == 9)
					{
						//�V���b�^�[�㉺
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, 5000, 750 * 1, 0, BARRIER_COLOR_BLUE, 0.0f, -0.15f, 0.00f);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, 5000, 750 * 1, 0, BARRIER_COLOR_BLUE, 0.0f, 0.15f, 0.00f);
					}
					else if (ran == 10)
					{
						//�^�񒆃_�C�������h
						SetWall(WALL_BARRIER, 0, 0, WALL_HEIGHT * 3, WALL_HEIGHT * 3, 45, BARRIER_COLOR_RED);
					}
					else if (ran == 11)
					{
						//�΂ߎl���_�C�������h
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, -WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, -WALL_INIT_HEIGHT_HALFHALF, (WALL_HEIGHT) * 2.0f, (WALL_HEIGHT) * 2.0f, 45, BARRIER_COLOR_MAGENTA);
					}
					else if (ran == 12)
					{
						//�^�񒆋󂫃_�C�������h
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 6, (WALL_HEIGHT) * 6, 45, BARRIER_COLOR_BLUE);
					}
					else if (ran == 13)
					{
						std::uniform_int_distribution<> dist(1, 360);
						int ran = dist(rd);
						//�����`�E��]
						SetWall(WALL_BARRIER, 0, 0, (WALL_HEIGHT) * 0.8, (WALL_HEIGHT) * 8, ran, BARRIER_COLOR_YELLOW, 0.0f, 0.0f, 0.01f);

					}
					else if (ran == 14)
					{
						std::uniform_int_distribution<> dist(1, 360);
						int ran = dist(rd);
						//�����`����]
						SetWall(WALL_BARRIER, 0, 0, (WALL_HEIGHT) * 0.8, (WALL_HEIGHT) * 8, ran, BARRIER_COLOR_CYAN, 0.0f, 0.0f, -0.01f);

					}
					else if (ran == 15)
					{
						std::uniform_int_distribution<> dist(0, 3);
						float ran = dist(rd);
						if (ran == 0)
						{
							std::uniform_real_distribution<> dist(0, 0.4f);
							float ran = dist(rd);
							L = ran;
							R = 0.4f - ran;
						}
						else
						{
							std::uniform_real_distribution<> dist(0, 0.35f);
							float ran = dist(rd);
							L = ran;
							R = 0.35f - ran;
						}

						std::uniform_real_distribution<> dist1(-10, 10);
						ran = dist1(rd);
						float P = ran;
						////�V���b�^�[�E�F�[�u���E
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 23, 0 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 20.5f, 6 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 18, 12 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 15.5f, 18 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 13, 24 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);

						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 20.5f, -6 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 18, -12 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 15.5f, -18 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF + 13, -24 + P, 3000, 300, 0, BARRIER_COLOR_RED, -R, 0.0f, 0.00f);

						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 23, 0 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 20.5f, 6 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 18, 12 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 15.5f, 18 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 13, 24 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);

						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 20.5f, -6 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 18, -12 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 15.5f, -18 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF - 13, -24 + P, 3000, 300, 0, BARRIER_COLOR_RED, L, 0.0f, 0.00f);
					}
					else if (ran == 16)
					{
						float T = 0.0f;
						float U = 0.0f;

						std::uniform_int_distribution<> dist(0, 3);
						float ran = dist(rd);
						if (ran == 0)
						{
							std::uniform_real_distribution<> dist(0, 0.2f);
							float ran = dist(rd);
							T = ran;
							U = 0.2f - ran;
						}
						else
						{
							std::uniform_real_distribution<> dist(0, 0.15f);
							float ran = dist(rd);
							T = ran;
							U = 0.15f - ran;
						}

						std::uniform_real_distribution<> dist1(-12, 12);
						ran = dist1(rd);
						float P = ran;
						////�V���b�^�[�E�F�[�u�㉺
						SetWall(WALL_BARRIER, 0 + P, WALL_INIT_HEIGHT_HALF + 23, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 6 + P, WALL_INIT_HEIGHT_HALF + 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 12 + P, WALL_INIT_HEIGHT_HALF + 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 18 + P, WALL_INIT_HEIGHT_HALF + 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 24 + P, WALL_INIT_HEIGHT_HALF + 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 30 + P, WALL_INIT_HEIGHT_HALF + 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 36 + P, WALL_INIT_HEIGHT_HALF + 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, 42 + P, WALL_INIT_HEIGHT_HALF + 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);

						SetWall(WALL_BARRIER, -6 + P, WALL_INIT_HEIGHT_HALF + 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -12 + P, WALL_INIT_HEIGHT_HALF + 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -18 + P, WALL_INIT_HEIGHT_HALF + 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -24 + P, WALL_INIT_HEIGHT_HALF + 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -30 + P, WALL_INIT_HEIGHT_HALF + 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -36 + P, WALL_INIT_HEIGHT_HALF + 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);
						SetWall(WALL_BARRIER, -42 + P, WALL_INIT_HEIGHT_HALF + 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, -T, 0.00f);

						SetWall(WALL_BARRIER, 0 + P, -WALL_INIT_HEIGHT_HALF - 23, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 6 + P, -WALL_INIT_HEIGHT_HALF - 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 12 + P, -WALL_INIT_HEIGHT_HALF - 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 18 + P, -WALL_INIT_HEIGHT_HALF - 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 24 + P, -WALL_INIT_HEIGHT_HALF - 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 30 + P, -WALL_INIT_HEIGHT_HALF - 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 36 + P, -WALL_INIT_HEIGHT_HALF - 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, 42 + P, -WALL_INIT_HEIGHT_HALF - 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);

						SetWall(WALL_BARRIER, -6 + P, -WALL_INIT_HEIGHT_HALF - 22, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -12 + P, -WALL_INIT_HEIGHT_HALF - 21, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -18 + P, -WALL_INIT_HEIGHT_HALF - 20, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -24 + P, -WALL_INIT_HEIGHT_HALF - 19, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -30 + P, -WALL_INIT_HEIGHT_HALF - 18, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -36 + P, -WALL_INIT_HEIGHT_HALF - 17, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
						SetWall(WALL_BARRIER, -42 + P, -WALL_INIT_HEIGHT_HALF - 16, 300, 3000, 0, BARRIER_COLOR_BLUE, 0.0f, U, 0.00f);
					}
					else if (ran == 17)
					{
						//�c�O�����
						SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_RED, 0.5f, 0.0f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF, 0, 200, 5000, 0, BARRIER_COLOR_BLUE, -0.5f, 0.0f);
					}
					else if (ran == 18)
					{
						//�c�O��
						SetWall(WALL_BARRIER, 0, 0, 200, 5000, 0, BARRIER_COLOR_GREEN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF + 10, 0, 200, 5000, 0, BARRIER_COLOR_RED, 0.8f, 0.0f);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF - 10, 0, 200, 5000, 0, BARRIER_COLOR_BLUE, -0.8f, 0.0f);
					}
					else if (ran == 19)
					{
						//���O�����
						SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_CYAN, 0.0f, 0.5f);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALFHALF, 5000, 150, 0, BARRIER_COLOR_YELLOW, 0.0f, -0.5f);
					}
					else if (ran == 20)
					{
						//���O��
						SetWall(WALL_BARRIER, 0, 0, 5000, 150, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF + 10, 5000, 150, 0, BARRIER_COLOR_CYAN, 0.0f, 0.4f);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF - 10, 5000, 150, 0, BARRIER_COLOR_YELLOW, 0.0f, -0.4f);
					}
					else if (ran == 21)
					{
						//����]
						std::uniform_real_distribution<> dist(-0.01, 0.01);
						ranf = dist(rd);
						for (int i = 0; i < 5; i++)
						{
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_BLUE, 0.0f, 0.0f, ranf);
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_GREEN, 0.0f, 0.0f, ranf);
						}
					}
					else if (ran == 22)
					{
						//����]
						std::uniform_real_distribution<> dist(-0.01, 0.01);
						ranf = dist(rd);
						for (int i = 0; i < 5; i++)
						{
							SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_RED, 0.0f, 0.0f, ranf);
							SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 7.0f, 80.0f, 0 + i * 72, BARRIER_COLOR_YELLOW, 0.0f, 0.0f, ranf);
						}
					}
					else if (ran == 23)
					{
						//�{
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 5.5f, (WALL_HEIGHT) * 3.5f, 0, BARRIER_COLOR_MAGENTA);
					}
					else if (ran == 24)
					{
						//X
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALF, 0, (WALL_HEIGHT) * 3, (WALL_HEIGHT) * 3, 45, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALF, 0, (WALL_HEIGHT) * 3, (WALL_HEIGHT) * 3, 45, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 2.5f, (WALL_HEIGHT) * 2.5f, 45, BARRIER_COLOR_CYAN);
						SetWall(WALL_BARRIER, 0, -WALL_INIT_HEIGHT_HALF, (WALL_HEIGHT) * 2.5f, (WALL_HEIGHT) * 2.5f, 45, BARRIER_COLOR_CYAN);
					}
					else if (ran == 25)
					{
						std::uniform_real_distribution<> dist1(0.8f, 1.2f);
						ranf = dist1(rd);
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_RED, -0.7f * ranf, 0.0f);
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_GREEN, 0.0f, 0.4f * ranf);
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_BLUE, 0.7f * ranf, 0.0f);
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_YELLOW, 0.0f, -0.4f * ranf);
					}
					else if (ran == 26)
					{
						std::uniform_real_distribution<> dist1(0.8f, 1.2f);
						ranf = dist1(rd);
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_RED, 0.0f, 0.4f * ranf);
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_GREEN, 0.7f * ranf, 0.0f);
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_BLUE, 0.0f, -0.4f * ranf);
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.5f, WALL_HEIGHT * 1.5f, 0, BARRIER_COLOR_YELLOW, -0.7f * ranf, 0.0f);
					}
					else if (ran == 27)
					{
						std::uniform_real_distribution<> dist1(0.3f, 1.2f);
						ranf = dist1(rd);
						//�E��l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_RED, -0.7f * ranf, 0.4f * ranf);
						//�����l�p
						SetWall(WALL_BARRIER, WALL_INIT_WIDTH_HALFHALF + 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_YELLOW, -0.7f * ranf, -0.4f * ranf);
						//����l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, -WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_GREEN, 0.7f * ranf, 0.4f * ranf);
						//�E���l�p
						SetWall(WALL_BARRIER, -WALL_INIT_WIDTH_HALFHALF - 10, WALL_INIT_HEIGHT_HALFHALF, WALL_WIDTH * 1.1f, WALL_HEIGHT * 1.1f, 0, BARRIER_COLOR_BLUE, 0.7f * ranf, -0.4f * ranf);
					}
					else if (ran == 28)
					{
						SetWall();
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					g_barrierSetCou = 0;
				}
				else
				{
					SetWall();
				}
			}

			g_wallSetCou = 0;
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawWall()
{
	p_Player = GetPlayer();
	bool playerDraw = false;
	bool fogDraw1 = false;
	bool fogDraw2 = false;
	bool fogDraw3 = false;
	for (int i = 0; i < WALL_MAX; i++)
	{
		if (g_Wall[i].use)
		{
			if (g_Wall[i].mode == WALL_BARRIER)
			{
				DrawBarrier(g_Wall[i].g_num);
			}

			DrawSpriteColor(g_TexNo,
				g_Wall[i].pos.x,
				g_Wall[i].pos.y,
				g_Wall[i].size.x, g_Wall[i].size.y,			//���A����
				WALL_WIDTH * 0.5f, WALL_HEIGHT * 0.5f,		//���SUV���W
				1.0f, 1.0f,									//�e�N�X�`�����A����
				g_Wall[i].color.r, g_Wall[i].color.g, g_Wall[i].color.b, g_Wall[i].color.a
			);

			if (p_Player[0].disRate > g_Wall[i].disRate -0.05f + PLAYER_HET_RANGE)
			{
				DrawPlayer();
				playerDraw = true;
			}

			if (g_Wall[i].disRate > 0.05f && !fogDraw1)
			{
				DrawFog();
				fogDraw1 = true;
			}
			if (g_Wall[i].disRate > 0.1f && !fogDraw2)
			{
				DrawFog();
				fogDraw2 = true;
			}
			if (g_Wall[i].disRate > 0.15f && !fogDraw3)
			{
				DrawFog();
				fogDraw3 = true;
			}

		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitWall(void)
{

}

//---------------------------------------------------
// �ǎ擾����
//---------------------------------------------------
WALL* GetWall()
{
	return &g_Wall[0];
}

//---------------------------------------------------
// �ǂ��Z�b�g(��ǂ�L��, ��Ǎ��W(�ǂ̒��S�����_�A�ǂ̏����T�C�Y����ɂ����傫��), ��ǃT�C�Y(�Ŏ�O�T�C�Y), ��Ǌp�x(�x���@), ��]����, ��]���x)
//---------------------------------------------------
void SetWall(int mode, float posX, float posY, float sizeX, float sizeY, float rot, int color, float speedX, float speedY, float rotSpeed)
{
	//���W�A���ɕϊ�
	float radian;
	radian = rot * (3.14159f / 180);

	for (int i = 0; i < WALL_MAX; i++)
	{
		if (g_Wall[i].use == false)//���g�p�̔z�������
		{
			g_Wall[i].size = D3DXVECTOR2(WALL_INIT_WIDTH, WALL_INIT_HEIGHT);
			g_Wall[i].oldSize = g_Wall[i].size;
			g_Wall[i].pos = D3DXVECTOR2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
			g_Wall[i].mode = mode;
			g_Wall[i].dis = 0.0f;
			g_Wall[i].use = true;//�g�p���ɂ���
			g_Wall[i].initSize = D3DXVECTOR2(g_Wall[i].size.x, g_Wall[i].size.y);
			g_Wall[i].initPos = D3DXVECTOR2(g_Wall[i].pos.x, g_Wall[i].pos.y);
			g_Wall[i].disRate = 0;
			g_Wall[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

			if (g_num > WALL_MAX)
			{
				g_num = 0;
			}
			g_num++;

			g_Wall[i].g_num = g_num;

			if (mode == 0)
			{
				//��ǂ̐ݒ�
				SetBarrier(g_num, posX, posY, sizeX, sizeY, radian, color, speedX, speedY, rotSpeed);
			}

			break;//�I��
		}
	}
	qsort(g_Wall, WALL_MAX, sizeof(WALL), cmpWallSize);//�N�C�b�N�\�[�g�Ŏ�O�̕ǂ��ɕ\������
}

//---------------------------------------------------
// �ǂ��~�߂�
//---------------------------------------------------
void StopWall()
{
	for (int i = 0; i < WALL_MAX; i++)
	{
		if (g_Wall[i].use == true)
		{
			g_move = false;
			g_Wall[i].zoomSpeed = 0;
			g_Wall[i].oldSize = g_Wall[i].size;
		}
	}
}