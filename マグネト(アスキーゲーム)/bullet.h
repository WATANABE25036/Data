//===================================================
//�e����(bullet.h)
//Auhor:�n� �C	Date:2023.1.16
//===================================================
#ifndef _BULLET_H_ //�C���N���[�h�K�[�h
#define _BULLET_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_BULLET (200) //�e�̐�

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�e�\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;	//x�X�s�[�h
	float ySpeed;	//y�X�s�[�h
	bool isUse;		//�g�p�t���O
}BULLET;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void FinalizeBullet(void);

void SetBullet(float px, float py, float sx, float sy);
BULLET* GetBullet(void);

#endif