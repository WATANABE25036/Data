/*********************************************************************
 * \file   Alpaca.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024/03/04
 *********************************************************************/
#pragma once
#define ALPACA_MAX			(50)//�L�����N�^�[�̐�
#define ALPACA_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�摜����
#define ALPACA_HEIGHT		(DEFAULT_TILE_SIZE * 0.5f)//�摜�c����
#define ALPACA_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//�G�l�~�[�̃q�b�g�{�b�N�X��
#define ALPACA_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.5f)//�G�l�~�[�̃q�b�g�{�b�N�X�c
#define ALPACA_WIDTH_PATTERN	(2)//���A�j���p�^�[����
#define ALPACA_HEIGHT_PATTERN	(4)//�c�A�j���p�^�[����
#define ALPACA_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//�t���[����
#define ALPACA_FRAME_SPAN	(8)//�A�j���[�V�����̃X�p��
#define ALPACA_FOLLOW_SPAN	(5)//�L�����N�^�[�Ԃ̊Ԋu�i�t���[���j
#define ALPACA_SPEED		(4.0f)//�G�l�~�[�̈ړ����x
#define ALPACA_UNBEATABLE_TEME (20)//���G����


#include "GameEntity/EntityBase.h"
#include <vector>
class Alpaca:public EntityBase
{
public:
	Alpaca():EntityBase("Alpaca"),_buffSize(50), _head(0), _tail(0),_full(false)
	{
		Init();
	}

	~Alpaca(){}

	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;
private:
	int							_buffSize;
	int							_head;
	int							_tail;
	bool						_full;
	std::vector<D3DXVECTOR2>	_posBuffer;
	void Push(const D3DXVECTOR2& pos);
	D3DXVECTOR2& GetPos(size_t offset);
};
