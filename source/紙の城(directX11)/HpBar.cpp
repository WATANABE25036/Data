/*********************************************************************
 * \file   hpBar.h
 * \brief
 *
 * \author
 * \date   2024 \  02 \ 02
 *********************************************************************/
#include "HpBar.h"
#include "sprite.h"
#include "camera.h"

void HpBar::Update()
{
	_startPoint = _entity->GetPosition() + _barInfo.offset;
}

void HpBar::Draw()
{
	float hpPercentage = _entity->GetHp()/_entity->GetMaxHp();
	if (hpPercentage<=0)
	{
		hpPercentage = 0;
	}
	DrawSpriteLeftTopCamera(_barInfo.hpBarFrameTexNo, _startPoint.x, _startPoint.y, _barInfo.size.x, _barInfo.size.y, 0, 0, 1, 1);
	if (hpPercentage >= 1.0f)
	{
		DrawSpriteLeftTopCamera(_barInfo.fullHpTexNo, _startPoint.x, _startPoint.y, _barInfo.size.x * hpPercentage, _barInfo.size.y, 0, 0, 1, 1);
	}
	else
	{
		DrawSpriteLeftTopCamera(_barInfo.notFullHpTexNo, _startPoint.x, _startPoint.y, _barInfo.size.x * hpPercentage, _barInfo.size.y, 0, 0, 1, 1);
	}
}

void HpBar::PlayerDraw()
{
	float hpPercentage = _entity->GetHp() / _entity->GetMaxHp();
	if (hpPercentage <= 0)
	{
		hpPercentage = 0;
	}
	DrawSpriteLeftTop(_barInfo.hpBarFrameTexNo, 400 - _barInfo.size.x * 0.5f, 50.0f, _barInfo.size.x, _barInfo.size.y, 0, 0, 1, 1);
	if (hpPercentage >= 1.0f)
	{
		DrawSpriteLeftTop(_barInfo.fullHpTexNo, 400 - _barInfo.size.x * 0.5f, 50.0f, _barInfo.size.x * hpPercentage, _barInfo.size.y, 0, 0, 1, 1);
	}
	else
	{
		DrawSpriteLeftTop(_barInfo.notFullHpTexNo, 400 - _barInfo.size.x * 0.5f, 50.0f, _barInfo.size.x * hpPercentage, _barInfo.size.y, 0, 0, 1, 1);
	}
}

void HpBar::BossDraw()
{
	float hpPercentage = _entity->GetHp() / _entity->GetMaxHp();
	if (hpPercentage <= 0)
	{
		hpPercentage = 0;
	}
	DrawSpriteLeftTop(_barInfo.hpBarFrameTexNo, SCREEN_WIDTH * 0.5f - _barInfo.size.x * 0.5f, SCREEN_HEIGHT * 0.9f, _barInfo.size.x, _barInfo.size.y, 0, 0, 1, 1);
	if (hpPercentage >= 1.0f)
	{
		DrawSpriteLeftTop(_barInfo.fullHpTexNo, SCREEN_WIDTH * 0.5f - _barInfo.size.x * 0.5f, SCREEN_HEIGHT * 0.9f, _barInfo.size.x * hpPercentage, _barInfo.size.y, 0, 0, 1, 1);
	}
	else
	{
		DrawSpriteLeftTop(_barInfo.notFullHpTexNo, SCREEN_WIDTH * 0.5f - _barInfo.size.x * 0.5f, SCREEN_HEIGHT * 0.9f, _barInfo.size.x * hpPercentage, _barInfo.size.y, 0, 0, 1, 1);
	}
}