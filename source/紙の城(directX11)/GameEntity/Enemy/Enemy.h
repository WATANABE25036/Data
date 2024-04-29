/*********************************************************************
 * \file   Enemy.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "..\..\renderer.h"
#include "..\EntityBase.h"
#include "EnemybulletSpawn.h"
#include "..\..\Fsm\StateMachine.h"
#include "..\..\sound.h"
#include <string>


//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define ENEMY_MAX			(50)//�L�����N�^�[�̐�
#define ENEMY_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�摜����
#define ENEMY_HEIGHT		(DEFAULT_TILE_SIZE * 0.5f)//�摜�c����
#define ENEMY_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�G�l�~�[�̃q�b�g�{�b�N�X��
#define ENEMY_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.5f)//�G�l�~�[�̃q�b�g�{�b�N�X�c
#define ENEMY_WIDTH_PATTERN	(4)//���A�j���p�^�[����
#define ENEMY_HEIGHT_PATTERN	(5)//�c�A�j���p�^�[����
#define ENEMY_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//�t���[����
#define ENEMY_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define ENEMY_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define ENEMY_SPEED		(4.0f)//�G�l�~�[�̈ړ����x
#define ENEMY_UNBEATABLE_TEME (20)//���G����
#define ENEMY_INIT_HP (1)


//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
class Enemy:public EntityBase
{
	bool _jump;
	StateMachine<Enemy>* _enemyFsm;
	void GroundDetection();
	

public:
	void Attack(D3DXVECTOR2 targetPos)
	{
		EnemyBulletSpawn::Instance()->SetBullet(_pos, targetPos, 150, 0.8f);
	}
	const bool GetJump()const { return _jump; }
	
	Enemy(int TexNo) :EntityBase("Enemy")
	{
		_textureNo = TexNo;
		Init();
	};
	~Enemy() override
	{ 
		UnInit();
		delete _enemyFsm;
	}

	HitBox _attackBox;

	StateMachine<Enemy>* GetFsm() const { return _enemyFsm; }
	void Attacked();
	// ͨ�� EntityBase �̳�
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	//��
	int _SE_hit;
	int _SE_enemyDown;
	int g_shotTime;
};

