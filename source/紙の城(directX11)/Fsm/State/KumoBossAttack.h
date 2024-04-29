/*********************************************************************
 * \file   KumoBossAttack.h
<<<<<<< HEAD
 * \brief   
 * \author ¥Þ¡¡¥³¥¦¥Eå¥?
 * \date   2024 \ 01 \ 20
=======
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  02 \ 07 
>>>>>>> origin/player-and-enemy
 *********************************************************************/
#pragma once
#include"..\State.h"
#include"..\..\GameEntity\Enemy\KumoBoss.h"

class KumoBossAttack :public State<KumoBoss>
{
public:
	static KumoBossAttack* Instance()
	{
		static KumoBossAttack p;
		return &p;
	}
private:
	KumoBossAttack() {}
	~KumoBossAttack() {}


	// Í¨¹ý State ¼Ì³Ð
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};
