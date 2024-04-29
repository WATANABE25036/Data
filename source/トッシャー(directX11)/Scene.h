/*==============================================================================

   シーン(基底) [Scene.h]
														 Author : 渡邉 修
														 Date   : 2023/12/30
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

//前方宣言
class SceneManager;

//*****************************************************************************
// クラス定義
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

