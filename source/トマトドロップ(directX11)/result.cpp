//===================================================
//���U���g���(result.cpp)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "result.h"
#include "result_tomato.h"
#include "bg.h"
#include "game_option.h"
#include "cursor.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
unsigned int g_ResultTexture;
static int g_BGM;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitResult()
{
	char bgm[] =
	{
		"data\\BGM\\nc293887.wav"
	};
	g_BGM = LoadSound(&bgm[0]);
	PlaySound(g_BGM, 0);
	InitBg();
	InitResultTomato();
	InitGameOption();
	InitCursor();
	InitScore();

}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateResult()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
		SetFadeTime(30.0f);//time:���t���[���Ńt�F�[�h�������������������H
		SetFade(FADE_STATE_IN);
	}
	UpdateBg();
	UpdateResultTomato();
	UpdateGameOption();
	UpdateCursor();
	UpdateScore();
	
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawResult()
{
	DrawBg();
	DrawResultTomato();
	DrawGameOption();
	DrawCursor();
	DrawScore();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitResult()
{
	UninitBg();
	UninitResultTomato();
	UninitGameOption();
	UninitCursor();
	UninitScore();
	StopSoundAll();
}
