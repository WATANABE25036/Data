/*********************************************************************
 * \file   KumoBossWeaponAttack.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/


#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossWeaponAttack :public State<KumoBoss>
{
public:
	static KumoBossWeaponAttack* Instance()
	{
		static KumoBossWeaponAttack p;
		return &p;
	}
private:
	KumoBossWeaponAttack() {}
	~KumoBossWeaponAttack() {}


	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};
