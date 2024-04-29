/*********************************************************************
 * \file   SpiderBullet.cpp
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#include "SpiderBullet.h"

#include "..\..\sprite.h"
#include "..\..\texture.h"

static int g_HitTexNo;



void SpiderBullet::Init()
{
	g_HitTexNo = LoadTexture((char*)"data/TEXTURE/Trigger.png");


	_vel = D3DXVECTOR2(0, 0);
	_size = D3DXVECTOR2(40, 40);
	_pos = D3DXVECTOR2(0, 0);
	_use= false;
	_animePattern = 0;
	_animeWidthPattern = 2;
	_animeBasePattern = 1;
	_animeSkipFrame = 0;
	//_rot =0.0f;
	_reverse = false;
	_a = _b = _c = 0;
	_color.r = _color.g = _color.b = _color.a = 1;


	_attackBox._use = false;
	_attackBox._pos = { _pos.x,_pos.y };
	_attackBox._size = Vec2(30, 30);


}

void SpiderBullet::Update()
{
	if (_use)
	{
		_pos += _vel;
		_pos.y = _a * pow(_pos.x, 2) + _b * _pos.x + _c;

		if (_attackBox._use == true)
		{
			_attackBox._pos = { _pos.x - 0,_pos.y - 10 };
		}

		if (_vel.x > 0)
		{
			_reverse = false;
		}
		else
		{
			_reverse = true;
		}
	}
}

void SpiderBullet::Draw()
{

	if (_use)
	{
		D3DXVECTOR2 _uv = SetAnimation(_animeBasePattern, _animePattern, 2, 1, _animeWidthPattern, _reverse);
		_animeSkipFrame = Counter(_animeSkipFrame, 2);

		if (_animeSkipFrame == 0)
		{
			_animePattern = Counter(_animePattern, 2);
			if (_animePattern == 0)
				_animeWidthPattern = 1;//アニメをループさせない
		}

		DrawSpriteColorRotateCamera(_textureNo,
			_pos.x,
			_pos.y,
			_size.x, _size.y,	//幅、高さ
			_uv.x, _uv.y,		//中心UV座標
			1.0f / 2, 1.0f,		//テクスチャ幅、高さ
			_color.r, _color.g, _color.b, _color.a,
			0.0f);

#ifdef _DEBUG
		/*if (_hitBox._use == true)
		{
			DrawSpriteColorRotateCamera(g_HitTexNo,
				(int)_hitBox._pos.x,
				(int)_hitBox._pos.y,
				_hitBox._size.x, _hitBox._size.y,	//幅、高さ
				0.5, 0.5,		//中心UV座標
				1, 1,		//テクスチャ幅、高さ
				1, 0.2, 0.2, 0.5f,
				0
			);
		}*/

		if (_attackBox._use == true)
		{
			DrawSpriteColorRotateCamera(g_HitTexNo,
				(int)_attackBox._pos.x,
				(int)_attackBox._pos.y,
				_attackBox._size.x, _attackBox._size.y,
				0.5, 0.5,		//中心UV座標
				1, 1,		//テクスチャ幅、高さ
				0, 0.2f, 0.2f, 0.5f,
				0
			);
		}
#endif


	}
}

void SpiderBullet::UnInit()
{
}

