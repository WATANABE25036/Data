/*==============================================================================

   タイトル画面処理(派生) [Title.h]
														 Author : 学校配布、渡邉 修
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include "Scene.h"

//*****************************************************************************
// クラス定義
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
	int	m_TextureNo = 0;	// テクスチャ情報
	int	m_BGMNo1 = 0;		// BGM識別子
	int	m_BGMNo2 = 0;		// BGM識別子
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


