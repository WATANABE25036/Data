//===================================================
//��(wall.h)
//Auhor:�n� �C	Date:2023.7.6
//===================================================
#pragma once
#include <string>
#include "main.h"
#include "renderer.h"
#include "barrier.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define WALL_WIDTH		(768)	//�摜����
#define WALL_HEIGHT		(432)	//�摜�c����
#define WALL_MAX		(300)	//�L�����N�^�[�̐�
#define WALL_FRAME_SPAN	(5)		//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define WALL_SPEED		(0.1f)	//�ړ����x
#define WALL_SET_SPEED	(5)		//���̕ǂ��o���X�s�[�h(-�̂ق����X�s�[�h����)
#define WALL_BARRIER_SET_SPEED	(0)	//��ǐݒu�X�s�[�h�␳(-�̂ق����X�s�[�h����)
#define WALL_ZOOM_SPEED	(0.01)	//��O�ɗ��鑬��
#define WALL_NORMAL		(-1)	//�ǂ̎��(�Ȃ�)
#define WALL_BARRIER	(0)		//�ǂ̎��(���)
#define WALL_WIDTH_MAX	(SCREEN_WIDTH + 700)
#define WALL_HEIGHT_MAX	(SCREEN_HEIGHT + 700)
#define BASE_ZOOM_RATE	(0.01f)	//��{�̎�O�ɗ��鑬��
#define ADD_ZOOM_RATE	(8.5f)	//��O�ɗ������̑����̑�����
#define WALL_INIT_WIDTH		(WALL_WIDTH * 0.1f)	//�ŏ��̕ǂ̉���
#define WALL_INIT_HEIGHT	(WALL_HEIGHT * 0.1f)//�ŏ��̕ǂ̏c��
#define WALL_INIT_WIDTH_HALF	(WALL_INIT_WIDTH * 0.5f)//�ŏ��̕ǂ̌��_X
#define WALL_INIT_HEIGHT_HALF	(WALL_INIT_HEIGHT * 0.5f)//�ŏ��̕ǂ̌��_Y
#define WALL_INIT_WIDTH_HALFHALF	(WALL_INIT_HEIGHT_HALF * 0.5f)
#define WALL_INIT_HEIGHT_HALFHALF	(WALL_INIT_HEIGHT_HALF * 0.5f)
#define MAX_PATTERN_SCORE			(3000)
#define WALL_ALPHA_ADD				(0.05f)//�ǐݒu����A���t�@���グ�Ă������x

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct WALL {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
	bool			use;	//�g�p���t���O
	D3DXVECTOR2		size;	//�T�C�Y
	D3DXVECTOR2		oldSize;	//�T�C�Y
	int				mode;	//�ǂ̎��
	float			dis;	//���ߋ���
	int				g_num;
	D3DXVECTOR2		initSize;	//�����T�C�Y
	float			disRate;	//0(�ŉ�)�`1(�őO)
	float			zoomSpeed;
	D3DXVECTOR2		initPos;	//�����ʒu
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitWall();
void UninitWall();
void UpdateWall();
void DrawWall();

WALL* GetWall();
void SetWall(int mode = -1, float posX = 0.0f, float posY = 0.0f, float sizeX = 0.0f, float sizeY = 0.0f, float rot = 0.0f, int color = BARRIER_COLOR_RANDOM, float speedX = 0.0f, float speedY = 0.0f, float rotSpeed = 0.0f);
void StopWall();