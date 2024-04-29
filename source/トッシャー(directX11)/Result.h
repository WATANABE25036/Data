/*==============================================================================

   ���U���g��ʏ���(�h��) [Result.h]
														 Author : �w�Z�z�z�A�n� �C
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Scene.h"
#include "Inventory.h"
#include "Score.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Result : public Scene
{
public:
	Result(SceneManager* sceneManager);
	~Result();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	int	m_TextureNo = 0;	// �e�N�X�`�����
	int	m_BGMNo = 0;		// BGM���ʎq
	int m_SE_CursorMove = 0;
	int m_SE_Decision = 0;
	int m_SE_Result = 0;
	float m_LightMove = 0;
	float m_LightOffsetX = 0;
	int m_TextureNoLight = 0;
	int m_TextureNoRetry = 0;
	int m_TextureNoQuit = 0;
	int m_TextureNoCursor = 0;
	int m_TextureNoCompleteText = 0;
	int m_TextureNoRest = 0;
	float m_SelectX = 0;
	int m_Cou = 0;
	bool m_Retry = false;
	bool m_Quit = false;
	bool m_RightButton = false;
	bool m_LeftButton = false;
	bool m_SelectButton = false;
	bool m_CursorRetry = false;
	bool m_CursorQuit = false;
	std::list<Item*> m_pItemList;
	Inventory m_Inventory;
	Score m_Score;
};



