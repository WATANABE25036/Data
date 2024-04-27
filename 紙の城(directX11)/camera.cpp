//===================================================
//�J����(camera.cpp)
//Auhor:�n� �C	Date:2023.8.27
//===================================================
#include <random>
#include "camera.h"
#include "texture.h"
#include "sprite.h"
#include "input.h"
#include "sound.h"
#include "collision.h"
#include "main.h"
#include "tile.h"
#include "GameEntity/Player/player.h"
#include "GameEntity/EntityManager.h"

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
static CAMERA g_Camera[CAMERA_MAX];
static TILE_DATA* p_Tile;
static bool g_Reverse;
static Player* p_Player;
static float g_ShakeRemain;
static float g_ShakeMagnitude;
static float g_ShakeLength;
static D3DXVECTOR2 g_MapSize;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitCamera(void)
{
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Camera.png");
	p_Player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		g_Camera[i].use = true;
		g_Camera[i].pos.x = SCREEN_WIDTH / 2;
		g_Camera[i].pos.y = SCREEN_HEIGHT / 3;
		g_Camera[i].oldPos = D3DXVECTOR2(0, 0);
		g_Camera[i].spd.x = 0.0f;
		g_Camera[i].spd.y = 0.0f;
		g_Camera[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Camera[i].size = D3DXVECTOR2(CAMERA_WIDTH, CAMERA_HEIGHT);
		g_Camera[i].use = true;
		g_Camera[i].cameraMove = D3DXVECTOR2(0, 0);
		g_Camera[i].notLoopPos = D3DXVECTOR2(0, 0);
		g_Camera[i].oldNotLoopPos = D3DXVECTOR2(0, 0);
		g_Camera[i].trackingDelay = D3DXVECTOR2(10, 10);
		g_Camera[i].cameraTotalMove = D3DXVECTOR2(0, 0);
		g_Camera[i].loopTrigger = 0;
	}

	//�O���[�o���ϐ�������
	g_U = 0.0f;
	g_V = 0.0f;
	g_UW = 1.0f / CAMERA_WIDTH_PATTERN;
	g_VH = 1.0f / CAMERA_HEIGHT_PATTERN;
	g_ShakeRemain = 0;
	g_ShakeMagnitude = 0;
	g_ShakeLength = 0;
	g_MapSize = GetMapSize();
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateCamera(void)
{
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		p_Player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");

		g_Camera[i].oldPos = g_Camera[i].pos;
		g_Camera[i].oldNotLoopPos = g_Camera[i].notLoopPos;

		if (g_Camera[i].use && p_Player->GetUse())
		{
			if (GetKeyboardPress(DIK_RIGHT))g_Camera[i].pos.x += 3.0f;
			if (GetKeyboardPress(DIK_LEFT))g_Camera[i].pos.x -= 3.0f;
			if (GetKeyboardPress(DIK_UP))g_Camera[i].pos.y -= 3.0f;
			if (GetKeyboardPress(DIK_DOWN))g_Camera[i].pos.y += 3.0f;

			//�J������h�炷
			if (g_ShakeRemain != 0)
			{
				g_Camera[i].pos.x += GetRandomFloat(-g_ShakeRemain, g_ShakeRemain);
				g_Camera[i].pos.y += GetRandomFloat(-g_ShakeRemain, g_ShakeRemain);

				g_ShakeRemain = max(0, g_ShakeRemain - ((1 / g_ShakeLength) * g_ShakeMagnitude));//max: 2�̒l����傫���ق���Ԃ�
			}

			//�v���C���[�����Α��ɍs�����烏�[�v����
			if (p_Player[i].loopTrigger == 1)g_Camera[i].pos.x -= STAGE_SIZE;
			else if (p_Player[i].loopTrigger == -1)g_Camera[i].pos.x += STAGE_SIZE;

			//�v���C���[�ɒǏ]����
			if (!GetKeyboardPress(DIK_RIGHT) && !GetKeyboardPress(DIK_LEFT) && !GetKeyboardPress(DIK_UP) && !GetKeyboardPress(DIK_DOWN))
			{
				g_Camera[0].spd.x = (p_Player->GetPosition().x - g_Camera[0].pos.x) / g_Camera[0].trackingDelay.x;

				g_Camera[0].spd.y = (p_Player->GetPosition().y - 400 - g_Camera[0].pos.y) / g_Camera[0].trackingDelay.y;

				g_Camera[0].pos += g_Camera[0].spd;


				//�c�̃J�����̓����ɏ����ݒ�
				if (p_Player->GetPosition().y > SCREEN_HEIGHT)g_Camera[i].pos.y = g_Camera[i].oldPos.y;
				if (p_Player->GetPosition().x < SCREEN_WIDTH || g_MapSize.x - SCREEN_WIDTH < p_Player->GetPosition().x)g_Camera[i].pos.x = g_Camera[i].oldPos.x;//�v���C���[���[�̂Ƃ��̓J������Ǐ]�����Ȃ�
			}

			//�������󂫂�������v���C���[�̈ʒu�Ƀ��[�v
			if (abs(p_Player->GetPosition().y - g_Camera[0].pos.y) > SCREEN_HEIGHT)
			{
				g_Camera[0].pos.y = p_Player->GetPosition().y;
			}
			if (abs(p_Player->GetPosition().x - g_Camera[0].pos.x) > SCREEN_WIDTH)
			{
				g_Camera[0].pos.x = p_Player->GetPosition().x;
			}

			//�`�ʂɉ��Z����J�����̈ړ���
			g_Camera[i].cameraMove.x -= g_Camera[i].oldPos.x - g_Camera[i].pos.x;
			g_Camera[i].cameraMove.y -= g_Camera[i].oldPos.y - g_Camera[i].pos.y;
		}
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawCamera(void)
{
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		if (g_Camera[i].use)
		{
			DrawSpriteCamera(g_TexNo,
				g_Camera[i].pos.x,
				g_Camera[i].pos.y,
				g_Camera[i].size.x, g_Camera[i].size.y,	//���A����
				g_U, g_V,		//���SUV���W
				g_UW, g_VH		//�e�N�X�`�����A����
			);
		}
	}
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitCamera(void)
{

}

//---------------------------------------------------
// �J�����擾����
//---------------------------------------------------
CAMERA* GetCamera()
{
	return &g_Camera[0];
}

//---------------------------------------------------
// �J�����|�W�V�����擾
//---------------------------------------------------
D3DXVECTOR2 GetCameraPos(int cameraIndex)
{
	return g_Camera[cameraIndex].pos;
}

//---------------------------------------------------
// �J�����|�W�V�����擾
//---------------------------------------------------
D3DXVECTOR2 GetCameraNotLoopPos(int cameraIndex)
{
	return g_Camera[cameraIndex].notLoopPos;
}

//---------------------------------------------------
// �J�����`��␳�l�擾
//---------------------------------------------------
D3DXVECTOR2 GetCameraMoveVolume(int cameraIndex)
{
	return g_Camera[cameraIndex].cameraMove;
}

//---------------------------------------------------
// �J�����`��␳�l�擾(�w�i�p)
//---------------------------------------------------
D3DXVECTOR2 GetCameraMoveTotalVolume(int cameraIndex)
{
	return g_Camera[cameraIndex].cameraTotalMove;
}

//---------------------------------------------------
// �V�F�C�N [����]shakeMagnitude: �h�炷�傫��, shakeLength: �h�炷����
//---------------------------------------------------
void Shake(float shakeMagnitude, float shakeLength)
{
	g_ShakeRemain = shakeMagnitude;
	g_ShakeMagnitude = shakeMagnitude;
	g_ShakeLength = shakeLength;
}