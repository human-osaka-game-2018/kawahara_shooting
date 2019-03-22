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
	NORMAL,
	NORMAL2,
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

private:
	void MoveOperation();
	DirectX* m_pDirectX;
	struct InfoEnemy
	{
		CustomVertex Enemy[4];
		int AppearCount = 0;
		bool m_MovementChange = true;
		int MovementChangeCount = 0;


		int AppearTimeSec;
		float X = 0.f;
		float Y = 0.f;
		int HP;
		int Item;
		int Type;
		int MovePattern;
	};
	std::vector<InfoEnemy> m_EnemyStatuses;
	InfoEnemy m_EnemyData;
	float m_EnemyMoveSpeed;
	bool AppearCountIsMoreThan(InfoEnemy enemies);
};
