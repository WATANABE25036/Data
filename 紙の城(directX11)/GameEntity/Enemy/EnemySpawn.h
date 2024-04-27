/*********************************************************************
 * \file   Spawner.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "enemy.h"
#include "..\..\texture.h"
#include "..\..\Fsm\State\Idle.h"

#define ENEMY_MAX			(50)
class Spawner
{
public:
	static Spawner* Instance() 
	{
		static Spawner p;
		return &p;
	}

	void Init()
	{
		int texNo = LoadTexture((char*)"data/TEXTURE/Enemy1.png");
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			_enemy[i] = new Enemy(texNo);
			EntityManager::Instance()->RegisterEntity(_enemy[i]);
		}


	}

	void SetEnemy(Vec2 Pos)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (_enemy[i]->GetUse() != true)
			{
				_enemy[i]->SetPosition(Pos);
				_enemy[i]->SetHp(ENEMY_INIT_HP);
				_enemy[i]->GetFsm()->SetCurrentState(Idle::Instance());
				_enemy[i]->SetUse(true);
				break;
			}
		}
	}

	template<typename T=EntityBase>
	void SetFor(Vec2 Pos)
	{
		EntityBase *entity = new T();
		entity->SetPosition(Pos);
		entity->SetUse(true);
		EntityManager::Instance()->RegisterEntity(entity);
	}

	template<typename T = EntityBase>
	void SetFor(Vec2 Pos, int tex,float time)
	{
		EntityBase* entity = new T(tex);
		entity->SetPosition(Pos);
		entity->SetUse(true);
		entity->SetAttackTime(time);
		EntityManager::Instance()->RegisterEntity(entity);
	}

	template<typename T = EntityBase>
	void SetFor(Vec2 Pos,int tex)
	{
		EntityBase* entity = new T(tex);
		entity->SetPosition(Pos);
		entity->SetUse(true);

		EntityManager::Instance()->RegisterEntity(entity);
	}

	void SetEnemyKnockBack(int index, float power, float radian)
	{
		//ƒ‰ƒWƒAƒ“‚ğ“x‚É•ÏŠ·
		double degrees = radian * 180.0f / 3.14159f;

		//ã‚É‚Ì‚İ’µ‚Ô‚æ‚¤‚É‚·‚é(ã”¼‰~‚ª‰E‚ğ0‹‚Æ‚µ0`-180A‰º”¼‰~‚ª¶‚ğ180‹‚Æ‚µ180`0)
		if (abs(degrees) < 90.0f) degrees = 45;
		if (abs(degrees) > 90.0f) degrees = 135;

		float radianA = degrees * 3.14159f / 180.0f;

		D3DXVECTOR2 vector = CalculateVector(-power, radianA);

		if (_enemy[index]->GetUse())
		{
			_enemy[index]->SetKnockBackX(vector.x);
			_enemy[index]->SetKnockBackY(vector.y);
		}
	}

	//---------------------------------------------------
	// ”½“®‚ğİ’è [ˆø”]index: ”z—ñ”Ô†
	//---------------------------------------------------
	void SetEnemyGunKick(int index, float power, float radian)
	{
		D3DXVECTOR2 vector = CalculateVector(-power, radian);

		if (_enemy[index]->GetUse())
		{
			_enemy[index]->SetKnockBackX(vector.x);
			_enemy[index]->SetKnockBackY(vector.y);
		}
	}

private:
	Enemy* _enemy[ENEMY_MAX];
	Spawner(){}
	~Spawner(){}
};
