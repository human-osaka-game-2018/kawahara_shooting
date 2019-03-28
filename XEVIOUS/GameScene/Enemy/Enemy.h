#pragma once

#include"DirectX.h"


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
	};

	Enemy(Status status);
	~Enemy();
	void Update();
	void Render();

	const Status& GetStatus() { return m_Status; }

private:
	void MoveOperation();
	DirectX* m_pDirectX;
	float m_EnemyMoveSpeed;
	bool m_MovementChange = true;
	int m_MovementChangeCount = 0;
	Status m_Status;
};
