#pragma once

#include "Scene.h"
#include "DirectX.h"
#include "GamePlayer.h"
#include "EnemyManager.h"


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void Update();
	void Render();

private:
	DirectX * m_pDirectX;
	GamePlayer* m_pGamePlayer;
	EnemyManager* m_pEnemyManager;
	CustomVertex m_BGVertices[4];
	struct InfoGameBG
	{
		float CenterBGPosX = 0.f;
		float CenterBGPosY = 0.f;
	};
	void KeyOperation();
	void LoadResources();
	void ScrollBackGround();
};
