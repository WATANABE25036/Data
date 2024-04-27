//===================================================
//�u���b�N����(block.h)
//Auhor:�n� �C	Date:2023.2.7
//===================================================
#ifndef _BLOCK_H_ //�C���N���[�h�K�[�h
#define _BLOCK_H_

#include "drawing.h"

//===================================================
//�}�N����`
//===================================================
#define MAX_BLOCK (DRAWING_HEIGHT_MAX * DRAWING_WIDTHW_MAX)	//�u���b�N�̐�
#define MAX_BLOCK_WIDE (15)	//���̃u���b�N��(101)
#define MAX_BLOCK_HEIGHT (6)	//�c�̃u���b�N��(30)
#define TURRET_RATE (2.5f)				//�A�ˑ��x(�Ⴂ = ����)
#define TURRET_PRECISION (5)		//���ː��x(�Ⴂ = �΂���Ȃ�)
#define TURRET_BULLET_SPEED (1.0f)	//�e�̑���(���� = ����)

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�u���b�N�\����
	float xPos[MAX_BLOCK_WIDE];		//x���W
	float yPos[MAX_BLOCK_HEIGHT];		//y���W
	float oldXPos[MAX_BLOCK_WIDE];		//1�t���[���O��x���W
	float oldYPos[MAX_BLOCK_HEIGHT];	//1�t���[���O��y���W
	int mode;			//�u���b�N�̎��
	bool untouch;		//�G����邩
	float speed;		//�X�s�[�h
	int targetXS;		//����x���W�ɗ�����X1�Ɍ�����(�X�^�[�g�n�_)
	int targetYS;		//����y���W�ɗ�����Y1�Ɍ�����(�X�^�[�g�n�_)
	int targetX1;		//����x���W�ɗ�����X2�Ɍ�����
	int targetY1;		//����y���W�ɗ�����Y2�Ɍ�����
	int targetX2;		//����x���W�ɗ�����X3�Ɍ�����
	int targetY2;		//����y���W�ɗ�����Y3�Ɍ�����
	int targetX3;		//����x���W�ɗ�����XS�Ɍ�����
	int targetY3;		//����y���W�ɗ�����YS�Ɍ�����
	int target;			//�i�ނׂ��^�[�Q�b�g
	bool startTrigger;	//���߂Ɉ�񂾂����s����Ƃ��p
	bool isUse;			//�g�p�t���O
	bool isUseWide[MAX_BLOCK_WIDE];		//���̃u���b�N�̎g�p�t���O
	bool isUseHeight[MAX_BLOCK_HEIGHT];	//�c�̃u���b�N�̎g�p�t���O
	bool topBlock[MAX_BLOCK_HEIGHT];	//���ʂ̌����ڂ�ς��邽��
}BLOCK;

//===================================================
//�񋓑̐錾
//===================================================
typedef enum
{
	TARGET_START = 0,
	TARGET_1,
	TARGET_2,
	TARGET_3
}TARGET;

typedef enum
{
	AIR = 0,
	BLOCK_SIMPLE,
	BLOCK_MAGNET_PLUS,
	BLOCK_MAGNET_MINUS,
	BLOCK_TURRET_LEFT,
	BLOCK_TURRET_RIGHT,
	BLOCK_TURRET_TOP,
	BLOCK_TURRET_UNDER,
	BLOCK_START,
	BLOCK_GOAL
}BLOCK_MODE;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void FinalizeBlock(void);

void SetBlock(float px, float py, int mode = BLOCK_SIMPLE, bool topBlock = true, int wide = 1, int height = 1, float speed = 0.0f, int targetX1 = 0, int targetY1 = 0, int targetX2 = 0, int targetY2 = 0, int targetX3 = 0, int targetY3 = 0);
void allDeleteBlock(void);
BLOCK* GetBlock(void);

#endif
