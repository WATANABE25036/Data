#include "Alpaca.h"
#include "GameEntity/Player/player.h"
#include "GameEntity/EntityManager.h"
#include "texture.h"
#include "sprite.h"

static bool idle = true;
void Alpaca::Init()
{
	auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
	_posBuffer.resize(_buffSize);
	_pos = (player->GetPosition() + Vec2{0,25});
	_U = 0;
	_V = 0;
	_UW = 1.0/2.0f;
	_VH = 1.0f/4.0f;
	_size = {200,200};
	_textureNo = LoadTexture((char*)"data/TEXTURE/PlayerA.png");
	_animeBasePattern = 0;
	_animePattern = 0;
	_animeSkipFrame=0;
	_animeFrameMax = 2;
	_use = true;
}

void Alpaca::Update()
{
	

    auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
    Push(player->GetPosition());

    if (_full)
    {
        Vec2 pos = GetPos(45);
        _pos = (pos + Vec2{ 0,25 });

    }
  
	if (player->GetPosition().x >= _pos.x)
	{
		_reverse = false;
	}
	else
	{
		_reverse = true;
	}

	if (_pos != oldPos)
	{
		idle = false;
	}
	else
	{
		idle = true;
	}

	oldPos = _pos;
}

void Alpaca::Draw()
{
	SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//テクスチャのフィルターをOFF
	if (_use)
	{

		if (idle)
		{
			_animeBasePattern = 0;
			_animePattern = 0;
			D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, ALPACA_WIDTH_PATTERN, ALPACA_HEIGHT_PATTERN, ALPACA_WIDTH_PATTERN, _reverse);

			_U = uv.x;
			_V = uv.y;

		
			DrawSpriteColorRotateCamera(_textureNo,
				(int)_pos.x,
				(int)_pos.y,
				_size.x, _size.y,	//幅、高さ
				_U, _V,		//中心UV座標
				0.5, 0.25,		//テクスチャ幅、高さ
				1, 1, 1, 1,
				0.0f
			);
		}
		else
		{
			_animeBasePattern = 6;
			D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, ALPACA_WIDTH_PATTERN, ALPACA_HEIGHT_PATTERN, ALPACA_WIDTH_PATTERN, _reverse);

			_U = uv.x;
			_V = uv.y;

			_animeSkipFrame = Counter(_animeSkipFrame, ALPACA_FRAME_SPAN);
			if (_animeSkipFrame == 0)
			{
				_animePattern = Counter(_animePattern, _animeFrameMax);
			}

			DrawSpriteColorRotateCamera(_textureNo,
				(int)_pos.x,
				(int)_pos.y,
				_size.x, _size.y,	//幅、高さ
				_U, _V,		//中心UV座標
				0.5, 0.25,		//テクスチャ幅、高さ
				1, 1, 1, 1,
				0.0f
			);
		}
	}

}

void Alpaca::UnInit()
{
}

void Alpaca::Push(const D3DXVECTOR2& pos)
{
    _posBuffer[_head] = pos;
    _head = (_head + 1) % _buffSize;
    _full = _head == _tail;
    if (_full)
    {
        _tail = (_tail + 1) % _buffSize;
    }
}

D3DXVECTOR2& Alpaca::GetPos(size_t offset)
{
    if (_full)
    {
        size_t index = (_head + _buffSize - offset - 1) % _buffSize;
        return _posBuffer[index];
    }
}
