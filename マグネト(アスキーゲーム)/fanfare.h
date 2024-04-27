//===================================================
//�t�@���t�@�[������(fanfare.h)
//Auhor:�n� �C	Date:2023.1.16
//===================================================
#ifndef _FANFARE_H_ //�C���N���[�h�K�[�h
#define _FANFARE_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_FANFARE (100) //�t�@���t�@�[���̐�

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�t�@���t�@�[���\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;	//x�X�s�[�h
	float ySpeed;	//y�X�s�[�h
	bool isUse;		//�g�p�t���O
}FANFARE;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeFanfare(void);
void UpdateFanfare(void);
void DrawFanfare(void);
void FinalizeFanfare(void);

void SetFanfare(float px, float py, float sx, float sy);
void SetFanfareFever(void);
FANFARE* GetFanfare(void);

#endif