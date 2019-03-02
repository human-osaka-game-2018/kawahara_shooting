#include "GameBullet.h"

using std::vector;

GameBullet::GameBullet()
{
	m_pDirectX = DirectX::GetInstance();
}

GameBullet::~GameBullet()
{

}

void GameBullet::Update()
{
	for (auto& m_CenterBullet : m_BulletPos)
	{
		m_CenterBullet.y -= BulletSpeed;
		m_pDirectX->InitSquareCustomVertex(m_CenterBullet.Bullet, m_CenterBullet.x, m_CenterBullet.y, BulletSize);
	}
}

void GameBullet::Create(float CenterPlayerPosX, float CenterPlayerPosY)
{
	m_CenterBullet.x = CenterPlayerPosX;
	m_CenterBullet.y = CenterPlayerPosY;
 	m_BulletPos.push_back(m_CenterBullet);
}

void GameBullet::Render()
{
	for (auto& m_CenterBullet : m_BulletPos)
	{
		m_pDirectX->DrawTexture("GAME_BULLET_TEX", m_CenterBullet.Bullet);
	}
}
