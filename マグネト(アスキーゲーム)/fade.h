//===================================================
//�Ó]����(fade.h)
//Auhor:�n� �C	Date:2023.2.25
//===================================================
#ifndef _FADE_H_ //�C���N���[�h�K�[�h
#define _FADE_H_

#include "drawing.h"

//===================================================
//�}�N����`
//===================================================
#define MAX_FADE ((DRAWING_WIDTHW_MAX / 2) * DRAWING_HEIGHT_MAX)	//�Ó]�̐�

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�Ó]�\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;		//�X�s�[�h
	float ySpeed;		//�X�s�[�h
	bool isUse;			//�g�p�t���O
}FADE;

//===================================================
//�񋓑̐錾
//===================================================

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeFade(void);
void UpdateFade(void);
void DrawFade(void);
void FinalizeFade(void);

void SetFadeOut(void);
void SetFadeIn(void);
bool GetBlacKOutTrigger(void);

FADE* GetFadeLeft(void);
FADE* GetFadeRight(void);

#endif
