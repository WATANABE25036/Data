//===================================================
//�X�R�A(score.cpp)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#include <fstream>
#include <iostream>
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "sound.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_ScoreList[SCORE_MAX];
static int g_Score;
unsigned int g_ScoreTexture;
static float g_scale;
static float g_easingFactor;
static bool g_fanfare;
static int g_SE_up;
static bool g_upSeCheck;
static D3DXCOLOR g_color;

//�N�C�b�N�\�[�g�Ŏg�p
int cmpScore(const void* n1, const void* n2)
{
	int value1 = *((const int*)n1);
	int value2 = *((const int*)n2);

	if (value1 < value2)
	{
		return 1;
	}
	else if (value1 > value2)
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
void InitScore()
{
	for (int i = 0; i < SCORE_MAX; i++)
	{
		g_ScoreList[i] = 0;
	}

	//�Q�[����ʂɈڍs���鎞����������
	switch (GetScene())
	{
	case SCENE_GAME:
		g_Score = SCORE_INIT_SCORE;
		break;

	case SCENE_RESULT:
		LoadScore();
		SaveScore();
		break;

	default:
		break;
	}

	//�e�N�X�`���쐬
	g_ScoreTexture = LoadTexture((char*)"data/TEXTURE/number.png");

	//���ʉ��쐬
	char se1[] =
	{
		"data\\SE\\up.wav"
	};
	g_SE_up = LoadSound(&se1[0]);

	g_scale = 0.0f;
	g_easingFactor = 1.0f;
	g_fanfare = false;
	g_upSeCheck = false;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateScore()
{
	//���̃X�R�A�ɂȂ邽�тɎ��s
	if (g_Score % SCORE_FANFARE_SCORE == 0 && !g_fanfare && g_Score != 0)
	{
		g_upSeCheck = true;

		g_fanfare = true;
		g_scale = 1.0f; // �X�P�[�������Z�b�g
	}

	//���̃X�R�A�ɂȂ邽�тɈ�񂾂�
	if (g_upSeCheck)
	{
		PlaySound(g_SE_up, 0);
		g_upSeCheck = false;
		g_color.g -= 0.06f;
		g_color.b -= 0.06f;
	}

	if (g_fanfare)
	{
		g_scale += SCORE_SCALE_UP_SPEED;

		if (g_scale > SCORE_SCALE_MAX)
		{
			g_scale = SCORE_SCALE_MAX;
			g_fanfare = false; // �t�@���t�@�[���I��

			// �����Ńt�@���t�@�[�����Đ����鏈����ǉ�
		}

		g_easingFactor = EaseInOut(g_scale); // �C�[�W���O�֐���K�p
	}
	else
	{
		if (g_scale > 1.0f)
		{
			g_scale -= SCORE_SCALE_DOWN_SPEED;
			g_easingFactor = EaseInOut(g_scale); // �C�[�W���O�֐���K�p
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawScore()
{
	switch (GetScene())
	{
	case SCENE_GAME:
		SetDrawScore(g_Score, SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 80, 88, g_easingFactor);
		break;

	case SCENE_RESULT:
		SetDrawScore(g_Score, SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.1f, 80, 88 * 1.5, 1.0f);
		for (int i = 0; i < 9; i++)
		{
			SetDrawRank(i + 1, SCREEN_WIDTH_HALF - 80 * 2.5f, SCREEN_HEIGHT * 0.2f + (((80 * 0.5f) + 20) * i), 77, 88 * 0.5f);
			SetDrawScore(g_ScoreList[i], SCREEN_WIDTH_HALF, SCREEN_HEIGHT * 0.2f + (((80 * 0.5f) + 20) * i) , 80 * 0.5f, 88 * 0.5f, 1.0f);
		}
		break;

	default:
		break;
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitScore()
{

}

//---------------------------------------------------
//�X�R�A�𑝂₷
//---------------------------------------------------
void AddScore(int Score)
{
	g_Score += Score;
}

//---------------------------------------------------
//�v���C���[�����t�@�C���֏�������
//---------------------------------------------------
bool SaveScore()
{
	//�t�@�C���I�[�v��
	std::ofstream ofs("score.txt");

	//�t�@�C�����I�[�v���ł��Ȃ�������
	if (ofs.fail())
	{
		return false;
	}
	
	//�\�[�g���ď�������
	//���X�g�̈�ԏ������X�R�A���傫����Ώ�������
	SortScore();
	if (g_ScoreList[SCORE_MAX - 1] < g_Score)
	{
		g_ScoreList[SCORE_MAX - 1] = g_Score;
		SortScore();
	}

	//���X�g�̏�������
	for (int i = 0; i < SCORE_MAX; i++)
	{
		ofs << g_ScoreList[i] << std::endl;
	}

	//�t�@�C���̃N���[�Y
	ofs.close();

	return false;
}

//---------------------------------------------------
//�v���C���[�����t�@�C������ǂݍ���
//---------------------------------------------------
bool LoadScore()
{
	//�t�@�C���I�[�v��
	std::ifstream ifs("score.txt");

	//�t�@�C�����I�[�v���ł��Ȃ�������
	if (ifs.fail())
	{
		return false;
	}

	//�v���C���[�f�[�^�̏�������
	for (int i = 0; i < SCORE_MAX; i++)
	{
		//�v���C���[�f�[�^��ǂݍ���
		ifs >> g_ScoreList[i];
	}

	SortScore();

	//�t�@�C���̃N���[�Y
	ifs.close();

	return false;
}

//---------------------------------------------------
//�N�C�b�N�\�[�g
//---------------------------------------------------
void SortScore()
{
	qsort(g_ScoreList, SCORE_MAX, sizeof(int), cmpScore);//�N�C�b�N�\�[�g
}

//---------------------------------------------------
//�X�R�A�\��
//---------------------------------------------------
void SetDrawScore(int score, float posX, float posY, float sizeX, float sizeY, float scale)
{
	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;
		tx = (n % 10) * 0.1f;
		ty = (n / 10) * 1.0f;

		score /= 10;

		float sx, sy;
		sx = (posX - (sizeX * SCORE_FIGURE * 0.5f * scale)) + ((sizeX * 0.5f * scale) * (SCORE_FIGURE * 2 - (i + i + 1)));
		sy = posY;

		switch (GetScene())
		{
		case SCENE_GAME:
			DrawSpriteColorRotateScale(g_ScoreTexture, sx, sy, sizeX, sizeY,
				0.0f, 0.0f,
				tx, ty, 0.1f, 1.0f,
				g_color.r, g_color.g, g_color.b, g_color.a,
				0.0f,
				scale, scale);
			break;

		case SCENE_RESULT:
			DrawSpriteColorRotateScale(g_ScoreTexture, sx, sy, sizeX, sizeY,
				0.0f, 0.0f,
				tx, ty, 0.1f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				0.0f,
				scale, scale);
			break;

		default:
			break;
		}

	}
}

//---------------------------------------------------
//���ʕ\��
//---------------------------------------------------
void SetDrawRank(int score, float posX, float posY, float sizeX, float sizeY)
{
	for (int i = 0; i < RANK_FIGURE; i++)
	{
		int n;
		float tx, ty;

		n = score % 10;
		tx = (n % 10) * 0.1f;
		ty = (n / 10) * 1.0f;

		score /= 10;

		float sx, sy;
		sx = (posX - (sizeX * RANK_FIGURE * 0.5f)) + ((sizeX * 0.5f) * (RANK_FIGURE * 2 - (i + i + 1)));
		sy = posY;

		DrawSprite(g_ScoreTexture, sx, sy, sizeX, sizeY,
			tx, ty, 0.1f, 1.0f);
	}
}

//---------------------------------------------------
//�X�R�A���擾
//---------------------------------------------------
int GetScore()
{
	return g_Score;
}

//---------------------------------------------------
//�J�[�u��`���l���擾
//---------------------------------------------------
float EaseInOut(float t)
{
	// �x�W�F�Ȑ��⑼�̃C�[�W���O�֐����g�p���āA���� t �̕�Ԓl���v�Z����
	return t * t + (1 - t) * (1 - t);
}

//---------------------------------------------------
//�X�R�A���`�ɂ���
//---------------------------------------------------
void SetScore(int Score)
{
	g_Score = Score;
}