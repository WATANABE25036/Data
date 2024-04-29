//===================================================
//�v���C���[(player.h)
//Auhor:�n� �C	Date:2023.7.6
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PLAYER_WIDTH		(27.0f * 4.0f)//�摜����(���摜27�s�N�Z���̉摜��4�{�ɂ��Ďg�p)
#define PLAYER_HEIGHT		(27.0f * 4.0f)//�摜�c����
#define PLAYER_WIDTH_PATTERN	(10)//���A�j���p�^�[����
#define PLAYER_HEIGHT_PATTERN	(1)//�c�A�j���p�^�[����
#define PLAYER_MAX			(1)//�L�����N�^�[�̐�
#define PLAYER_FRAME_MAX	((PLAYER_WIDTH_PATTERN * PLAYER_HEIGHT_PATTERN) -1)//�t���[����
#define PLAYER_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define PLAYER_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define PLAYER_SPEED		(1.0f)//�v���C���[�̈ړ����x
#define PLAYER_WIDTH_MAX	(PLAYER_WIDTH * 4)
#define PLAYER_HEIGHT_MAX	(PLAYER_HEIGHT * 4)
#define PLAYER_BASE_ZOOM_RATE	(0.01f)	//��{�̎�O�ɗ��鑬��
#define PLAYER_ADD_ZOOM_RATE	(8.5f)	//��O�ɗ������̑����̑�����
#define PLAYER_DIS_SPEED_RATE	(10)	//�����ɂ��X�s�[�h�̑���
#define PLAYER_HET_RANGE				(-0.3f)	//�ǂƎ��ۂɓ����鋗��(�}�C�i�X���傫���قǂԂ���̂��x���Ȃ�)
#define PLAYER_DEFAULT_DIS		(1.5f)	//�ʏ펞�̃v���C���[�̉��s
#define PLAYER_DEFAULT_DIS_MOVE_SPEED	(0.01f)	//PLAYER_DEFAULT_DIS�Ɉړ����鑬��
#define PLAYER_START_DIS	(3.0f)	//��ԍŏ��̃g�}�g�̉��s
#define RANDOM_MOVE_SPAN	(5)	//�������̃v���v�����鑬��
#define PLAYER_MOVE_SE_SPZN	(10)	//SE��炷�X�p��
#define PLAYER_HET_SIZE		(0.3f)	//�q�b�g�{�b�N�X�ɂ��̒l���|����

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct PLAYER {
	D3DXVECTOR2		pos;	//�ʒu�x�N�g��
	D3DXVECTOR2		oldPos;	//�O�t���[���̈ʒu�x�N�g��
	D3DXVECTOR2		vel;	//���x�x�N�g��
	D3DXCOLOR		color;	//���_�J���[
	int				dir;	//����
	bool			use;	//�g�p���t���O
	D3DXVECTOR2		size;	//�T�C�Y
	float			dis;	//���ߋ���
	int				BufferIndex;//�����O�o�b�t�@�̎Q�ƃC���f�N�X
	D3DXVECTOR2		initSize;	//�����T�C�Y
	float			disRate;	//0(�ŉ�)�`1(�őO)
	float			speed;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer();
