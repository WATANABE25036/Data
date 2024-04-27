//===================================================
//�q�b�g�G�t�F�N�g(hit_spark.h)
//Auhor:�n� �C	Date:2023.9.3
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define HIT_SPARK_MAX			(100)//�L�����N�^�[�̐�
#define HIT_SPARK_WIDTH		(80 *6)//�摜����
#define HIT_SPARK_HEIGHT	(80 *6)//�摜�c����
#define HIT_SPARK_HITBOX_WIDTH		(40)//�q�b�g�G�t�F�N�g�̃q�b�g�{�b�N�X��
#define HIT_SPARK_HITBOX_HEIGHT		(40)//�q�b�g�G�t�F�N�g�̃q�b�g�{�b�N�X�c
#define HIT_SPARK_WIDTH_PATTERN	(10)//���A�j���p�^�[����
#define HIT_SPARK_HEIGHT_PATTERN	(11)//�c�A�j���p�^�[����
#define HIT_SPARK_FRAME_MAX	(HIT_SPARK_WIDTH_PATTERN * HIT_SPARK_HEIGHT_PATTERN)//�t���[����
#define HIT_SPARK_FRAME_SPAN	(5)//�A�j���[�V�����̃X�p��
#define HIT_SPARK_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[��
#define HIT_SPARK_SPEED		(8.0f)//�q�b�g�G�t�F�N�g�̈ړ����x

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct HIT_SPARK {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	float rot;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	int animeFrameMax;
	int animeSpan;
	bool reverse;
};

enum class EFFECT
{
	NONE,		//�G�t�F�N�g�Ȃ�
	COMBAT,		//�U���G�t�F�N�g
	SPLATTER,	//��������悤��
	RING,		//�~���L�����Ă���
	LEAF,		//��������
	COMBAT2,	//�U���G�t�F�N�g(�A�j���[�V�����Ȃ�)
	HIT_SPARK,	//�e����
	BALL,		//�����̋�
	COMBAT3,	//�؂艺��
	COMBAT4,	//�˂�
	LIGHT,		//���
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitHitSpark(void);
void UninitHitSpark(void);
void UpdateHitSpark(void);
void DrawHitSpark(void);

HIT_SPARK* GetHitSpark();
void SetHitSpark(EFFECT name, float posX, float posY, bool reverse = false, float rot = 0.0f, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetHitSpark(EFFECT name, D3DXVECTOR2 pos, bool reverse = false, float rot = 0.0f, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetHitSparkAnime(EFFECT name, int i);