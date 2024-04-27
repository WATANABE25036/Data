/*********************************************************************
 * \file   KumoBossAttacked.h
<<<<<<< HEAD
 * \brief   
 * \author �ޡ�������E�?
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

class KumoBossAttacked :public State<KumoBoss>
{
public:
	static KumoBossAttacked* Instance()
	{
		static KumoBossAttacked p;
		return &p;
	}
private:
	KumoBossAttacked() {}
	~KumoBossAttacked() {}


	// ͨ�� State �̳�
	void EnterState(KumoBoss* entity) override;

	void StayState(KumoBoss* entity) override;

	void ExitState(KumoBoss* entity) override;

};