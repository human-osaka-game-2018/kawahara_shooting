﻿#include "GameScene.h"

GameScene::GameScene()
{
	m_pDirectX = DirectX::GetInstance();
	m_pGamePlayer = new GamePlayer();
	LoadResources();
	InfoGameBG CenterBG;
	CenterBG.CenterBGPosX = 320.f;
	CenterBG.CenterBGPosY = 240.f;
	m_pDirectX->InitRectangleCustomVertex(m_BGVertices, CenterBG.CenterBGPosX, CenterBG.CenterBGPosY,384.f,480.f);
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
	m_pDirectX->DrawTexture("GAME_BG_TEX", m_BGVertices);
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
	if (m_BGVertices[0].tv <= -1.0f)
	{
		for (CustomVertex& BGVertex : m_BGVertices)
		{
			BGVertex.tv += 1.0f;
		}
	}
	for (CustomVertex& BGVertex : m_BGVertices)
	{
		BGVertex.tv -= 0.01f;
	}
}
