/*==============================================================================

   �t�F�[�h���� [Fade.h]
														 Author : �w�Z�z�z�A�n� �C
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once
#include <d3dx9.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FADE_RATE					(0.02f)			// �t�F�[�h�W��

// �t�F�[�h�̏��
enum FADE_STATE
{
	FADE_NONE = 0,	// �t�F�[�h���������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C��������
	FADE_OUT,		// �t�F�[�h�A�E�g������
	FADE_OUT_COMP,	// �t�F�[�h�A�E�g����
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
	FADE_STATE m_FadeState = FADE_NONE;// �t�F�[�h�̏��
	D3DXCOLOR m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); //�t�F�[�h�̃J���[
	int m_TextureNo = 0;// �e�N�X�`���ԍ�
};

