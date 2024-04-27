/*********************************************************************
 * \file   Tree.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 16
 *********************************************************************/
#include "..\EntityBase.h"
#include "..\..\Fsm\StateMachine.h"
#include "../../texture.h"
#include <string>
#pragma once
 //---------------------------------------------------
 //�}�N����`
 //---------------------------------------------------
#define TREE_MAX			(1)//�L�����N�^�[�̐�
#define TREE_WIDTH			(500 * 5)//�摜����
#define TREE_HEIGHT		(300 * 5)//�摜�c����
#define TREE_HITBOX_WIDTH		(TREE_WIDTH * 0.1f)//�v���C���[�̃q�b�g�{�b�N�X��
#define TREE_HITBOX_HEIGHT		(TREE_HEIGHT - 1)//�v���C���[�̃q�b�g�{�b�N�X�c(�Ȃ�1�s�N�Z�������̂�-1)
#define TREE_WIDTH_PATTERN		(4)//���A�j���p�^�[����
#define TREE_HEIGHT_PATTERN		(5)//�c�A�j���p�^�[����
#define TREE_FRAME_MAX		((TREE_WIDTH_PATTERN * TREE_HEIGHT_PATTERN) -1)//�t���[����
#define TREE_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define TREE_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
//#define TREE_SPEED		(0.0f)//�v���C���[�̈ړ����x
#define TREE_INIT_HP		(5)//�����̗�
#define TREE_UNBEATABLE_TEME (80)//���G����



class Tree :public EntityBase
{
	StateMachine<Tree>* _TreeFsm;
	void CollisionHandling();
public:
	Tree(int TexNo) :EntityBase("Tree")
	{
		_textureNo = TexNo;
		texPaperGuardian = LoadTexture((char*)"data/TEXTURE/paperGuardian.png");
		texPepper = LoadTexture((char*)"data/TEXTURE/paperenemy.png");
		Init();
	}
	~Tree()
	{
		UnInit();
		delete _TreeFsm;
	}

	StateMachine<Tree>* GetFsm() const { return _TreeFsm; }

	int texPaperGuardian ;
	int texPepper;
	void Attacked();
	void PositionHandling();
	void GroundDetection();
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

