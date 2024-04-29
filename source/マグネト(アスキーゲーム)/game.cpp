//=============================================================================
//ÉQÅ[ÉÄÉÅÉCÉìêßå‰ [game.cpp]
//Author:ìnÁ≥ èC	Date:2023.1.19
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
//èâä˙âª
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
//çXêV
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
//ï`âÊ
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
//èàóù
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