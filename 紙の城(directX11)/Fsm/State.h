/*********************************************************************
 * \file   State.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#ifndef STATE_H_
#define STATE_H_
template<class GameEntity>
class State
{
public:
	virtual ~State() { ; }								
	virtual void EnterState(GameEntity* entity) = 0;
	virtual void StayState(GameEntity* entity) = 0;
	virtual void ExitState(GameEntity* entity) = 0;
};
#endif // !STATE_H