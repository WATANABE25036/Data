/*==============================================================================

   �V�[���Ǘ� [SceneManager.h]
														 Author : �n� �C
														 Date   : 2023/12/29
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "Game.h"
#include "Result.h"
#include "Title.h"
#include "Inventory.h"
#include "Player.h"
class Fade;

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum SCENE_INDEX
{
	SCENE_NONE,		//�V�[�������Ȃ�
	SCENE_TITLE,	//�^�C�g��
	SCENE_GAME,		//�Q�[��
	SCENE_RESULT,	//���U���g

	SCENE_MAX		//�Ōゾ�Ƃ킩��z�������
};

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	HRESULT Init(SCENE_INDEX index);
	void Uninit();
	void Update();
	void Draw();

	void SetScene(SCENE_INDEX index);
	SCENE_INDEX GetNextIndex() const;
	void CheckScene();

	Inventory* GetInventory() { return m_pInventory; }
	bool GetComplete()const { return m_Complete; }
	Player* GetPlayer()const { return m_pPlayer; }
	void SetFade(Fade* fade) { m_pFade = fade; }
	void SetInventory(Inventory* inventory) { m_pInventory = inventory; }
	void SetComplete(bool complete) { m_Complete = complete; }

private:
	Game m_Game = nullptr;
	Result m_Result = nullptr;
	Title m_Title = nullptr;
	Fade* m_pFade = nullptr;
	Player* m_pPlayer = nullptr;
	Inventory* m_pInventory = nullptr;
	SCENE_INDEX m_SceneIndex = SCENE_NONE;
	SCENE_INDEX m_SceneNextIndex = SCENE_NONE;
	bool m_Complete = false;
};




