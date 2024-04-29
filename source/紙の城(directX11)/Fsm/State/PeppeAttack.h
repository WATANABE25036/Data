/*********************************************************************
 * \file   PeppeAttack.h
 * \brief   
 * \author �ޡ�������E�?
 * \date   2024 \ 02 \ 08
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\Enemy\PepperEnemy.h"
class PepperAttack :public State<PepperEnemy>
{
public:
	static PepperAttack* Instance()
	{
		static PepperAttack p;
		return &p;
	}
	void EnterState(PepperEnemy* entity) override;
	void StayState(PepperEnemy* entity) override;
	void ExitState(PepperEnemy* entity) override;
private:
	PepperAttack() {}
	~PepperAttack() {}

};
