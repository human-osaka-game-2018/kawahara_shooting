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
	BGScroll(m_BG);
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
}

void GameScene::BGScroll(CustomVertex BG[4])
{
	if (BG[0].tv <= -1.0f)
	{
		BG[0].tv = 0.f;
		BG[1].tv = 0.f;
		BG[2].tv = 1.0f;
		BG[3].tv = 1.0f;
	}
		BG[0].tv -= 0.01f;
		BG[1].tv -= 0.01f;
		BG[2].tv -= 0.01f;
		BG[3].tv -= 0.01f;
}
