/*==============================================================================

   �r���{�[�h(���) [BillBoard.h]
														 Author : �n� �C
														 Date   : 2023/11/30
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Renderer.h"
#include "Camera.h"

#define BULLET_NUM		(10)		// �o���b�g��Max��
#define BULLET_SPEED	(10.0f)		// �o���b�g�̈ړ��X�s�[�h

class BillBoard : public Object
{
public:
	BillBoard(D3DXVECTOR3 pos, D3DXVECTOR3 rot, GameWorld* gameWorld, Camera* camera);
	virtual ~BillBoard();

	virtual void Init() override;
	void Uninit() override;
	virtual void Update() override;
	void Draw() override;
	void ModelLoad() override;

protected:
	MATERIAL m_Material;
	int m_TexNo = 0;
	ID3D11Buffer* m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	Camera* m_pCamera = nullptr;
};

