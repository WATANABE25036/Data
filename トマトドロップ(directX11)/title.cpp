//===================================================
//�^�C�g�����(title.cpp)
//Auhor:�n� �C	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "title.h"
#include "title_logo.h"
#include "bg.h"
#include "title_tomato.h"
#include "game_option.h"
#include "cursor.h"
#include "fade.h"
#include "sound.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
unsigned int g_TitleTexture;
static int g_BGM;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitTitle()
{
	char bgm[] =
	{
		"data\\BGM\\nc309629.wav"
	};
	g_BGM = LoadSound(&bgm[0]);
	PlaySound(g_BGM, -1);
	InitBg();
	InitTitleTomato();
	InitTitleLogo();
	InitCursor();
	InitGameOption();
}

//---------------------------------------------------
//�X�V
//---------------------------------------------------
void UpdateTitle()
{
	if (GetFadeState() == FADE_STATE_OUT)
	{
		SetFadeColor(0.0f, 0.0f, 0.0f);//�Ȃ񂩓K���ȐF���Z�b�g
		SetFadeTime(30.0f);//time:���t���[���Ńt�F�[�h�������������������H
		SetFade(FADE_STATE_IN);
	}
	UpdateBg();
	UpdateTitleTomato();
	UpdateTitleLogo();
	UpdateCursor();
	UpdateGameOption();
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawTitle()
{
	DrawBg();
	DrawTitleTomato();
	DrawTitleLogo();
	DrawCursor();
	DrawGameOption();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitTitle()
{
	UninitBg();
	UninitTitleTomato();
	UninitTitleLogo();
	UninitCursor();
	UninitGameOption();
	StopSoundAll();
}
