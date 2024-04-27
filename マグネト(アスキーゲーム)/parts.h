//===================================================
//�j�А���(parts.h)
//Auhor:�n� �C	Date:2023.2.28
//===================================================
#ifndef _PARTS_H_ //�C���N���[�h�K�[�h
#define _PARTS_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_PARTS (300)
#define MAX_SPEED (0.5f)		//���E�̍ő�X�s�[�h
#define DEC_X (0.9f)		//����X(0.**�ŋL��)
#define DEC_Y (0.9f)		//����Y(0.**�ŋL��)
#define ACC (0.02f)			//����
#define JUMP_POWER (0.2f)	//�W�����v��
#define JUMP_MAX (5.0f)		//�W�����v����
#define PARTS_SPAWN_NUM (10)//�v���C���[�����ꂽ�Ƃ��ɏo��p�[�c�̐�

//===================================================
//�\���̐錾
//===================================================
typedef struct { //�j�Ѝ\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;	//x�X�s�[�h
	float ySpeed;	//y�X�s�[�h
	float gravity;	//�d��
	bool ground;	//�n�ʂɖʂ��Ă��邩
	bool minusBlock;	//�}�C�i�X�u���b�N�ɂ������Ă��邩�̔���
	bool isUse;		//�g�p�t���O
	bool moveBlockTrigger;
	bool xStackTrigger;
	bool yStackTrigger;
	int partsNum;	//�����ڂɍ��ꂽ�L�^����
}PARTS;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeParts(void);
void UpdateParts(void);
void DrawParts(void);
void FinalizeParts(void);

void SetParts(float px, float py);
void SetPartsFever(void);
PARTS* GetParts(void);
void allDeleteParts(void);

#endif