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
};

class GameEnemy
{
public:
	GameEnemy();
	~GameEnemy();
	void Update();
	void Render();
	void LoadDate(const char* fileName);

private:
	DirectX* m_pDirectX;
	struct InfoEnemy
	{
		CustomVertex Enemy[4];
		int count = 0;

		int AppearTime;
		float x = 0.f;
		float y = 0.f;
		int HP;
		int Item;
		int Type;
	};
	std::vector<InfoEnemy> m_EnemyPos;
	InfoEnemy m_EnemyData;
};