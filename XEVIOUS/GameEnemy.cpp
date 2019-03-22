#include"GameEnemy.h"
#include <fstream>
#include <string>


#include <iostream>
#include <sstream>
#include <algorithm>


GameEnemy::GameEnemy()
{
	m_pDirectX = DirectX::GetInstance();
}

GameEnemy::~GameEnemy()
{

}


void GameEnemy::Update()
{
	for (auto& status : m_EnemyStatuses)
	{
		status.AppearCount++;
	}
	MoveOperation();
}

void GameEnemy::Render()
{
	for (auto& status : m_EnemyStatuses)
	{
		if (AppearCountIsMoreThan(status))
		{
			m_pDirectX->DrawTexture("GAME_ENEMY_TEX", status.Enemy);
		}
	}
}

bool GameEnemy::AppearCountIsMoreThan(InfoEnemy enemyStatus)
{
	int appearSecond = enemyStatus.AppearTimeSec * 60;
	return enemyStatus.AppearCount >= appearSecond;
}

void GameEnemy::MoveOperation()
{
	for (auto& status : m_EnemyStatuses)
	{
		D3DXVECTOR2 moveDirection(0.f, 0.f);
		if (AppearCountIsMoreThan(status))
		{
			status.MovementChangeCount++;
			switch (status.MovePattern)
			{
			case NORMAL:
				moveDirection.y += 1.f;
				m_EnemyMoveSpeed = 4.f;
				break;
			case NORMAL2:
				moveDirection.y += 2.f;
				m_EnemyMoveSpeed = 4.f;
				if (status.m_MovementChange)
				{
					moveDirection.x += 1.f;
				}
				else
				{
					moveDirection.x -= 1.f;
				}
				if (status.MovementChangeCount == 30)
				{
					status.m_MovementChange = !status.m_MovementChange;
					status.MovementChangeCount = 0;
				}
				break;
			}
			//単位ベクトルを求める関数
			D3DXVec2Normalize(&moveDirection, &moveDirection);
			moveDirection *= m_EnemyMoveSpeed;
			m_pDirectX->MoveCustomVertex(status.Enemy, moveDirection);
		}
	}
}

void GameEnemy::LoadDate(const char* fileName)
{

	// ファイル読み込み関数実行
	std::ifstream ifs(fileName);
	std::string str;
	
	while (getline(ifs, str))
	{
		replace(str.begin(), str.end(), ',', ' ');
		std::stringstream staggStream(str);

		for (int i = 0;i < (MOVEPATTERN + 1);i++)
		{
			switch (i)
			{
			case APPEARTIME:
				staggStream >> m_EnemyData.AppearTimeSec;
				break;
			case POSX:
				staggStream >> m_EnemyData.X;
				break;
			case POSY:
				staggStream >> m_EnemyData.Y;
				break;
			case HP:
				staggStream >> m_EnemyData.HP;
				break;
			case ITEM:
				staggStream >> m_EnemyData.Item;
				break;
			case TYPE:
				staggStream >> m_EnemyData.Type;
				float size;
				switch (m_EnemyData.Type)
				{
				case NORMAL:
					size = ENEMY_SIZE;
					break;
				case NORMAL2:
					size = ENEMY_SIZE * 2.f;
					break;
				}
				m_pDirectX->InitSquareCustomVertex(m_EnemyData.Enemy, m_EnemyData.X, m_EnemyData.Y, size);
				break;
			case MOVEPATTERN:
				staggStream >> m_EnemyData.MovePattern;
				break;
			}
		}
		m_EnemyStatuses.push_back(m_EnemyData);
	}
}
