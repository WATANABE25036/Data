//===================================================
//�v���C���[����(player.h)
//Auhor:�n� �C	Date:2023.1.13
//===================================================
#ifndef _PLAYER_H_ //�C���N���[�h�K�[�h(��d��`�̖h�~)
#define _PLAYER_H_

//===================================================
//�}�N����`
//===================================================
#define MAX_SPEED (0.5f)		//���E�̍ő�X�s�[�h
#define DEC_X (0.9f)		//����X(0.**�ŋL��)
#define DEC_Y (0.9f)		//����Y(0.**�ŋL��)
#define ACC (0.02f)			//����
#define JUMP_POWER (0.2f)	//�W�����v��
#define JUMP_MAX (5.0f)		//�W�����v����
#define MINUS_JUMP_POWER (JUMP_POWER / 3)	//�}�C�i�X�}�O�l�b�g�ׂ̗̎��̈ړ����x
#define RIGHT_FACING (1)	//�E����
#define LEFT_FACING (-1)	//������
#define UP_FACING (1)		//�����
#define DOWN_FACING (-1)	//������
#define MOTIONFRAME_MAX_PLAYER_WALK (4)	//�������[�V�����̊G�̖���
#define MOTIONFRAME_PLAYER_WALK (3)		//�������[�V�������x(�ꖇ������̕\������)
#define MOTIONFRAME_MAX_PLAYER_IDLE (40)//�ҋ@���[�V�����̊G�̖���
#define MOTIONFRAME_PLAYER_IDLE (5)		//�ҋ@���[�V�������x(�ꖇ������̕\������)
#define MOTIONFRAME_MAX_PLAYER_APPEAL (4)//�A�s�[�����[�V�����̊G�̖���
#define MOTIONFRAME_PLAYER_APPEAL (20)	//�A�s�[�����[�V�������x(�ꖇ������̕\������)
#define RESPAWN_TIMER (60 * 2)			//���X�|�[���܂ł̑ҋ@����
#define REMAIN (10)	//�c�@

//===================================================
//�񋓑̐錾
//===================================================
typedef enum
{
	RISE = 0,		//�㏸��
	FALL,			//���~��
	IDLE,			//�����Ă��Ȃ�
	WALK,			//����
	APPEAL,			//�S�[������
	MAGNET_S_TOP,	//�������Ă���
	MAGNET_S_RIGHT,	//�������Ă���
	MAGNET_S_LEFT	//�������Ă���
}STATE;

//===================================================
//�\���̐錾
//===================================================
typedef struct { //�v���C���[�\����
	float xPos;		//x���W
	float yPos;		//y���W
	float oldXPos;	//1�t���[���O��x���W
	float oldYPos;	//1�t���[���O��y���W
	float xSpeed;	//x�X�s�[�h
	float ySpeed;	//y�X�s�[�h
	int facing;		//���E�̌���
	int upDownfacing;	//���΂ɂ������Ă�Ƃ��̏㉺�̌���
	int state;		//���
	int oldState;	//1�t���[���O�̏��
	int chargCnt;	//�`���[�W�V���b�g�p�J�E���^�[
	float gravity;	//�d��
	bool dead;		//���S����
	int stageNum;	//���݂̃X�e�[�W�i���o�[
	bool goal;		//�S�[������
	int motionCnt;	//���[�V�����̃J�E���g
	bool minusBlock;//�}�C�i�X�u���b�N�ɂ������Ă��邩�̔���
	bool plusBlock;//�v���X�u���b�N�̉e�����󂯂Ă��邩�̔���
	bool isUse;		//�g�p�t���O
	bool respawn;	//���X�|�[���ł��邩�ǂ���
	bool inportSwitch;	//�}�O�l�b�g�̐؂�ւ�����Ǘ�
	int remain;		//�c�@
}PLAYER;

//===================================================
//�v���g�^�C�v�錾
//===================================================
void InitializePlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void FinalizePlayer(void);

void SetPlayer(float px = 1.0f, float py = 1.0f);
PLAYER GetPlayer(void);
#endif