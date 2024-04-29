/*==============================================================================

   �{�[�h(���) [Board.h]
														 Author : �n� �C
														 Date   : 2024/02/15
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Renderer.h"
#include "Object.h"

#define BULLET_NUM		(10)		// �o���b�g��Max��
#define BULLET_SPEED	(10.0f)		// �o���b�g�̈ړ��X�s�[�h

enum class ORDER_TAG;

class Board : public Object
{
public:
	Board(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld);
	virtual ~Board();

	virtual void Init() override;
	void Uninit() override;
	virtual void Update() override;
	void Draw() override;
	void ModelLoad() override;

protected:
	MATERIAL m_Material;
	int m_TexNo = 0;
	ID3D11Buffer* m_VertexBuffer = NULL;	// ���_�o�b�t�@
};

