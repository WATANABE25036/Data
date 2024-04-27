/*********************************************************************
 * \file   player.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "..\..\renderer.h"
#include "..\..\Fsm\StateMachine.h"
#include "..\EntityBase.h"
#include "..\..\camera.h"
#include "..\..\hit_spark.h"
#include "..\..\particle.h"
#include "..\..\sound.h"

#include "..\..\HpBar.h"


//---------------------------------------------------
//�}�N����`
//---------------------------------------------------
#define PLAYER_MAX			(1)//�L�����N�^�[�̐�
#define PLAYER_WIDTH		(660 * 0.8f)//�摜����
#define PLAYER_HEIGHT		(473 * 0.8f)//�摜�c����
#define PLAYER_HITBOX_WIDTH		(PLAYER_WIDTH * 0.1f)//�v���C���[�̃q�b�g�{�b�N�X��
#define PLAYER_HITBOX_HEIGHT	(PLAYER_HEIGHT - 65*2)//�v���C���[�̃q�b�g�{�b�N�X�c
#define PLAYER_WIDTH_PATTERN	(9.0f)//���A�j���p�^�[����
#define PLAYER_HEIGHT_PATTERN	(32.0f)//�c�A�j���p�^�[����
#define PLAYER_FRAME_MAX	((PLAYER_WIDTH_PATTERN * PLAYER_HEIGHT_PATTERN) -1)//�t���[����
#define PLAYER_FRAME_SPAN	(2)//�A�j���[�V�����̃X�p��
#define PLAYER_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define PLAYER_SPEED		(4.0f)//�v���C���[�̈ړ����x
#define PLAYER_DASH_SPEED	(14.0f)//Shift�������đ������Ƃ��̑���
#define PLAYER_INIT_HP		(5)//�����̗�
#define PLAYER_UNBEATABLE_TEME (80)//���G����


//---------------------------------------------------
//�\���̐錾
//---------------------------------------------------
class Player :public EntityBase
{
public:
	Player() :EntityBase("Player") 
	{
		Init();
		
	}
	~Player() override 
	{ 
		UnInit();
		delete _playerFsm;
	}
	

	bool _animeLoop;
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	void Reset();
	void Jump(bool keyJump);
	void TripleJump(bool Jumpkey);
	void Attacked();
	void PositionHandling();
	StateMachine<Player>* GetFsm()const { return _playerFsm; }
	HpBarInfo				_hpBarInfo;
	HpBar					_hpBar;

	HitBox _attackBox;

	bool GetMoveRKey() const;
	bool GetMoveLKey() const;
	bool GetDashKey() const;
	bool GetAttackKey() const;
	bool GetJumpKey() const;
	bool GetSpecialKey() const;
	bool GetDownKey() const;

	bool GetReleaseAttackKey() const { return _releaseAttackKey; }
	void SetReleaseAttackKey(bool judge) { _releaseAttackKey = judge; }

	//��
	int _SE_move1;
	int _SE_move2;
	int _SE_damage;
	int _SE_playerDown;
	int _SE_attack1;
	int _SE_attack2;
	int _SE_attack3;
	int _SE_attack4;
	int _SE_itemGet;
	int _SE_landing;
	int _SE_jump;
	int _SE_attack5;
	int _SE_swing;
	int _BGM_GameOver;

private:
	void GroundDetection();
	void CollisionHandling();
	StateMachine<Player>* _playerFsm;

	//���͊֌W
	bool _moveLKey;
	bool _moveRKey;
	bool _dashKey;
	bool _attackKey;
	bool _jumpKey;
	bool _specialKey;
	bool _downKey;

	//�U���{�^���𗣂���������
	bool _releaseAttackKey;
};

void SetPlayerGunKick(float power, float radian);
void SetPlayerKnockBack(float power, float radian);
void SetPlayer(float posX, float posY);
void SetPlayerScore(int add);
