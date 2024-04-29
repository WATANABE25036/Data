/*==============================================================================

   �}�b�v [Map.h]
														 Author : �n� �C
														 Date   : 2024/01/18
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include <list>
#include "GameWorld.h"

#define MAX_TILE_X (50)//�ő�50���炢
#define MAX_TILE_Y (50)//�ő�50���炢
#define ATTRIBUTE_X (MAX_TILE_X - 4)//����̕Ǘp�ƃI�[�o�[�����΍��-4
#define ATTRIBUTE_Y (MAX_TILE_Y - 4)
#define TILE_HET_SIZE (80.0f)
#define TILE_OFFSET (60.0f)
#define TILE_OFFSET_HALF (TILE_OFFSET * 0.5f)

//�^�C���̑���
enum TILE_ATTRIBUTE
{
	OUT_RANGE,
	AIR,
	STOP,
};

enum TILE_STATE
{
	TILE_STATE_NONE,
	HEAR_SOUND,
};

//�A�C�e���̑���
enum ITEM_ATTRIBUTE
{
	ITEM_ATTRIBUTE_NONE,
	ITEM_SET,
};

struct TILE
{
	TILE_ATTRIBUTE TileAttribute = OUT_RANGE;
	ITEM_ATTRIBUTE ItemAttribute = ITEM_ATTRIBUTE_NONE;
	D3DXVECTOR3 Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�^�C������
	TILE_PATTERN TilePattern = TILE_PATTERN_NONE;
	ITEM_PATTERN ItemPattern = ITEM_PATTERN_NONE;
	TILE_STATE TileState = TILE_STATE_NONE;
	bool Player = false;//�v���C���[�����邩
	bool Enemy = false;//�G�l�~�[�����邩
	D3DXVECTOR2 arrayPos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};

struct  AROUND_TILE
{
	TILE Top;
	TILE Right;
	TILE Under;
	TILE Left;
};

class Map
{
public:
	Map(GameWorld* gameWorld);
	~Map();

	void Update();

	void CreateMap();//�������ƂɃ}�b�v����ʏ�ɐ���
	AROUND_TILE GetAroundTile(D3DXVECTOR3 pos) const;	//����̃^�C���̏���Ԃ�
	AROUND_TILE GetAroundTile(D3DXVECTOR2 pos) const;	//�z���
	void RandomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin);
	void SoundEcho(D3DXVECTOR2 arrayPos);

	TILE GetTile(D3DXVECTOR3 pos) const;
	D3DXVECTOR2 GetArrayPos(D3DXVECTOR3 pos) const;	//�ʒu����map�z��̂ǂ��ɂ��邩��Ԃ�
	D3DXVECTOR3 GetXYPos(D3DXVECTOR2 arrayPos) const;//map�z�񂩂�ʒu�̂ǂ��ɂ��邩��Ԃ�
	D3DXVECTOR3 GetPlayerSpawnPos() const { return m_PlayerSpawnPos; }

private:
	TILE m_Map[MAX_TILE_Y][MAX_TILE_X];
	GameWorld* m_pGameWorld;
	D3DXVECTOR3 m_PlayerOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 m_PlayerOldArrayPos = D3DXVECTOR2(0.0f, 0.0f);
	int m_PlayerNoMoveCou = 0;
	std::list<TILE*> m_TileHistory;//�^�C���̗���
	D3DXVECTOR3 m_PlayerSpawnPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�v���C���[�̃X�|�[���n�_
};

