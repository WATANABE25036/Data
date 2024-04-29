//=============================================================================
//�^�C�g�� [title.cpp]
//Author:�n� �C	Date:2023.1.19
//=============================================================================
#include "title.h"
#include "main.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "drawing.h"
#include "gameControl.h"
#include "block.h"
#include "collision.h"
#include "fade.h"
#include "fanfare.h"
#include "parts.h"

#define CONIOEX
#include "conioex.h"

//===================================================
//�O���[�o���ϐ�
//===================================================
int g_decisionSe;
int g_cnt;
int g_trigger;

//===================================================
//������
//===================================================
void InitializeTitle(void)
{
	InitializePlayer();
	InitializeBullet();
	InitializeEnemy();
	InitializeExplosion();
	InitializeScore();
	InitializeDrawing();
	InitializeGameControl();
	InitializeBlock();
	InitializeCollision();
	InitializeFade();
	InitializeFanfare();
	InitializeParts();
	g_cnt = 0;
	g_trigger = false;
	g_decisionSe = opensound("Data\\decision.mp3");
}

//===================================================
//�X�V
//===================================================
void UpdateTitle(void)
{
	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateExplosion();
	UpdateScore();
	UpdateDrawing();
	UpdateGameControl();
	UpdateBlock();
	UpdateCollision();
	UpdateFade();
	UpdateFanfare();
	UpdateParts();

	if ((inport(PK_ENTER) || inport(PJ1_BTNS) == 128) && !g_trigger)
	{
		playsound(g_decisionSe, 0);

		g_trigger = true;
	}

	if (g_trigger)
	{
		g_cnt++;
	}

	if (g_cnt >= 50)
	{
		SetScene(SCENE_GAME);
	}

}
//===================================================
//�`��
//===================================================
void DrawTitle(void)
{
	DrawBullet();
	DrawEnemy();
	DrawPlayer();
	DrawExplosion();
	DrawScore();
	DrawDrawing();
	DrawGameControl();
	DrawBlock();
	DrawCollision();
	DrawFade();
	DrawFanfare();
	DrawParts();
}
//===================================================
//����
//===================================================
void FinalizeTitle(void)
{
	FinalizePlayer();
	FinalizeBullet();
	FinalizeEnemy();
	FinalizeExplosion();
	FinalizeScore();
	FinalizeDrawing();
	FinalizeGameControl();
	FinalizeBlock();
	FinalizeCollision();
	FinalizeFade();
	FinalizeFanfare();
	FinalizeParts();
	closesound(g_decisionSe);
}