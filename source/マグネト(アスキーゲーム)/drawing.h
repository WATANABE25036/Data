//===================================================
//�}�b�v����(drawing.h)
//Auhor:�n� �C	Date:2023.1.24
//===================================================
#ifndef _DRAWING_H_ //�C���N���[�h�K�[�h(��d��`�̖h�~)
#define _DRAWING_H_

#define CONIOEX
#include "conioex.h"

//===================================================
//�}�N����`
//===================================================
#define DRAWING_WIDTHW_MAX (188)//�E�̕`��͈�(101)
#define DRAWING_HEIGHT_MAX (47)	//���̕`��͈�(30)
#define DRAWING_WIDTHW_MIN (0)	//���̕`��͈�(0)
#define DRAWING_HEIGHT_MIN (0)	//��̕`��͈�(0)
#define BACK_COLOR (WHITE)		//�w�i�F
#define NOT_COLOR (72)			//�w��F�Ȃ�
#define ASCLl_COLOR (LIGHTGRAY)	//�����̐F
#define ASCLl_BACK_COLOR (DARKGRAY)//�����̔w�i�F
#define START_TOP_COLOR (LIGHTMAGENTA)	//�X�^�[�g�̏��
#define START_COLOR (MAGENTA)			//�X�^�[�g�̑���
#define GOAL_TOP_COLOR (LIGHTGREEN)		//�S�[���̏��
#define GOAL_COLOR (GREEN)				//�S�[���̑���

//===================================================
//�\���̐錾
//===================================================
typedef struct//�o�b�t�@�p�\����
{ 
	char moji[2];
	int color;
	int backColor;
}BUFFER;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeDrawing(void);
void UpdateDrawing(void);
void DrawDrawing(void);
void FinalizeDrawing(void);

void BufferSet(BUFFER* p, int x, int y, char* moji, int color, int backColor = NOT_COLOR);
void BufferPrint(BUFFER* p0, BUFFER* p1);
void PlayerMotionRightTurn(int startFrame);
void PlayerMotionRightRise(void);
void PlayerMotionRightFall(void);
void PlayerMotionLeftTurn(int startFrame);
void PlayerMotionLeftRise(void);
void PlayerMotionLeftFall(void);

#endif
