/*==============================================================================

   スコア [Score.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCORE_MAX			(99999)		// スコアの最大値
#define SCORE_DIGIT			(2)			// 桁数

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
	D3DXVECTOR2 m_WH = D3DXVECTOR2(0.0f, 0.0f);			// 幅と高さ
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ポリゴンの座標
	int m_TexNo = 0;	// テクスチャ番号
	int m_Score = 0;	// スコア
};









