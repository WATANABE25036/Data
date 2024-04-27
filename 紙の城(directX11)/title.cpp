//===================================================
//�^�C�g�����(title.cpp)
//Auhor:�n� �C	Date:2023.8.4
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "title.h"
#include "title_logo.h"
#include "tile.h"
#include "title_background.h"
#include "game_option.h"
#include "cursor.h"
#include "fade.h"
#include "sound.h"

#include "input.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
unsigned int g_TitleTexture;
static int g_Result;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitTitle()
{
	char tilem[] =
	{
		"data\\BGM\\Title.wav"
	};
	g_Result = LoadSound(&tilem[0]);
	//SetVolume(g_Result, 0.3f);//����
	PlaySound(g_Result, -1, 0.4f);

	InitTitleBackground();
	InitTitleLogo();
	//InitCursor();
	//InitGameOption();
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

	UpdateTitleBackground();
	UpdateTitleLogo();
	//UpdateCursor();
	//UpdateGameOption();

	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_A))
	{
		//�w��V�[���Ɉڍs
		SetFadeColor(1.0f, 1.0f, 1.0f);
		SetFade(FADE_STATE_OUT);//�t�F�[�h�A�E�g�J�n���N�G�X�g
		SceneTransition(SCENE_GAME);
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawTitle()
{

	DrawTitleBackground();
	DrawTitleLogo();
	//DrawCursor();
	//DrawGameOption();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitTitle()
{

	UninitTitleBackground();
	UninitTitleLogo();
	//UninitCursor();
	//UninitGameOption();
	StopSoundAll();
}
