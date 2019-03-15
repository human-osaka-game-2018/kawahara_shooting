#pragma once

#include"DirectX.h"
#include <vector>

enum Parameter
{
	APPEARTIME,
	POSX,
	POSY,
	HP,
	ITEM,
	TYPE,
	MOVEPATTERN,
};

enum EnemyType
{
	TYPE1,
	TYPE2,
};

const float ENEMY_SIZE = 32.f;

class GameEnemy
{
public:
	GameEnemy();
	~GameEnemy();
	void Update();
	void Render();
	void LoadDate(const char* fileNam);
	int m_AppearCount = 0;

private:
	void MoveOperation();
	DirectX* m_pDirectX;
	struct EnemyStatus
	{
		CustomVertex Enemy[4];
		bool MovementChange = true;
		int MovementChangeCount = 0;
		int AppearTimeSec;
		float X = 0.f;
		float Y = 0.f;
		int HP;
		int Item;
		int Type;
		int MovePattern;
	};
	std::vector<EnemyStatus> m_EnemyStatuses;
	EnemyStatus m_EnemyData;
	float m_EnemyMoveSpeed;
	bool CanAppear(EnemyStatus enemyStatus);
};
