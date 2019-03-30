#pragma once

#include "DirectX.h"
#include "GameBullet.h"

const float PLAYER_SIZE = 32.f;
const float PLAYER_MOVE_SPEED = 5.f;

class GamePlayer
{
public:
	//singleton関係
	static GamePlayer* GetInstance();
	void DeleteInstence();

	void Update();
	void Render();
	
	CustomVertex m_Player[4];
private:
	GamePlayer();
	~GamePlayer();

	DirectX* m_pDirectX;
	GameBullet* m_pGameBullet;
	float m_PosX = 0.f;
	float m_PosY = 0.f;
	void KeyOperation();
	void TurnbackToGameArea();

	static GamePlayer* m_pInstance;
};
