/*==============================================================================

   �}�b�v�ɕ��ׂ�^�C��(�h��) [Tile.h]
														 Author : �n� �C
														 Date   : 2024/01/16
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Object.h"
#include "BodyParts.h"

//�^�C���̌�����
enum TILE_PATTERN
{
	//�^�C����ǉ������炱���ɒǉ�
	//---------------------
	//��
	TILE_PATTERN_NONE,
	WALL,		//����ȕ�
	WALL_END,	//����ȕǒ[
	PILLAR,		//��
	CORNER,		//�p
	T,			//T��
	CROSS,		//�\��
	DEAD_END,	//�s���~�܂�
	//---------------------
	//��
	AISLE,		//�ʘH
	CEILING,	//�V��t����
	//---------------------
};

class Tile : public Object
{
public:
	Tile(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TILE_PATTERN pattern, GameWorld* gameWorld);
	~Tile() override;

	void Init() override;
	void Update() override;

private:

};
