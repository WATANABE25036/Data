/*********************************************************************
 * \file   PepperEnemy.h
 * \brief   
 * \author �}�@�R�E�����E
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#pragma once
//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PEPPER_MAX			(1)//�L�����N�^�[�̐�
#define PEPPER_WIDTH		(DEFAULT_TILE_SIZE*0.6)//�摜����
#define PEPPER_HEIGHT		(DEFAULT_TILE_SIZE*0.6)//�摜�c����
#define PEPPER_HITBOX_WIDTH		(PEPPER_WIDTH * 0.5f)//�v���C���[�̃q�b�g�{�b�N�X��
#define PEPPER_HITBOX_HEIGHT	(PEPPER_HEIGHT)//�v���C���[�̃q�b�g�{�b�N�X�c
#define PEPPER_WIDTH_PATTERN	(7)//���A�j���p�^�[����
#define PEPPER_HEIGHT_PATTERN	(2)//�c�A�j���p�^�[����
#define PEPPER_FRAME_MAX	((PEPPER_WIDTH_PATTERN * PEPPER_HEIGHT_PATTERN) -1)//�t���[����
#define PEPPER_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define PEPPER_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define PEPPER_SPEED		(8.0f)//�v���C���[�̈ړ����x
#define PEPPER_INIT_HP		(3)//�����̗�
#define PEPPER_UNBEATABLE_TEME (80)//���G����



class PepperEnemy :public EntityBase
{
	StateMachine<PepperEnemy>*		_pepperEnemyFsm;
	void CollisionHandling();

public:
	PepperEnemy(int TexNo):EntityBase("PepperEnemy") 
	{ 
		_textureNo = TexNo;
		Init();
	}
	~PepperEnemy() 
	{ 
		UnInit(); 
		delete _pepperEnemyFsm;
	}

	
	StateMachine<PepperEnemy>* GetFsm() const { return _pepperEnemyFsm; }

	void Attacked();
	void PositionHandling();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	//��
	Vec2 offset;
	float g_time;
	int _SE_hit;
};

