//===================================================
//���U���g���(result.cpp)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "result.h"
#include "tile.h"
#include "game_option.h"
#include "cursor.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "result_background.h"

#include "input.h"

//---------------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------------
unsigned int g_ResultTexture;
static int g_Result;

//---------------------------------------------------
//������
//---------------------------------------------------
void InitResult()
{
	char tilem[] =
	{
		"data\\BGM\\Clear.wav"
	};
	g_Result = LoadSound(&tilem[0]);
	PlaySound(g_Result, 0);
	InitResult_background();
	//InitCursor();
	//InitScore();

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
	UpdateResult_background();
	//UpdateCursor();
	//UpdateScore();
	
	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_START) || IsButtonTriggered(0, BUTTON_A))
	{
		//�w��V�[���Ɉڍs
		SetFadeColor(1.0f, 1.0f, 1.0f);
		SetFade(FADE_STATE_OUT);//�t�F�[�h�A�E�g�J�n���N�G�X�g
		SceneTransition(SCENE_TITLE);
	}
}

//---------------------------------------------------
//�`��
//---------------------------------------------------
void DrawResult()
{
	DrawResult_background();
	//DrawCursor();
	//DrawScore();
}

//---------------------------------------------------
//�I������
//---------------------------------------------------
void UninitResult()
{
	UninitResult_background();
	//UninitCursor();
	//UninitScore();
	StopSoundAll();
}
