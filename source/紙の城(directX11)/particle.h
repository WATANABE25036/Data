//===================================================
//���q(particle.h)
//Auhor:�n� �C	Date:2023.9.9
//===================================================
#pragma once
#include "main.h"
#include "renderer.h"
#include "hit_spark.h"

//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PARTICLE_MAX			(1000)//�L�����N�^�[�̐�
#define PARTICLE_WIDTH		(20)//�摜����
#define PARTICLE_HEIGHT		(20)//�摜�c����
#define PARTICLE_HITBOX_WIDTH		(20 * 0.3f)//���q�̃q�b�g�{�b�N�X��
#define PARTICLE_HITBOX_HEIGHT	(20 * 0.3f)//���q�̃q�b�g�{�b�N�X�c
#define PARTICLE_FRAME_SPAN	(2)//�A�j���[�V�����̃X�p��
#define PARTICLE_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
struct PARTICLE {
	D3DXVECTOR2	pos;	//�ʒu�x�N�g��
	D3DXVECTOR2	spd;	//���x�x�N�g��
	D3DXCOLOR color;	//���_�J���[
	bool use;			//�g�p���t���O
	D3DXVECTOR2 size;	//�T�C�Y
	float rot;
	float sp;
	D3DXVECTOR2 uv;
	int animePattern;
	int animeWidthPattern;
	int animeBasePattern;
	int animeSkipFrame;
	int animeFrameMax;
	bool reverse;
	float releaseX;
	float releaseY;
	float grv;
	D3DXVECTOR2 scale;
	D3DXCOLOR color255;
	bool loop;
	EFFECT hit;
};

//---------------------------------------------------
//�v���g�^�C�v�錾
//---------------------------------------------------
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

PARTICLE* GetParticle();
void SetParticle(EFFECT name, float posX, float posY, int num, float minPower = 0.5f, float maxPower = 20.0f, bool loop = false, bool reverse = false, EFFECT hit = EFFECT::NONE, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetParticle(EFFECT name, D3DXVECTOR2 pos, int num, float minPower = 0.5f, float maxPower = 20.0f, bool loop = false, bool reverse = false, EFFECT hit = EFFECT::NONE, float r = 255.0f, float g = 255.0f, float b = 255.0f);
void SetParticleRelease(int index, float power, float radian);
void SetParticleAnime(EFFECT name, int i);

