#include "GameBullet.h"

using std::vector;

GameBullet::GameBullet()
{
	m_pDirectX = DirectX::GetInstance();
	m_BulletIntervalCount = 0;
	m_BulletInterval = false;
	m_BulletIntervalRange = 8;
}

GameBullet::~GameBullet()
{

}

void GameBullet::Update()
{
	for (auto& CenterBullet : m_BulletPos)
	{
		CenterBullet.y -= BulletSpeed;
		m_pDirectX->InitSquareCustomVertex(CenterBullet.Bullet, CenterBullet.x, CenterBullet.y, BulletSize);
	}

	if (m_BulletInterval)
	{
		m_BulletIntervalCount++;
		if (m_BulletIntervalCount > m_BulletIntervalRange)
		{
			m_BulletInterval = false;
			m_BulletIntervalCount = 0;
		}
	}
}

void GameBullet::Create(float CenterPlayerPosX, float CenterPlayerPosY)
{
	if (!m_BulletInterval)
	{
		m_CenterBullet.x = CenterPlayerPosX;
		m_CenterBullet.y = CenterPlayerPosY;
		m_BulletPos.push_back(m_CenterBullet);

		m_BulletInterval = true;
	}
}

void GameBullet::Render()
{
	for (auto& CenterBullet : m_BulletPos)
	{
		m_pDirectX->DrawTexture("GAME_BULLET_TEX", CenterBullet.Bullet);
	}
}
