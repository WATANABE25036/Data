/*********************************************************************
 * \file   EnemybulletSpawn.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\..\main.h"
#include "SpiderBullet.h"
#include "..\EntityManager.h"
#include "..\..\texture.h"
#define	EBULLET				EnemyBulletSpawn::Instance()
#define BULLET_MAX			(50)

class EnemyBulletSpawn
{
public:
	static EnemyBulletSpawn* Instance()
	{	
		static EnemyBulletSpawn p;
		return &p;
	}

	//------------------------------------------
	//[in]startPoint : スタート位置座標       
	//[in]targetPoint : ターゲット位置の座標
	//[in]high : 最大高さ
	//[in]time : 飛行速度（時間）
	//-----------------------------------------
	void SetBullet(D3DXVECTOR2 startPoint,D3DXVECTOR2 targetPoint,int high=200,float time=2.0f);
	void Init()
	{
		int texNo = LoadTexture((char*)"data/TEXTURE/Bullet.png");
		for (int i = 0; i < BULLET_MAX; i++)
		{
			SBullet[i] = new SpiderBullet(texNo);
			EntityManager::Instance()->RegisterEntity(SBullet[i]);
		}
	}
	SpiderBullet* SBullet[BULLET_MAX];
private:
	EnemyBulletSpawn() {; }
	~EnemyBulletSpawn() { ; }
};
