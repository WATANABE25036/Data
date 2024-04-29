//===================================================
//�����蔻�萧��(collision.h)
//Auhor:�n� �C	Date::2023.2.16
//===================================================
#ifndef _COLLISION_H_ //�C���N���[�h�K�[�h
#define _COLLISION_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_COLLISION_X (8)	//�����蔻��̉�������(����̑傫��)
#define MAX_COLLISION_Y (4)	//�����蔻��̏c������(����̑傫��)

//===================================================
//�\���̐錾
//===================================================
typedef struct {	//�����蔻��\����
	float xPos[MAX_COLLISION_X];	//x���W
	float yPos[MAX_COLLISION_Y];	//y���W
	float oldXPos[MAX_COLLISION_X];	//1�t���[���O��x���W
	float oldYPos[MAX_COLLISION_Y];	//1�t���[���O��y���W
	bool magSTrigger[MAX_COLLISION_Y][MAX_COLLISION_X];//S�Ɏ���̉e���̔���
	bool magNTrigger[MAX_COLLISION_Y][MAX_COLLISION_X];//N�Ɏ���̉e���̔���
	bool blockTrigger;				//�V���v���u���b�N����
}COLLISION;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializeCollision(void);
void UpdateCollision(void);
void DrawCollision(void);
void FinalizeCollision(void);

COLLISION GetCollisionTopP(void);
COLLISION GetCollisionUnderP(void);
COLLISION GetCollisionRightP(void);
COLLISION GetCollisionLeftP(void);

#endif