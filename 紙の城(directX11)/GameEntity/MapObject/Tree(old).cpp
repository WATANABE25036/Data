/*********************************************************************
 * \file   Tree.cpp
 * \brief
 * \author マ　コウリュウ
 * \date   2024 \ 02 \ 07
 *********************************************************************/
#include "..\..\GameEntity\Enemy\enemy.h"
#include "..\..\texture.h"
#include "..\..\sprite.h"
#include "..\..\input.h"
#include "..\..\sound.h"
#include "..\..\collision.h"
#include "..\..\dead.h"
//#include "..\..\main.h"
#include "..\..\tile.h"
#include "..\..\bullet.h"
#include "..\..\GameEntity\Player\player.h"
#include "..\..\particle.h"

#include "Tree.h"





void Tree::Init()
{
	_use = true;
	_pos.x = 1500;
	_pos.y = SCREEN_HEIGHT / 4;
	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_hsp = 0;
	_vsp = 0;
	_grv = 0.3f;
	_walksp = 0.0f;
	_controller = true;
	_hascontrol = false;
	_canjump = false;
	_knockBackX = 0;
	_knockBackY = 0;
	_ground = false;
	_animeWidthPattern = 1;
	_animeHeightPattern = 2;
	_animeFrameMax = 0;
	_size = D3DXVECTOR2(TREE_WIDTH, TREE_HEIGHT);
	//_jump = false;
	_move = 0;
	_animeBasePattern = 0;
	_animeSkipFrame = 0;
	_reverse = true;
	_hp = 10;
	_oldHp = 0;
	_unbeatable = false;
	_unbeatableTime = TREE_UNBEATABLE_TEME;
	_unbeatableCou = 0;
	//_jumpPower = -15;
	_oldGround = false;
	_U = 0.0f;
	_V = 0.0f;
	_UW = 1.0f / TREE_WIDTH_PATTERN;
	_VH = 1.0f / TREE_HEIGHT_PATTERN;
	_animePattern = 0;
}

void Tree::Update()
{
	if(_use)
	{
		auto player = EntityManager::Instance()->GetEntityWithTag<Player>("Player");
		float enemyRadian = 0;
		if (!_unbeatable && CollisionRot(_pos.x, _pos.y, player->GetHitBox()._pos.x, player->GetHitBox()._pos.y, TREE_HITBOX_WIDTH, TREE_HITBOX_HEIGHT, player->GetHitBox()._size.x, player->GetHitBox()._size.y, 0.0f))
		{
			_hp--;
		}

		if (_hp <= 0)
		{
			SetParticle(_pos.x, _pos.y, 30, 1, 1, 1);
			_use = false;
			_hitBox._use = false;
		}
		//ダメージを食らった時の処理
		else if (_oldHp > _hp)
		{
			_unbeatable = true;
			//PlaySound(g_SE_playerHit, 0);
		}

		//無敵中の処理
		if (_unbeatable)
		{
			_unbeatableCou = Counter(_unbeatableCou, _unbeatableTime);
			if (_unbeatableCou % 10 < 5)
			{
				_color.a = 0.5f;
			}
			else
			{
				_color.a = 0.8f;
			}

			if (_unbeatableCou == 0)
			{
				_unbeatable = false;
				_color.a = 1.0f;
			}
		}
		else
		{
			if (_color.a == 0)_color.a = 1;
		}
	}

}


void Tree::Draw()
{
	if (_use)
	{
		SetSamplerState(FILTER_MODE_POINT, ADDRESS_MODE_MIRROR);//僥僋僗僠儍偺僼傿儖僞乕傪OFF
		D3DXVECTOR2 uv = SetAnimation(_animeBasePattern, _animePattern, TREE_WIDTH_PATTERN, TREE_HEIGHT_PATTERN, _animeWidthPattern, _reverse);
		_U = uv.x;
		_V = uv.y;

		_animeSkipFrame = Counter(_animeSkipFrame, TREE_FRAME_SPAN / _walksp);
		if (_animeSkipFrame == 0)
		{
			_animePattern = Counter(_animePattern, _animeFrameMax);
		}

		DrawSpriteColorRotateCamera(_textureNo,
			(int)_pos.x,
			(int)_pos.y,
			_size.x, _size.y,	//暆丄崅偝
			_U, _V,		//拞怱UV嵗昗
			_UW, _VH,		//僥僋僗僠儍暆丄崅偝
			_color.r, _color.g, _color.b, _color.a,
			0.0f
		);
	}

}

void Tree::UnInit()
{

}
