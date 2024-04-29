//===================================================
//�����A�j���[�V��������(explosion.h)
//Auhor:�n� �C	Date::2023.1.19
//===================================================
#ifndef _EXPLOSION_H_ //�C���N���[�h�K�[�h
#define _EXPLOSION_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_EXPLOSION (100)					//�����A�j���[�V�����̐�
#define ANIMATION_FRAME_EXPLOSION (2)		//1�A�j���̕\���t���[��
#define ANIMATION_FRAME_MAX_EXPLOSION (4)	//�A�j���[�V�����̖���

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�����A�j���[�V�����\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;	//x�X�s�[�h
	float ySpeed;	//y�X�s�[�h
	int frameCut;	//�A�j���[�V�����J�E���g
	bool isUse;		//�g�p�t���O
}EXPLOSION;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void FinalizeExplosion(void);

void SetExplosion(float px, float py, float sx = 0.0f, float sy = 0.0f);//�����������ȗ����鏑����
EXPLOSION* GetExplosion(void);

#endif