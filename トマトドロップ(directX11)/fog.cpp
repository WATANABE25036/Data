//===================================================
//��(fog.cpp)
//Auhor:�n� �C	Date:2023.8.7
//===================================================
#include "fog.h"
#include "texture.h"
#include "sprite.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
//static��t����ƃt�@�C���̒��̃O���[�o���ϐ��ɂȂ�
static int g_TexNo;
static float g_U;
static float g_V;
static FOG	g_Fog[FOG_MAX];

//---------------------------------------------------
//������
//---------------------------------------------------
void InitFog(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/barrier.png");

	//�O���[�o���ϐ�������
	g_U = FOG_WIDTH * 0.5f;
	g_V = FOG_HEIGHT * 0.5f;

	for (int i = 0; i < FOG_MAX; i++)
	{
		g_Fog[i].color = D3DXCOLOR(0, 0, 0, 0);
		g_Fog[i].pos = D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF);
		g_Fog[i].size = D3DXVECTOR2(FOG_WIDTH, FOG_HEIGHT);
		g_Fog[i].use = false;
	}

	for (int i = 0; i < 3; i++)
	{
		SetFog();
	}
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateFog(void)
{

}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawFog()
{
	for (int i = 0; i < FOG_MAX; i++)
	{
		if (g_Fog[i].use)
		{
			DrawSpriteColor(g_TexNo,
				g_Fog[i].pos.x,
				g_Fog[i].pos.y,
				g_Fog[i].size.x, g_Fog[i].size.y,	//���A����
				g_U, g_V,	//���SUV���W
				1, 1,	//�e�N�X�`�����A����
				g_Fog[i].color.r, g_Fog[i].color.g, g_Fog[i].color.b, g_Fog[i].color.a
			);
			break;
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitFog(void)
{

}

//---------------------------------------------------
// �����Z�b�g
//---------------------------------------------------
void SetFog()
{
	for (int i = 0; i < FOG_MAX; i++)
	{
		if (!g_Fog[i].use)
		{
			g_Fog[i].color = D3DXCOLOR(0, 0, 0.2f, 0.2f);
			g_Fog[i].pos = D3DXVECTOR2(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF);
			g_Fog[i].size = D3DXVECTOR2(FOG_WIDTH, FOG_HEIGHT);
			g_Fog[i].use = true;
			break;
		}
	}
}
