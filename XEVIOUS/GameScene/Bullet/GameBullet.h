#pragma once

#include "DirectX.h"
#include <vector>

const float BULLET_SIZE = 10.f;
const float BULLET_SPEED = 7.f;

class GameBullet
{
public:
	GameBullet();
	~GameBullet();
	void Update();
	void Render();
	void Create(float centerPlayerPosX, float centerPlayerPosY);
	struct InfoBullet
	{
		CustomVertex Bullet[4];
		bool CheakHit = false;

		float X = 0.f;
		float Y = 0.f;
	};

	static  std::vector<InfoBullet> m_BulletPos;
	std::vector<InfoBullet> GetBulletPos() { return m_BulletPos; }

private:
	DirectX* m_pDirectX;
	InfoBullet m_CenterBullet;
	int m_BulletIntervalCount;
	bool m_BulletInterval;
	int m_BulletIntervalRange;

};
