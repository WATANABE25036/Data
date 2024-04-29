//===================================================
//���U���g�g�}�g(result_tomato.h)
//Auhor:�n� �C	Date:2023.8.8
//===================================================
#pragma once
#include "main.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define RESULT_TOMATO_WIDTH		(1824*0.5f)//�摜����
#define RESULT_TOMATO_HEIGHT		(1240*0.5f)//�摜�c����
#define RESULT_TOMATO_WIDTH_PATTERN	(4)//���A�j���p�^�[����
#define RESULT_TOMATO_HEIGHT_PATTERN	(5)//�c�A�j���p�^�[����
#define RESULT_TOMATO_MAX			(1)//�L�����N�^�[�̐�
#define RESULT_TOMATO_FRAME_MAX	((RESULT_TOMATO_WIDTH_PATTERN * RESULT_TOMATO_HEIGHT_PATTERN) -1)//�t���[����
#define RESULT_TOMATO_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define RESULT_TOMATO_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitResultTomato(void);
void UpdateResultTomato(void);
void DrawResultTomato(void);
void UninitResultTomato(void);
