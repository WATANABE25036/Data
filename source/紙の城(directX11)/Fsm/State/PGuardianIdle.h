/*********************************************************************
 * \file   PGuardianIdle.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 21
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\Player\paperGuardian.h"

class PGuardianIdle :public State<PaperGuardian>
{
public:
	static PGuardianIdle* Instance()
	{
		static PGuardianIdle p;
		return &p;
	}
	void EnterState(PaperGuardian* entity) override;
	void StayState(PaperGuardian* entity) override;
	void ExitState(PaperGuardian* entity) override;
private:
	PGuardianIdle() {};
	~PGuardianIdle() {};
};

