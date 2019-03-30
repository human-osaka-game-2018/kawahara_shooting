#include "GameScene.h"

GameScene::GameScene()
{
	m_pDirectX = DirectX::GetInstance();
	m_pGamePlayer = GamePlayer::GetInstance();
	m_pEnemyManager = new EnemyManager();
	LoadResources();
	m_pEnemyManager->LoadDate("csv/Stage1.csv");
	InfoGameBG centerBG;
	centerBG.CenterBGPosX = 320.f;
	centerBG.CenterBGPosY = 240.f;
	m_pDirectX->InitRectangleCustomVertex(m_BGVertices, centerBG.CenterBGPosX, centerBG.CenterBGPosY,384.f,480.f);
}

GameScene::~GameScene()
{
	m_pGamePlayer->DeleteInstence();
	delete m_pEnemyManager;
	m_pEnemyManager = NULL;
}

void GameScene::Update()
{
	m_pGamePlayer->Update();
	m_pEnemyManager->Update();
	ScrollBackGround();
	KeyOperation();
}


void GameScene::Render()
{
	m_pDirectX->DrawTexture("GAME_BG_TEX", m_BGVertices);
	m_pGamePlayer->Render();
	m_pEnemyManager->Render();
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
