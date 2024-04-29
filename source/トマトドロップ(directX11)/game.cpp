//===================================================
//�Q�[�����(game.cpp)
//Auhor:�n� �C	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "game.h"
#include "wall.h"
#include "barrier.h"
#include "dead.h"
#include "fog.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
static int g_BGM;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitGame()
{
	char bgm[] =
	{
		"data\\BGM\\nc296708.wav"
	};
	g_BGM = LoadSound(&bgm[0]);
	PlaySound(g_BGM, -1);
	InitPlayer();
	InitWall();
	InitBarrier();
	InitDead();
	InitFog();
	InitScore();
	SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
	SetFadeTime(240.0f);//time:���t���[���Ńt�F�[�h�������������������H
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateGame()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
		SetFadeTime(30.0f);//time:���t���[���Ńt�F�[�h�������������������H
		SetFade(FADE_STATE_IN);
	}
	UpdatePlayer();
	UpdateWall();
	UpdateBarrier();
	UpdateDead();
	UpdateFog();
	UpdateScore();
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawGame()
{
	//DrawBarrier()�͕ǂŌĂяo�����ߓ���Ȃ�
	//DrawFog()�͕ǂŌĂяo�����ߓ���Ȃ�
	DrawWall();
	//DrawPlayer()�͕ǂŌĂяo�����ߓ���Ȃ�;
	DrawDead();
	DrawScore();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitGame()
{
	UninitDead();
	UninitBarrier();
	UninitWall();
	UninitPlayer();
	UninitFog();
	UninitScore();
	StopSoundAll();
}
