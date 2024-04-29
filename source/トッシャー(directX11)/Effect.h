/*==============================================================================

   エフェクト(ビルボード) [Effect.h]
														 Author : 渡邉 修
														 Date   : 2024/02/15
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Board.h"

//エフェクトの種類
enum EFFECT_PATTERN
{
	//エフェクトを追加したらここに追加
	//---------------------
	EFFECT_PATTERN_NONE,
	RIPPLES,//波紋
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

