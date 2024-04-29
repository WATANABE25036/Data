//===================================================
//�}�b�v�͈͑I��(range_select.cpp)
//Auhor:�n� �C	Date:2024.1.20
//===================================================
#include "range_select.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "main.h"
#include "tile.h"
#include "tile.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static int g_SE_landing;
static int g_SE_range_selectHit;
static int g_SE_range_selectDown;
static int g_SE_coinGet;
static int g_SE_hpUp;
static int g_SE_powerUp;
static int g_SE_boxOpen;
static float g_U;
static float g_V;
static float g_UW;
static float g_VH;
static int g_AnimePattern;
static int g_AnimeBasePattern;//�A�j���[�V�����ԍ��̕������Ƃ̃x�[�X�l
static int g_AnimeSkipFrame;
static float g_AnimeSkipFrameFloat;
static RANGE_SELECT g_RangeSelect[RANGE_SELECT_MAX];
static TILE_DATA* p_Tile;
static bool g_Reverse;
static D3DXVECTOR2 g_LastGroundPos;
static int g_DropRevivalTime;
static int g_DropRevivalCou;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitRangeSelect(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Filter.png");

	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		g_RangeSelect[i].use = false;
		g_RangeSelect[i].pos.x = SCREEN_WIDTH / 2;
		g_RangeSelect[i].pos.y = SCREEN_HEIGHT / 4;
		g_RangeSelect[i].spd.x = RANGE_SELECT_SPEED;
		g_RangeSelect[i].spd.y = RANGE_SELECT_SPEED;
		//�x�N�g���̐��K��
		g_RangeSelect[i].spd = D3DXVECTOR2(RANGE_SELECT_SPEED, RANGE_SELECT_SPEED);//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����
		g_RangeSelect[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		g_RangeSelect[i].size = D3DXVECTOR2(RANGE_SELECT_WIDTH, RANGE_SELECT_HEIGHT);
		g_RangeSelect[i].dir = 0;
	}

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / 1.0f;
	g_VH = 1.0f / 1.0f;
	g_AnimePattern = 0;
	g_AnimeSkipFrame = 0;
	g_AnimeSkipFrameFloat = 0;
	g_AnimeBasePattern = 0;
	g_Reverse = false;
	g_LastGroundPos = D3DXVECTOR2(0, 0);
	g_DropRevivalTime = 60;
	g_DropRevivalCou = 0;
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateRangeSelect(void)
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (GetKeyboardPress(DIK_P))
		{
			g_RangeSelect[i].pos.x = SCREEN_WIDTH / 2;
			g_RangeSelect[i].pos.y = SCREEN_HEIGHT / 4;


		}

		if (g_RangeSelect[i].use)
		{
			//�����L�΂�
			g_RangeSelect[i].pos.x += g_RangeSelect[i].spd.x * g_RangeSelect[i].dir * 0.5f;
			g_RangeSelect[i].size.x += g_RangeSelect[i].spd.x * abs(g_RangeSelect[i].dir);

		}
		//�{�^���𗣂����Ƃ�
		else
		{
			//�{�^���𗣂����Ƃ��͈͓�������
			if (g_RangeSelect[i].size.x > MAPCHIP_SIZE * 1.5f)
			{
				CatTile(g_RangeSelect[i].pos.x - g_RangeSelect[i].size.x * 0.5f, g_RangeSelect[i].pos.x + g_RangeSelect[i].size.x * 0.5f);
				g_RangeSelect[i].size.x = 0.0f;
			}
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawRangeSelect(void)
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (g_RangeSelect[i].use)
		{
			//����
			DrawSpriteColorRotateCamera(g_TexNo,
				(int)g_RangeSelect[i].pos.x,
				(int)g_RangeSelect[i].pos.y,
				g_RangeSelect[i].size.x, g_RangeSelect[i].size.y,	//���A����
				g_U, g_V,		//���SUV���W
				g_UW, g_VH,		//�e�N�X�`�����A����
				g_RangeSelect[i].color.r, g_RangeSelect[i].color.g, g_RangeSelect[i].color.b, g_RangeSelect[i].color.a,
				0.0f
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitRangeSelect(void)
{

}

//---------------------------------------------------
// �擾����
//---------------------------------------------------
RANGE_SELECT* GetRangeSelect()
{
	return &g_RangeSelect[0];
}

//---------------------------------------------------
// �z�u(���� : dir -1��1���Ō����𔻒f)
//---------------------------------------------------
void SetRangeSelect(D3DXVECTOR2 pos, int dir)
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (!g_RangeSelect[i].use)
		{
			g_RangeSelect[i].pos.x = pos.x;
			g_RangeSelect[i].pos.y = pos.y;
			g_RangeSelect[i].spd.x = RANGE_SELECT_SPEED;
			g_RangeSelect[i].spd.y = RANGE_SELECT_SPEED;
			g_RangeSelect[i].spd = D3DXVECTOR2(RANGE_SELECT_SPEED, RANGE_SELECT_SPEED);
			g_RangeSelect[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			g_RangeSelect[i].size = D3DXVECTOR2(1.0f, SCREEN_HEIGHT);
			g_RangeSelect[i].dir = dir;

			g_RangeSelect[i].use = true;
			break;
		}
	}
}

//---------------------------------------------------
// �폜(�͈͌���)
//---------------------------------------------------
void DecisionRangeSelect()
{
	for (int i = 0; i < RANGE_SELECT_MAX; i++)
	{
		if (g_RangeSelect[i].use)
		{
			g_RangeSelect[i].use = false;
		}
	}
}