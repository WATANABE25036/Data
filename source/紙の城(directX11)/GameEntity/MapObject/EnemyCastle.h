/*********************************************************************
 * \file   EnemyCastle.h
 * \brief
 * \author
 * \date   2024 \ 03 \ 03
 *********************************************************************/
#pragma once

#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#include "..\..\HpBar.h"

 //---------------------------------------------------
 //�}�N����`
 //---------------------------------------------------
#define ENEMY_CASTLE_MAX			(1)//�L�����N�^�[�̐�
#define ENEMY_CASTLE_WIDTH			(DEFAULT_TILE_SIZE*10)//�摜����
#define ENEMY_CASTLE_HEIGHT			(DEFAULT_TILE_SIZE*8)//�摜�c����
#define ENEMY_CASTLE_HITBOX_WIDTH		(ENEMY_CASTLE_WIDTH * 0.8f)//�v���C���[�̃q�b�g�{�b�N�X��
#define ENEMY_CASTLE_HITBOX_HEIGHT	(ENEMY_CASTLE_HEIGHT)//�v���C���[�̃q�b�g�{�b�N�X�c
#define ENEMY_CASTLE_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define ENEMY_CASTLE_HEIGHT_PATTERN		(1)//�c�A�j���p�^�[����
#define ENEMY_CASTLE_FRAME_MAX		((ENEMY_CASTLE_WIDTH_PATTERN * ENEMY_CASTLE_HEIGHT_PATTERN) -1)//�t���[����
#define ENEMY_CASTLE_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define ENEMY_CASTLE_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
//#define TREE_SPEED		(0.0f)//�v���C���[�̈ړ����x
#define ENEMY_CASTLE_INIT_HP		(3000)//�����̗�
#define ENEMY_CASTLE_UNBEATABLE_TEME (80)//���G����



class EnemyCastle :public EntityBase
{
	StateMachine<EnemyCastle>* _EnemyCastleFsm;
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;
	void CollisionHandling();
public:
	EnemyCastle() :EntityBase("EnemyCastle")
	{
		Init();
	}
	EnemyCastle(int TexNo) :EntityBase("EnemyCastle")
	{
		_textureNo = TexNo;
		Init();
	}
	~EnemyCastle()
	{
		UnInit();
		delete _EnemyCastleFsm;
	}

	StateMachine<EnemyCastle>* GetFsm() const { return _EnemyCastleFsm; }

	void Attacked();
	void PositionHandling();
	void GroundDetection();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;


	int _BGM_Clear;
};

