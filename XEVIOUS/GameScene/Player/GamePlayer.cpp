#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
	m_pDirectX = DirectX::GetInstance();
	m_pGameBullet = new GameBullet();
	InfoPlayer centerPlayerPos;
	centerPlayerPos.X = 320.f;
	centerPlayerPos.Y = 464.f;
	m_pDirectX->InitSquareCustomVertex(m_Player, centerPlayerPos.X, centerPlayerPos.Y, PLAYER_SIZE);
}

GamePlayer::~GamePlayer()
{

}

void GamePlayer::Update()
{
	//キャラのキーの動き
	KeyOperation();
	//ステージ外に出たら戻る
	TurnbackToGameArea();
	//弾の動き
	m_pGameBullet->Update();
}


void GamePlayer::KeyOperation()
{
	D3DXVECTOR2 moveDirection(0.f, 0.f);
	if (m_pDirectX->IsKeyPressed(DIK_LEFT))
	{
		moveDirection.x -= 1.f;
	}
	if (m_pDirectX->IsKeyPressed(DIK_RIGHT))
	{
		moveDirection.x += 1.f;
	}
	if (m_pDirectX->IsKeyPressed(DIK_UP))
	{
		moveDirection.y -= 1.f;
	}
	if (m_pDirectX->IsKeyPressed(DIK_DOWN))
	{
		moveDirection.y += 1.f;
	}
	//単位ベクトルを求める関数
	D3DXVec2Normalize(&moveDirection, &moveDirection);

	moveDirection *= PLAYER_MOVE_SPEED;

	m_pDirectX->MoveCustomVertex(m_Player, moveDirection);

	if (m_pDirectX->IsKeyPressed(DIK_SPACE))
	{
		float centerX = m_Player[0].x + (PLAYER_SIZE / 2);
		float centerY = m_Player[0].y + (PLAYER_SIZE / 2);
		m_pGameBullet->Create(centerX, centerY);
	}
}

//ステージ外に出たら戻る
void GamePlayer::TurnbackToGameArea()
{
	float centerX;
	float centerY;
	if (m_Player[0].x <= MARGIN)
	{
		centerX = MARGIN + (PLAYER_SIZE / 2);
		centerY = m_Player[0].y + (PLAYER_SIZE / 2);
		m_pDirectX ->InitSquareCustomVertex(m_Player, centerX, centerY, PLAYER_SIZE);
	}
	if (m_Player[1].x >= DISPLAY_WIDTH - MARGIN)
	{
		centerX = (DISPLAY_WIDTH - MARGIN) - (PLAYER_SIZE / 2);
		centerY = m_Player[1].y + (PLAYER_SIZE / 2);
		m_pDirectX->InitSquareCustomVertex(m_Player, centerX, centerY, PLAYER_SIZE);
	}
	if (m_Player[0].y < 0.f)
	{
		centerX = m_Player[0].x + (PLAYER_SIZE / 2);
		centerY = 0.f + (PLAYER_SIZE / 2);
		m_pDirectX->InitSquareCustomVertex(m_Player, centerX, centerY, PLAYER_SIZE);
	}
	if (m_Player[2].y > DISPLAY_HEIGHT)
	{
		centerX = m_Player[2].x - (PLAYER_SIZE / 2);
		centerY = DISPLAY_HEIGHT - (PLAYER_SIZE / 2);
		m_pDirectX->InitSquareCustomVertex(m_Player, centerX, centerY, PLAYER_SIZE);
	}
}

void GamePlayer::Render()
{
	m_pDirectX->DrawTexture("GAME_PLAYER_TEX", m_Player);
	m_pGameBullet->Render();
}
