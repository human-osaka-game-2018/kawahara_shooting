#include "GameScene.h"

GameScene::GameScene()
{
	m_pDirectX = DirectX::GetInstance();
	m_pGamePlayer = new GamePlayer();
	m_pGameEnemy = new GameEnemy();
	LoadResources();
	m_pGameEnemy->LoadDate("csv/Stage1.csv");
	InfoGameBG centerBG;
	centerBG.CenterBGPosX = 320.f;
	centerBG.CenterBGPosY = 240.f;
	m_pDirectX->InitRectangleCustomVertex(m_BGVertices, centerBG.CenterBGPosX, centerBG.CenterBGPosY,384.f,480.f);
}

GameScene::~GameScene()
{
	delete m_pGamePlayer;
	m_pGamePlayer = NULL;
}

void GameScene::Update()
{
	m_pGamePlayer->Update();
	m_pGameEnemy->Update();
	ScrollBackGround();
	KeyOperation();
}

void GameScene::Render()
{
	m_pDirectX->DrawTexture("GAME_BG_TEX", m_BGVertices);
	m_pGamePlayer->Render();
	m_pGameEnemy->Render();
}

void GameScene::KeyOperation()
{
		
}

void GameScene::LoadResources()
{
	m_pDirectX->LoadTexture("Texture/Player.png", "GAME_PLAYER_TEX");
	m_pDirectX->LoadTexture("Texture/Enemy.png", "GAME_ENEMY_TEX");
	m_pDirectX->LoadTexture("Texture/GameBG.jpg", "GAME_BG_TEX");
	m_pDirectX->LoadTexture("Texture/Bullet.png", "GAME_BULLET_TEX");
}

void GameScene::ScrollBackGround()
{
	if (m_BGVertices[0].tv <= -1.0f)
	{
		for (CustomVertex& bgVertex : m_BGVertices)
		{
			bgVertex.tv += 1.0f;
		}
	}
	for (CustomVertex& bgVertex : m_BGVertices)
	{
		bgVertex.tv -= 0.005f;
	}
}
