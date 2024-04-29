//===================================================
//�w�i(bg.h)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define BG_WIDTH		(SCREEN_WIDTH)//�摜����
#define BG_HEIGHT		(SCREEN_HEIGHT)//�摜�c����
#define BG_WIDTH_PATTERN	(4)//���A�j���p�^�[����
#define BG_HEIGHT_PATTERN	(4)//�c�A�j���p�^�[����
#define BG_MAX			(1)//�L�����N�^�[�̐�
#define BG_FRAME_MAX	((BG_WIDTH_PATTERN * BG_HEIGHT_PATTERN) -1)//�t���[����
#define BG_FRAME_SPAN	(32)//�A�j���[�V�����̃X�p��
#define BG_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitBg(void);
void UpdateBg(void);
void DrawBg(void);
void UninitBg(void);
