/*********************************************************************
 * \file   KumoBossJumpAttack.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossJumpAttack :public State<KumoBoss>
{
public:
	static KumoBossJumpAttack* Instance()
	{
		static KumoBossJumpAttack p;
		return &p;
	}
private:
	KumoBossJumpAttack() {}
	~KumoBossJumpAttack() {}


	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};
