/*********************************************************************
 * \file   EnemyCastleFallen.h
 * \brief
 * \author
 * \date   2024 \ 03 \ 03
 *********************************************************************/
#include "..\State.h"
 #include "..\..\GameEntity\MapObject\EnemyCastle.h"


class EnemyCastleFallen :public State<EnemyCastle>
{
public:
	static EnemyCastleFallen* Instance()
	{
		static EnemyCastleFallen p;
		return &p;
	}
	void EnterState(EnemyCastle* entity) override;
	void StayState(EnemyCastle* entity) override;
	void ExitState(EnemyCastle* entity) override;
private:
	EnemyCastleFallen() {};
	~EnemyCastleFallen() {};
};



