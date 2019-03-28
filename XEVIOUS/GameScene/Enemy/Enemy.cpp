#include"Enemy.h"

Enemy::Enemy(Status status)
{
	m_Status = status;
	m_pDirectX = DirectX::GetInstance();
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	MoveOperation();
}

void Enemy::Render()
{
	m_pDirectX->DrawTexture("GAME_ENEMY_TEX", m_Status. m_EnemyVertex);
}

void Enemy::MoveOperation()
{
	D3DXVECTOR2 moveDirection(0.f, 0.f);
	m_MovementChangeCount++;
	switch (m_Status.m_MovePattern)
	{
	case TYPE1:
		moveDirection.y += 1.f;
		m_EnemyMoveSpeed = 4.f;
		break;
	case TYPE2:
		moveDirection.y += 2.f;
		m_EnemyMoveSpeed = 4.f;
		if (m_MovementChange)
		{
			moveDirection.x += 1.f;
		}
		else
		{
			moveDirection.x -= 1.f;
		}
		if (m_MovementChangeCount == 30)
		{
			m_MovementChange = ! m_MovementChange;
			m_MovementChangeCount = 0;
		}
		break;
	}
	//単位ベクトルを求める関数
	D3DXVec2Normalize(&moveDirection, &moveDirection);
	moveDirection *= m_EnemyMoveSpeed;
	m_pDirectX->MoveCustomVertex(m_Status.m_EnemyVertex, moveDirection);

}
