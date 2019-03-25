#pragma once

#include"DirectX.h"
#include"Enemy.h"
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


const float ENEMY_SIZE = 32.f;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update();
	void Render();
	void LoadDate(const char* fileName);

private:
	DirectX* m_pDirectX;
	int m_AppearCount = 0;
	int m_EnemyCreateCount = 0;
	std::vector<Enemy*> m_Enemies;
	std::vector<Enemy::Status> m_Statuses;
	bool CanAppear(int appeartimesec);
};
