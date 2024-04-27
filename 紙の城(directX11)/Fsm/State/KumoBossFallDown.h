/*********************************************************************
 * \file   KumoBossFallDown.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossFallDown :public State<KumoBoss>
{
public:
	static KumoBossFallDown* Instance()
	{
		static KumoBossFallDown p;
		return &p;
	}
private:
	KumoBossFallDown() {}
	~KumoBossFallDown() {}


	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};