/*==============================================================================

   �^�C�g����ʏ���(�h��) [Title.h]
														 Author : �w�Z�z�z�A�n� �C
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Scene.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Title : public Scene
{
public:
	Title(SceneManager* sceneManager);
	~Title();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int	m_TextureNo = 0;	// �e�N�X�`�����
	int	m_BGMNo1 = 0;		// BGM���ʎq
	int	m_BGMNo2 = 0;		// BGM���ʎq
	int m_SE_CursorMove = 0;
	int m_SE_Decision = 0;
	int m_TextureNoLight = 0;
	int m_TextureNoStart = 0;
	int m_TextureNoEnd = 0;
	int m_TextureNoCursor = 0;
	float m_LightMove = 0;
	float m_LightOffsetX = 0;
	float m_SelectX = 0;
	int m_Cou = 0;
	bool m_NextScene = false;
	bool m_End = false;
	bool m_RightButton = false;
	bool m_LeftButton = false;
	bool m_SelectButton = false;
	bool m_GameScene = false;
	bool m_CursorStart = false;
	bool m_CursorEnd = false;
};


