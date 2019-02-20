#include "SceneManager.h"
#include "GameScene.h"



SceneManager::SceneManager()
{
	m_CurrentScene = SCENE_NONE;
	m_NextScene = GAME_SCENE;
}

SceneManager::~SceneManager()
{
	
}


void SceneManager::Update()
{
	if (m_CurrentScene != m_NextScene)
	{
		switch (m_NextScene)
		{
		case TITLE_SCENE:
			//m_pScene = new  TitleScene();
			break;
		case GAME_SCENE:
			m_pScene = new  GameScene();
			break;
		case RESULT_SCENE:
			//m_pScene = new  ResultScene();
			break;
		}
		m_CurrentScene = m_NextScene;
	}
	m_pScene->Update();
}


void SceneManager::Render()
{
	m_pScene->Render();
}
