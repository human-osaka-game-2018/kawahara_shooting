#include "GameScene.h"

GameScene::GameScene()
{
	m_pDirectX = DirectX::GetInstance();
	m_pGamePlayer = new GamePlayer();
	LoadResources();
	InfoGameBG CenterBG;
	CenterBG.CenterBGPosX = 320.f;
	CenterBG.CenterBGPosY = 240.f;
	m_pDirectX->InitRectangleCustomVertex(m_BG, CenterBG.CenterBGPosX, CenterBG.CenterBGPosY,384.f,480.f);
}

GameScene::~GameScene()
{
	delete m_pGamePlayer;
	m_pGamePlayer = NULL;
}

void GameScene::Update()
{
	m_pGamePlayer->Update();
	ScrollBackGround();
	KeyOperation();
}

void GameScene::Render()
{
	m_pDirectX->DrawTexture("GAME_BG_TEX", m_BG);
	m_pGamePlayer->Render();
}

void GameScene::KeyOperation()
{
		
}

void GameScene::LoadResources()
{
	m_pDirectX->LoadTexture("Texture/Player.png", "GAME_PLAYER_TEX");
	m_pDirectX->LoadTexture("Texture/GameBG.jpg", "GAME_BG_TEX");
	m_pDirectX->LoadTexture("Texture/Bullet.png", "GAME_BULLET_TEX");
}

void GameScene::ScrollBackGround()
{
	if (m_BG[0].tv <= -1.0f)
	{
		for (int i = 0;i < 4;i++)
		{
			m_BG[i].tv = 0.f;
			if (i > 1)
			{
				m_BG[i].tv = 1.0f;
			}
		}
	}
	for (int i = 0;i < 4;i++)
	{
		m_BG[i].tv -= 0.01f;
	}
}
