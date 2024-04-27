//===================================================
//���(barrier.h)
//Auhor:�n� �C	Date:2023.7.11
//===================================================
#pragma once
#include <string>
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define BARRIER_WIDTH		(16)	//�摜����
#define BARRIER_HEIGHT		(16)	//�摜�c����
#define BARRIER_MAX			(200)		//�L�����N�^�[�̐�
#define BARRIER_FRAME_SPAN	(5)		//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define BARRIER_WIDTH_MAX	(SCREEN_WIDTH + 700)/4
#define BARRIER_HEIGHT_MAX	(SCREEN_HEIGHT + 700)/4
#define BARRIER_DEFAULT_ALPHA	(0.85f)

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct BARRIER {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		oldPos;	//�ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXVECTOR2		speed;	//���x
	D3DXCOLOR		color;	//���_�J���[
	bool			use;	//�g�p���t���O
	D3DXVECTOR2		size;	//�T�C�Y
	D3DXVECTOR2		oldSize;	//�T�C�Y
	float			dis;	//���ߋ���
	float			disRate;
	int				g_num;
	float			rot;	//�p�x
	D3DXVECTOR2		initSize;//�����T�C�Y
	D3DXVECTOR2		initPos;//�����|�W�V����
	D3DXVECTOR2		maxSize;//�ł���O�ɗ������̑傫��
	float			rotSpeed;//��]���x
	D3DXVECTOR2		adjVel;	//�v���C���[�̈ʒu�ɑ΂���x�N�g��
};

//---------------------------------------------------
//�񋓑̐錾
//---------------------------------------------------
typedef enum
{
	BARRIER_COLOR_RANDOM,
	BARRIER_COLOR_RED,
	BARRIER_COLOR_GREEN,
	BARRIER_COLOR_BLUE,
	BARRIER_COLOR_YELLOW,
	BARRIER_COLOR_MAGENTA,
	BARRIER_COLOR_CYAN,
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitBarrier();
void UninitBarrier();
void UpdateBarrier();
void DrawBarrier(int g_num);

BARRIER* GetBarrier();
void SetBarrier(int wallNum, float posX, float posY, float sizeX, float sizeY, float rot = 0.0f, int color = BARRIER_COLOR_RANDOM, float speedX = 0.0f, float speedY = 0.0f, float rotSpeed = 0.0f);
void StopBarrier();