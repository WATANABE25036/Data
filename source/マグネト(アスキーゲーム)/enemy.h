//===================================================
//�G����(enemy.h)
//Auhor:�n� �C	Date::2023.1.17
//===================================================
#ifndef _ENEMY_H_ //�C���N���[�h�K�[�h
#define _ENEMY_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_ENEMY (100) //�G�̐�

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�G�\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;	//x�X�s�[�h
	float ySpeed;	//y�X�s�[�h
	int moveTime;	//�ړ�����
	bool isUse;		//�g�p�t���O
}ENEMY;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void FinalizeEnemy(void);

void SetEnemy(float px, float py, float sx = 0.0f, float sy = 0.0f);//�����������ȗ����鏑����
ENEMY* GetEnemy(void);

#endif