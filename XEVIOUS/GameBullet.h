#pragma once

#include "DirectX.h"
#include <vector>

const float BulletSize = 10.f;
const float BulletSpeed = 7.f;

class GameBullet
{
public:
	GameBullet();
	~GameBullet();
	void Update();
	void Render();
	void Create(float CenterPlayerPosX, float CenterPlayerPosY);

private:
	DirectX* m_pDirectX;
	struct InfoBullet
	{
		CustomVertex Bullet[4];

		float x = 0.f;
		float y = 0.f;
	};
	std::vector<InfoBullet> m_BulletPos;
	InfoBullet m_CenterBullet;
	int m_BulletIntervalCount;
	bool m_BulletInterval;
	int m_BulletIntervalRange;

};
