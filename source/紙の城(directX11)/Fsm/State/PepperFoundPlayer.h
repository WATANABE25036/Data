/*********************************************************************
 * \file   PepperFoundPlayer.h
 * \brief   
 * \author •ﬁ°°•≥•¶•ÅEÂ•¶
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\Enemy\PepperEnemy.h"
class PepperFoundPlayer :public State<PepperEnemy>
{
public:
	static PepperFoundPlayer* Instance()
	{
		static PepperFoundPlayer p;
		return &p;
	}
	void EnterState(PepperEnemy* entity) override;
	void StayState(PepperEnemy* entity) override;
	void ExitState(PepperEnemy* entity) override;
private:
	PepperFoundPlayer() {}
	~PepperFoundPlayer() {}
};
