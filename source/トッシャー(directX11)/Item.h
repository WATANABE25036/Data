/*==============================================================================

   �A�C�e�� [Item.h]
														 Author : �n� �C
														 Date   : 2024/02/13
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "BillBoard.h"

//�A�C�e���̎��
enum ITEM_PATTERN
{
	//�A�C�e����ǉ������炱���ɒǉ�
	//---------------------
	//��
	ITEM_PATTERN_NONE,
	COIN_GOLD,//����
	//---------------------
};

class Item : public BillBoard
{
public:
	Item(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_PATTERN pattern, GameWorld* gameWorld, Camera* camera);
	~Item();

	void Init() override;
	void Update() override;

	ITEM_PATTERN GetItemPattern() const { return m_ItemPattern; }
	int GetNum() const { return m_Num; }
	int GetItemCou() const { return m_sCou; }
	void SetNum(int num) { m_Num = num; }

private:
	ITEM_PATTERN m_ItemPattern = ITEM_PATTERN_NONE;
	int m_Num = 0; //�擾��
	static int m_sCou;
};

