/*********************************************************************
 * \file   FoundPlayer.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\enemy.h"
class FoundPlayer:public State<Enemy>
{
	FoundPlayer() { ; }
	~FoundPlayer() { ; }
public:
	
	static FoundPlayer* Instance()
	{
		static FoundPlayer p;
		return &p;
	}
	// ͨ�� State �̳�
	void EnterState(Enemy* entity) override;
	void StayState(Enemy* entity) override;
	void ExitState(Enemy* entity) override;
};
