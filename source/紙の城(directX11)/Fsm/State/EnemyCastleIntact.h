/*********************************************************************
 * \file   EnemyCastleIntact.h
 * \brief
 * \author
 * \date   2024 \ 03 \ 03
 *********************************************************************/
#include "..\State.h"
#include "..\..\GameEntity\MapObject\EnemyCastle.h"
 //#include 


class EnemyCastleIntact :public State<EnemyCastle>
{
public:
	static EnemyCastleIntact* Instance()
	{
		static EnemyCastleIntact p;
		return &p;
	}
	void EnterState(EnemyCastle* entity) override;
	void StayState(EnemyCastle* entity) override;
	void ExitState(EnemyCastle* entity) override;
private:
	EnemyCastleIntact() {};
	~EnemyCastleIntact() {};
};



