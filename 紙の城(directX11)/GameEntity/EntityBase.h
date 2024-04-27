/*********************************************************************
 * \file   EntityBase.h
 * \brief  
 * 
 * \author MA HANGLONG
 * \date   2024 \  01 \ 17 
 *********************************************************************/
#pragma once
#include "..\renderer.h"
#include "..\tile.h"
#include <string>

#define Vec2		D3DXVECTOR2
#define Color		D3DXCOLOR

struct HitBox
{
	Vec2 _size;
	Vec2 _pos;
	bool _use;
};

class EntityBase
{
public:
	EntityBase() = default;
	EntityBase(const std::string tag) :_tag(tag) { ; }
	EntityBase(const std::string tag, int texNo) :_tag(tag),_textureNo(texNo) { ; }
	virtual ~EntityBase(){}
protected:
	std::string			_tag;
	Vec2				_pos;
	Vec2				_vel;
	Color				_color;
	int					_dir;
	bool				_use;
	Vec2				_size;

	float				_hsp;
	float				_vsp;
	float				_grv;

	float				_walksp;
	float				_controller;
	bool				_hascontrol;
	int					_canjump;
	float				_knockBackX;
	float				_knockBackY;
	bool				_ground;
	bool				_oldGround;
	bool				_reverse;

	float				_hp;
	float				_maxHp;
	float				_oldHp;
	int					_itemCount = 0;

	bool				_unbeatable;
	int					_unbeatableCou;
	int					_unbeatableTime;

	int					_spawnCounter;
	int					_spawnTime;
	bool				_canEnemySpawn;
	bool				_canAllySpawn;
	bool				_canRegenerate;
	int					_regenerateCounter;


	int					_textureNo;
	int					_jumpPower;
	int					_move;
	TILE_DATA*			_Tile = nullptr;
	HitBox				_hitBox;
	HitBox				_attackBox;
public:
	int					_animeWidthPattern;
	int					_animeHeightPattern;
	int					_animeFrameMax;
	int					_animeBasePattern;
	int					_animeSkipFrame;
	int					_animeFrameSpan;
	float				_U;
	float				_V;
	float				_UW;
	float				_VH;
	int					_animePattern;
	int					_oldAnimePattern;
	float				_jumpSp;
	float				_attackTime;

public:
	int					score;
	int					loopTrigger;
	Vec2				notLoopPos;
	Vec2				oldPos;
	const int GetOldAnimePattern()const { return _oldAnimePattern; }
	const Vec2 GetPosition()const{ return _pos; }
	void SetPosition(const Vec2& pos) { _pos = pos; }
	void SetAttackTime(float time) { _attackTime = time; }
	void SetPosition(const float x, const float y) { SetPosition({ x,y }); }
	void SetPositionX(const float x) { _pos.x = x; }
	void SetPositionY(const float y) { _pos.y = y; }
	const Vec2 GetVel()const { return _vel; }
	void SetVel(const Vec2& vel) { _vel = vel; }
	const Color GetColor()const { return _color; }
	void SetColor(const Color& color) { _color = color; }
	const bool GetUse()const { return _use; }
	void SetUse(const bool use) { _use = use; }
	const Vec2 GetSize()const { return _size; }
	void SetSize(Vec2& size) { _size = size; }
	const int GetTexNo()const { return _textureNo; }
	void SetTexNo(const int texNO) { _textureNo = texNO; }
	const int GetMove()const { return _move; }
	void SetMove(const int move) { _move = move; }
	const bool GetReverse()const { return _reverse; }
	void SetReverse(const bool reverse) { _reverse = reverse; }
	const float GetKnockBackX() const { return _knockBackX; }
	void SetKnockBackX(const float x) { _knockBackX = x; }
	const float GetKnockBackY() const { return _knockBackY; }
	void SetKnockBackY(const float y) { _knockBackY = y; }
	const float GetVSpeed()const { return _vsp; }
	void SetVSpeed(const float vsp) { _vsp = vsp; }
	const float GetHSpeed()const { return _hsp; }
	void SetHSpeed(const float hsp) { _hsp = hsp; }
	const float GetWalkSpeed()const { return _walksp; }
	void SetWalkSpeed(const float walksp) { _walksp = walksp; }
	const bool GetCanJump()const { return _canjump; }
	void SetCanJump(const bool canJump) { _canjump = canJump; }
	const float GetGravity()const { return _grv; }
	void SetGravity(const float gravity) { _grv = gravity; }
	const float GetJumpPower()const { return _jumpPower; }
	void SetJumpPower(float jumpPower) { _jumpPower = jumpPower; }
	const TILE_DATA* GetTileData()const { return _Tile; }
	void SetTileData(TILE_DATA* p) { _Tile = p; }
	const bool GetGround()const { return _ground; }
	void SetGround(const bool ground) {_ground = ground;}
	const bool GetOldGround()const { return _oldGround; }
	void SetOldGround(const bool ground) { _oldGround = ground; }
	const float GetHp()const { return _hp; }
	const float GetMaxHp()const { return _maxHp; }
	void SetHp(const float hp) { _hp = hp; }
	const int GetItemCount()const { return _itemCount; }
	void SetItemCount(int itemCount) { _itemCount = itemCount; }
	void SetEnemySpawn(bool canEnemySpawn) { _canEnemySpawn = canEnemySpawn; }

	const std::string& GetTag()const { return _tag; }
	const int GetDirection()const { return _dir; }
	void SetDirection(const int dir) { _dir = dir; }
	const HitBox GetHitBox()const { return _hitBox; }
	HitBox GetAttackBox() const {
		return _attackBox;
	}
	void SetAttackUse(const bool use) { _attackBox._use = use; }
	void SetHitBoxUse(const bool use) {
		_hitBox._use = use;
	}

	int GetSpawnCounter() const {
		return _spawnCounter;
	}
	void SetUnbeatable(bool unbeatable) {
		_unbeatable = unbeatable;
	}

	void SetOldHp(const float hp) { _oldHp = hp; }
	const float GetOldHp()const { return _oldHp; }
	const float GetVsp()const { return _vsp; }

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void UnInit() = 0;
};

