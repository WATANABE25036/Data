//===================================================
//Q[æÊ(game.h)
//Auhor:nç³ C	Date:2023.8.4
//===================================================
#pragma once
#ifndef GAME_H_
#define GAME_H_

//---------------------------------------------------
//}Nè`
//---------------------------------------------------

//---------------------------------------------------
//ñÌé¾
//---------------------------------------------------
typedef enum
{
	GAME_STATE_IDLE_1,
	GAME_STATE_READY,
	GAME_STATE_IDLE_2,
	GAME_STATE_START,
	GAME_STATE_PLAY,
	GAME_STATE_OVER,
	GAME_STATE_CLEAR,
}GAME_STATE;

//---------------------------------------------------
//vg^Cvé¾
//---------------------------------------------------
void InitGame();
void UninitGame();
void UpdateGame();
void DrawGame();

#endif