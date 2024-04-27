/*********************************************************************
 * \file   KumoBossGetUp.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossGetUp :public State<KumoBoss>
{
public:
	static KumoBossGetUp* Instance()
	{
		static KumoBossGetUp p;
		return &p;
	}
private:
	KumoBossGetUp() {}
	~KumoBossGetUp() {}

	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};