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
//ƒ}ƒNƒ’è‹`
//---------------------------------------------------
#define ENEMY_MAX			(50)//ƒLƒƒƒ‰ƒNƒ^[‚Ì”
#define ENEMY_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//‰æ‘œ‰¡•
#define ENEMY_HEIGHT		(DEFAULT_TILE_SIZE * 0.5f)//‰æ‘œc‚‚³
#define ENEMY_HITBOX_WIDTH		(DEFAULT_TILE_SIZE * 0.5f)//ƒGƒlƒ~[‚Ìƒqƒbƒgƒ{ƒbƒNƒX‰¡
#define ENEMY_HITBOX_HEIGHT	(DEFAULT_TILE_SIZE * 0.5f)//ƒGƒlƒ~[‚Ìƒqƒbƒgƒ{ƒbƒNƒXc
#define ENEMY_WIDTH_PATTERN	(4)//‰¡ƒAƒjƒƒpƒ^[ƒ“”
#define ENEMY_HEIGHT_PATTERN	(5)//cƒAƒjƒƒpƒ^[ƒ“”
#define ENEMY_FRAME_MAX	((ENEMY_WIDTH_PATTERN * ENEMY_HEIGHT_PATTERN) -1)//ƒtƒŒ[ƒ€”
#define ENEMY_FRAME_SPAN	(8)//ƒAƒjƒ[ƒVƒ‡ƒ“‚ÌƒXƒpƒ“
#define ENEMY_FOLLOW_SPAN	(5)//ƒLƒƒƒ‰ƒNƒ^[ŠÔ‚ÌŠÔŠuiƒtƒŒ[ƒ€j
#define ENEMY_SPEED		(4.0f)//ƒGƒlƒ~[‚ÌˆÚ“®‘¬“x
#define ENEMY_UNBEATABLE_TEME (20)//–³“GŠÔ
#define ENEMY_INIT_HP (1)


//---------------------------------------------------
//\‘¢‘ÌéŒ¾
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
	// Í¨¹ı EntityBase ¼Ì³Ğ
	void Init() override;
	void Update() override;
	void Draw() override;
	void UnInit() override;

	//‰¹
	int _SE_hit;
	int _SE_enemyDown;
	int g_shotTime;
};

