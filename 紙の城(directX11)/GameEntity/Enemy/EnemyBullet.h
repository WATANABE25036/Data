/*********************************************************************
 * \file   EnemyBullet.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include"..\..\main.h"
#include"..\EntityBase.h"
class EnemyBullet:public EntityBase
{
public:
	EnemyBullet() = default;
	EnemyBullet(const std::string& tag, const int texNo) :EntityBase(tag,texNo) {}
	~EnemyBullet()override{ ; }

protected:
	Vec2					_uv;				
	float					_rot;
};
