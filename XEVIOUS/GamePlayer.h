#pragma once

#include "CustomVertex.h"
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
	CustomVertex m_Player[4];
	
private:
	DirectX* m_pDirectX;
	struct InfoPlayer
	{
		float CenterPlayerPosX = 0.f;
		float CenterPlayerPosY = 0.f;
	};
	void KeyOperation();
	void RestrictionFrameOut();
};
