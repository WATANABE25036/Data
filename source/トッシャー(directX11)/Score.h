/*==============================================================================

   �X�R�A [Score.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_MAX			(99999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(2)			// ����

class Score
{
public:
	Score();
	~Score();

	HRESULT Init(void);
	void Draw(void);
	void Add(int add);
	void SetScore(int value);

private:
	D3DXVECTOR2 m_WH = D3DXVECTOR2(0.0f, 0.0f);			// ���ƍ���
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �|���S���̍��W
	int m_TexNo = 0;	// �e�N�X�`���ԍ�
	int m_Score = 0;	// �X�R�A
};









