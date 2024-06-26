/*==============================================================================

   V[(îê) [Scene.h]
														 Author : nç³ C
														 Date   : 2023/12/30
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//Oûé¾
class SceneManager;

//*****************************************************************************
// NXè`
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

