/*********************************************************************
 * \file   KumoBossIdle.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossIdle :public State<KumoBoss>
{
public:
	static KumoBossIdle* Instance()
	{
		static KumoBossIdle p;
		return &p;
	}
private:
	KumoBossIdle() {}
	~KumoBossIdle() {}


	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};