/*********************************************************************
 * \file   Tree.h
 * \brief
 *
 * \author 
 * \date   2024 \  02 \ 07
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "..\..\renderer.h"
#include "..\EntityBase.h"
//#include "EnemybulletSpawn.h"
#include "..\..\Fsm\StateMachine.h"
#include <string>



 //---------------------------------------------------
 //�}�N����`
 //---------------------------------------------------
#define TREE_MAX			(2)//�L�����N�^�[�̐�
#define TREE_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�摜����
#define TREE_HEIGHT		(DEFAULT_TILE_SIZE)//�摜�c����
#define TREE_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�G�l�~�[�̃q�b�g�{�b�N�X��
#define TREE_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE)//�G�l�~�[�̃q�b�g�{�b�N�X�c
#define TREE_WIDTH_PATTERN	(1)//���A�j���p�^�[����
#define TREE_HEIGHT_PATTERN	(2)//�c�A�j���p�^�[����
#define TREE_FRAME_MAX	((TREE_WIDTH_PATTERN * TREE_HEIGHT_PATTERN) -1)//�t���[����
#define TREE_FRAME_SPAN	(2)//�A�j���[�V�����̃X�p��
#define TREE_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j

#define TREE_UNBEATABLE_TEME (20)//���G����


//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
class Tree :public EntityBase
{
public:
		//EnemyBulletSpawn::Instance()->SetBullet(_pos, targetPos, 150, 1.0f);
		//TreeBulletSpawn::Instance()->SetBullet(_pos, targetPos, 150, 1.0f);
	}
	//const bool GetJump()const { return _jump; }

	Tree(int TexNo) :EntityBase("Tree")
	{
		_textureNo = TexNo;
		Init();
	};
	~Tree() override
	{
		UnInit();
	}
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
};

