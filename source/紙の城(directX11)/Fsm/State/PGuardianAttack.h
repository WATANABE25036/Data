/*********************************************************************
 * \file   PGuardianAttack.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 25
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\Enemy\PepperEnemy.h"
#include "..\..\GameEntity\Player\paperGuardian.h"

class PGuardianAttack :public State<PaperGuardian>
{
public:
	static PGuardianAttack* Instance()
	{
		static PGuardianAttack p;
		return &p;
	}
	void EnterState(PaperGuardian* entity) override;
	void StayState(PaperGuardian* entity) override;
	void ExitState(PaperGuardian* entity) override;
private:
	PGuardianAttack() {}
	~PGuardianAttack() {}

};
