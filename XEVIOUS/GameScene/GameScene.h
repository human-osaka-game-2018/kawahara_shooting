#pragma once

#include "Scene.h"
#include "DirectX.h"
#include "GamePlayer.h"
#include "GameEnemy.h"


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
	GameEnemy* m_pGameEnemy;
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
