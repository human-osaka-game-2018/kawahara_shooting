#pragma once

#include "Scene.h"
#include "DirectX.h"
#include "GamePlayer.h"


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void Update();
	void Render();
	void KeyOperation();
	void LoadResources();

private:
	DirectX * m_pDirectX;
	GamePlayer* m_pGamePlayer;
	CustomVertex m_BG[4];
	struct InfoGameBG
	{
		float CenterBGPosX = 0.f;
		float CenterBGPosY = 0.f;
	};
	void BGScroll(CustomVertex BG[4]);
};
