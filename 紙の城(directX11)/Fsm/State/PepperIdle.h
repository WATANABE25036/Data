/*********************************************************************
 * \file   PepperIdle.h
 * \brief   
 * \author •ﬁ°°•≥•¶•ÅEÂ•¶
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\Enemy\PepperEnemy.h"

class PepperIdel:public State<PepperEnemy>
{
public:
	static PepperIdel* Instance()
	{
		static PepperIdel p;
		return &p;
	}
	void EnterState(PepperEnemy* entity) override;
	void StayState(PepperEnemy* entity) override;
	void ExitState(PepperEnemy* entity) override;
private:
	PepperIdel() {};
	~PepperIdel() {};
};

