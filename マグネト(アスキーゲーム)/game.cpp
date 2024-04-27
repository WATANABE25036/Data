//=============================================================================
//�Q�[�����C������ [game.cpp]
//Author:�n� �C	Date:2023.1.19
//=============================================================================
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
//������
//===================================================
void InitializeGame(void)
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
}

//===================================================
//�X�V
//===================================================
void UpdateGame(void)
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
}
//===================================================
//�`��
//===================================================
void DrawGame(void)
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
void FinalizeGame(void)
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
}