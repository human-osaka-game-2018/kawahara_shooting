#pragma once

#include"DirectX.h"
#include "GamePlayer.h"

enum EnemyType
{
	TYPE1,
	TYPE2,
};

class Enemy
{
public:
	struct  Status
	{
		CustomVertex m_EnemyVertex[4];
		int m_AppearTimeSec;
		float m_PosX = 0.f;
		float m_PosY = 0.f;
		int m_HP;
		int m_Item;
		int m_Type;
		int m_MovePattern;
		int m_TheirNumber;
	};

	Enemy(Status status);
	~Enemy();
	void Update();
	void Render();
	void DamageCalculation();
	void CheckCollisionPlayertoEnemy();
	void CheckCollisionBullettoEnemy();

	Status GetStatus() { return m_Status; }

private:
	DirectX * m_pDirectX;
	GamePlayer * m_pGamePlayer;
	GameBullet* m_pGameBullet;
	void MoveOperation();
	float m_EnemyMoveSpeed;
	bool m_MovementChange = true;
	int m_MovementChangeCount = 0;
	Status m_Status;
};
