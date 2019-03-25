#include"EnemyManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using std::ifstream;
using std::string;
using std::stringstream;

EnemyManager::EnemyManager()
{
	m_pDirectX = DirectX::GetInstance();
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Update()
{
	m_AppearCount++;
	
	if (m_EnemyCreateCount > 0)
	{
		if (CanAppear(m_Statuses[0].m_AppearTimeSec))
		{
			m_Enemies.push_back(new Enemy(m_Statuses[0]));
			m_Statuses.erase(m_Statuses.begin());
			m_EnemyCreateCount--;
		}
	}
	for (auto& enemy : m_Enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Render()
{
	for (auto& enemy : m_Enemies)
	{
		enemy->Render();
	}
}


bool EnemyManager::CanAppear(int appeartimesec)
{
	int appearFrame = appeartimesec * 60;
	return m_AppearCount >= appearFrame;
}


void EnemyManager::LoadDate(const char* fileName)
{
	Enemy::Status status;

	// ファイル読み込み関数実行
	ifstream ifs(fileName);
	string str;

	while (getline(ifs, str))
	{
		replace(str.begin(), str.end(), ',', ' ');
		stringstream staggStream(str);

		staggStream >> status.m_AppearTimeSec;
		staggStream >> status.m_PosX;
		staggStream >> status.m_PosY;
		staggStream >> status.m_HP;
		staggStream >> status.m_Item;
		staggStream >> status.m_Type;
		float size;
		switch (status.m_Type)
		{
		case TYPE1:
			size = ENEMY_SIZE;
			break;
		case TYPE2:
			size = ENEMY_SIZE * 2.f;
			break;
		}
		m_pDirectX->InitSquareCustomVertex(status.m_EnemyVertex, status.m_PosX, status.m_PosY, size);

		staggStream >> status.m_MovePattern;

		m_Statuses.push_back(status);
		m_EnemyCreateCount++;
	}
}

