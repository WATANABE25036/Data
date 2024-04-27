/*********************************************************************
 * \file   KumoBossBackAttacked.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossBackAttacked :public State<KumoBoss>
{
public:
	static KumoBossBackAttacked* Instance()
	{
		static KumoBossBackAttacked p;
		return &p;
	}
private:
	KumoBossBackAttacked() {}
	~KumoBossBackAttacked() {}


	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};