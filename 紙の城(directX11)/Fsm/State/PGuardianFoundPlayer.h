/*********************************************************************
 * \file   PGuardianFoundPlayer.h
 * \brief
 * \author 
 * \date   2024 \ 02 \ 21
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\Player\paperGuardian.h"

class PGuardianFoundPlayer :public State<PaperGuardian>
{
public:
	static PGuardianFoundPlayer* Instance()
	{
		static PGuardianFoundPlayer p;
		return &p;
	}
	void EnterState(PaperGuardian* entity) override;
	void StayState(PaperGuardian* entity) override;
	void ExitState(PaperGuardian* entity) override;
private:
	PGuardianFoundPlayer() {}
	~PGuardianFoundPlayer() {}
};

