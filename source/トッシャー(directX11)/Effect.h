/*==============================================================================

   �G�t�F�N�g(�r���{�[�h) [Effect.h]
														 Author : �n� �C
														 Date   : 2024/02/15
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Board.h"

//�G�t�F�N�g�̎��
enum EFFECT_PATTERN
{
	//�G�t�F�N�g��ǉ������炱���ɒǉ�
	//---------------------
	EFFECT_PATTERN_NONE,
	RIPPLES,//�g��
	//---------------------
};

class Effect : public Board
{
public:
	Effect(D3DXVECTOR3 pos, D3DXVECTOR3 rot, EFFECT_PATTERN pattern, GameWorld* gameWorld, ORDER_TAG tag, int ownerCou);
	~Effect();
	void Init() override;
	void Update() override;

private:
	static int m_sCou;
};

