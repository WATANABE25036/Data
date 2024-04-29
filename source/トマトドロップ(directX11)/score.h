//===================================================
//�X�R�A(score.h)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#pragma once

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define SCORE_MAX		(30)
#define SCORE_FIGURE	(6)
#define RANK_FIGURE		(1)
#define SCORE_SCALE_MAX			(1.2f)
#define SCORE_SCALE_UP_SPEED	(0.005f)
#define SCORE_SCALE_DOWN_SPEED	(0.01f)
#define SCORE_FANFARE_SCORE		(200)
#define SCORE_INIT_SCORE		(0)

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitScore();
void UninitScore();
void UpdateScore();
void DrawScore();

void AddScore(int Score);

bool SaveScore();
bool LoadScore();
void SortScore();
void SetDrawScore(int score, float posX, float posY, float sizeX, float sizeY, float scale);
void SetDrawRank(int score, float posX, float posY, float sizeX, float sizeY);
int GetScore();
float EaseInOut(float t);
void SetScore(int Score);
