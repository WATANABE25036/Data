/*********************************************************************
 * \file   hpBar.h
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 02
 *********************************************************************/
#pragma once
#include "GameEntity/EntityBase.h"
#include "texture.h"
struct HpBarInfo
{
	int    fullHpTexNo;
	int    notFullHpTexNo;
	int    hpBarFrameTexNo;
	Vec2   offset;
	Vec2   size;
};


class HpBar
{
public:
	~HpBar() {}

	void Update();
	void Draw();
	void PlayerDraw();
	void BossDraw();
	void SetTarget(EntityBase* entity) { _entity = entity; }
	void SetHpBarInfo(const HpBarInfo& barinfo) { _barInfo = barinfo; }
private:
	EntityBase* _entity;
	HpBarInfo   _barInfo;
	Vec2		_startPoint;
public:

	HpBar() = default;
};

