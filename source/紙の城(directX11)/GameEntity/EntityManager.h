/*********************************************************************
 * \file   EntityManager.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include <list>
#include "EntityBase.h"
#include <vector>

class EntityManager
{
public:

	static EntityManager* Instance()
	{
		static EntityManager p;
		return &p;
	}

	void RegisterEntity(EntityBase* p)
	{
		_entityList.emplace_back(p);
	}
	
	void CleanAll()
	{
		for (auto x : _entityList)
		{
			delete x;
		}
		_entityList.clear();
	}

	void Update()
	{
		for (auto x : _entityList)
		{
			x->Update();
		}
	}
	void Draw()
	{
		for (auto it = _entityList.begin(); it != _entityList.end(); ++it)
		{
			if ((*it)->GetTag() == "Player")
			{
				_entityList.splice(_entityList.end(), _entityList, it);
				break;
			}
		}

		for (auto x : _entityList)
		{
			x->Draw();
		}
	}

	template<typename T = EntityBase>
	std::vector<T*> GetEntitysWithTag(const std::string& tag)
	{
		std::vector<T*> return_entity;

		for (auto x : _entityList)
		{
			if (x->GetTag() != tag) continue;

			if (T* t = dynamic_cast<T*>(x))
			{
				return_entity.push_back(t);
			}
		}
		return return_entity;
	}

	template<typename T = EntityBase>
	T* GetEntityWithTag(const std::string & tag)
	{
		for (auto x : _entityList)
		{
			if (x->GetTag() != tag) continue;

			if (T* t = dynamic_cast<T*>(x))
			{
				return t;
			}
		}
	}
private:
	std::list<EntityBase*> _entityList;
	EntityManager() {}
	~EntityManager() {}
};
