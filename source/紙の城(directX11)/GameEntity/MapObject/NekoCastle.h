/*********************************************************************
 * \file   NekoCastle.h
 * \brief
 * \author
 * \date   2024 \ 02 \ 26
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#include "..\..\HpBar.h"
#pragma once
 //---------------------------------------------------
 //�}�N����`
 //---------------------------------------------------
#define CASTLE_MAX			(1)//�L�����N�^�[�̐�
#define CASTLE_WIDTH			(DEFAULT_TILE_SIZE*10)//�摜����
#define CASTLE_HEIGHT			(DEFAULT_TILE_SIZE*8)//�摜�c����
#define CASTLE_HITBOX_WIDTH		(CASTLE_WIDTH * 0.8f)//�v���C���[�̃q�b�g�{�b�N�X��
#define CASTLE_HITBOX_HEIGHT	(CASTLE_HEIGHT)//�v���C���[�̃q�b�g�{�b�N�X�c
#define CASTLE_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define CASTLE_HEIGHT_PATTERN		(1)//�c�A�j���p�^�[����
#define CASTLE_FRAME_MAX		((CASTLE_WIDTH_PATTERN * CASTLE_HEIGHT_PATTERN) -1)//�t���[����
#define CASTLE_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define CASTLE_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
//#define TREE_SPEED		(0.0f)//�v���C���[�̈ړ����x
#define CASTLE_INIT_HP		(30)//�����̗�
#define CASTLE_UNBEATABLE_TEME (80)//���G����



class Castle :public EntityBase
{
	StateMachine<Castle>*	_CastleFsm;
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;
	void CollisionHandling();
public:
	Castle() :EntityBase("Castle")
	{
		Init();
	}
	Castle(int TexNo) :EntityBase("Castle")
	{
		_textureNo = TexNo;
		Init();
	}
	~Castle()
	{
		UnInit();
		delete _CastleFsm;
	}

	StateMachine<Castle>* GetFsm() const { return _CastleFsm; }

	void Attacked();
	void PositionHandling();
	void GroundDetection();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	int _BGM_GameOver;

};

