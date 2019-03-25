#pragma once

#include "DirectX.h"
#include "GameBullet.h"

const float PLAYER_SIZE = 32.f;
const float PLAYER_MOVE_SPEED = 5.f;

class GamePlayer
{
public:
	GamePlayer();
	~GamePlayer();
	void Update();
	void Render();
	
private:
	DirectX* m_pDirectX;
	GameBullet* m_pGameBullet;
	float m_PosX = 0.f;
	float m_PosY = 0.f;
	CustomVertex m_Player[4];
	void KeyOperation();
	void TurnbackToGameArea();
};
