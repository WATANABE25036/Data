/*==============================================================================

   �V�[��(���) [Scene.h]
														 Author : �n� �C
														 Date   : 2023/12/30
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//�O���錾
class SceneManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class Scene
{
public:
	Scene(SceneManager* sceneManager);
	virtual ~Scene();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

protected:
	SceneManager* m_pSceneManager = nullptr;
};

