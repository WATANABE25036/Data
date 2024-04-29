/*********************************************************************
 * \file   paperGuardian.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 21
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>
#pragma once
 //---------------------------------------------------
 //�}�N����`
 //---------------------------------------------------
#define PGUARDIAN_MAX			(1)//�L�����N�^�[�̐�
#define PGUARDIAN_WIDTH		(DEFAULT_TILE_SIZE*0.6)//�摜����
#define PGUARDIAN_HEIGHT		(DEFAULT_TILE_SIZE*0.6)//�摜�c����
#define PGUARDIAN_HITBOX_WIDTH		(PGUARDIAN_WIDTH * 0.5f)//�v���C���[�̃q�b�g�{�b�N�X��
#define PGUARDIAN_HITBOX_HEIGHT	(PGUARDIAN_HEIGHT)//�v���C���[�̃q�b�g�{�b�N�X�c
#define PGUARDIAN_WIDTH_PATTERN	(7)//���A�j���p�^�[����
#define PGUARDIAN_HEIGHT_PATTERN	(2)//�c�A�j���p�^�[����
#define PGUARDIAN_FRAME_MAX	((PGUARDIAN_WIDTH_PATTERN * PGUARDIAN_HEIGHT_PATTERN) -1)//�t���[����
#define PGUARDIAN_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define PGUARDIAN_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define PGUARDIAN_SPEED		(8.0f)//�v���C���[�̈ړ����x
#define PGUARDIAN_INIT_HP		(3)//�����̗�
#define PGUARDIAN_UNBEATABLE_TIME (80)//���G����





class PaperGuardian :public EntityBase
{
	StateMachine<PaperGuardian>* _paperGuardianFsm;
	void CollisionHandling();

public:
	PaperGuardian(int TexNo) :EntityBase("PaperGuardian")
	{
		_textureNo = TexNo;
		Init();
	}
	~PaperGuardian()
	{
		UnInit();
		delete _paperGuardianFsm;
	}

	//int texPaperGuardian = LoadTexture((char*)"data/TEXTURE/paperGuardian.png");
	StateMachine<PaperGuardian>* GetFsm() const { return _paperGuardianFsm; }


	Vec2 offset;
	void Attacked();
	void PositionHandling();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

