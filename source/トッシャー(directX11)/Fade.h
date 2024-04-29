/*==============================================================================

   フェード処理 [Fade.h]
														 Author : 学校配布、渡邉 修
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include <d3dx9.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	FADE_RATE					(0.02f)			// フェード係数

// フェードの状態
enum FADE_STATE
{
	FADE_NONE = 0,	// フェード処理をしていない
	FADE_IN,		// フェードイン処理中
	FADE_OUT,		// フェードアウト処理中
	FADE_OUT_COMP,	// フェードアウト完了
};

class Fade
{
public:
	Fade();
	~Fade();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void FadeOut();
	void FadeIn();
	FADE_STATE GetFadeState() const;

	void SetFadeColor(float r, float g, float b);

private:
	FADE_STATE m_FadeState = FADE_NONE;// フェードの状態
	D3DXCOLOR m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //フェードのカラー
	int m_TextureNo = 0;// テクスチャ番号
};

