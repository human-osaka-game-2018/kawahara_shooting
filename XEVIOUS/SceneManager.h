#pragma once

#include "Scene.h"
#include "SceneID.h"

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Update();
	void Render();

private:
	Scene* m_pScene;
	//今のシーン
	SCENE_NUM m_CurrentScene;
	//次のシーン
	SCENE_NUM m_NextScene;
};
