/*********************************************************************
 * \file   SpiderBullet.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "EnemyBullet.h"
#include "string"

class SpiderBullet:public EntityBase
{

	//StateMachine<SpiderBullet>* _spiderBulletFsm;
	void CollisionHandling();

public:
	SpiderBullet(int texNo) :EntityBase("Bullet") 
	{ 
		_textureNo = texNo;
		Init();
	}

	~SpiderBullet() { 

		UnInit();
		//delete _spiderBulletFsm;
	}
	float _a=0, _b=0, _c = 0;



	void Init()override;
	void Update()override;
	void Draw()override;
	void UnInit()override;
};
