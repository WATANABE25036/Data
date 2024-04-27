//===================================================
//�^�C�g���w�i(title_background.h)
//Auhor:�n� �C	Date:2023.8.5
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define TITLE_BACKGROUND_WIDTH		(1920)//�摜����
#define TITLE_BACKGROUND_HEIGHT		(1080)//�摜�c����
#define TITLE_BACKGROUND_WIDTH_PATTERN	(10)//���A�j���p�^�[����
#define TITLE_BACKGROUND_HEIGHT_PATTERN	(15)//�c�A�j���p�^�[����
#define TITLE_BACKGROUND_MAX			(1)//�L�����N�^�[�̐�
#define TITLE_BACKGROUND_FRAME_MAX	(145)//�t���[����
#define TITLE_BACKGROUND_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define TITLE_BACKGROUND_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitTitleBackground(void);
void UpdateTitleBackground(void);
void DrawTitleBackground(void);
void UninitTitleBackground(void);
