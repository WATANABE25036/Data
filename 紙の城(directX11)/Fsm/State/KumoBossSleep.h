/*********************************************************************
 * \file   KumoBossSleep.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossSleep :public State<KumoBoss>
{
public:
	static KumoBossSleep* Instance()
	{
		static KumoBossSleep p;
		return &p;
	}
private:
	KumoBossSleep() {}
	~KumoBossSleep() {}

	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};