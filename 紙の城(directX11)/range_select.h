//===================================================
//�}�b�v�͈͑I��(range_select.h)
//Auhor:�n� �C	Date:2024.1.20
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define RANGE_SELECT_MAX			(1)//�L�����N�^�[�̐�
#define RANGE_SELECT_WIDTH		(DEFAULT_TILE_SIZE)//�摜����
#define RANGE_SELECT_HEIGHT		(DEFAULT_TILE_SIZE)//�摜�c����
#define RANGE_SELECT_SPEED		(4.0f)//�ړ����x

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct RANGE_SELECT {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	spd;	//�X�s�[�h
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	int dir;	//����
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitRangeSelect(void);
void UninitRangeSelect(void);
void UpdateRangeSelect(void);
void DrawRangeSelect(void);

void SetRangeSelect(D3DXVECTOR2 pos, int dir);
void DecisionRangeSelect();
