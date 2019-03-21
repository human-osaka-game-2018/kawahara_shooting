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
	for (auto& centerEnemy : m_Enemies)
	{
		centerEnemy.AppearCount++;
	}
	MoveOperation();
}

void GameEnemy::Render()
{
	for (auto& infoEnemy : m_Enemies)
	{
		if (OverTheTimeLimit(infoEnemy))
		{
			m_pDirectX->DrawTexture("GAME_ENEMY_TEX", infoEnemy.Enemy);
		}
	}
}

bool GameEnemy::OverTheTimeLimit(InfoEnemy enemies)
{
	if (enemies.AppearCount >= enemies.AppearTimeSec * 60)
	{
		return true;
	}
	return false;
}

void GameEnemy::MoveOperation()
{
	for (auto& infoEnemy : m_Enemies)
	{
		D3DXVECTOR2 moveDirection(0.f, 0.f);
		if (OverTheTimeLimit(infoEnemy))
		{
			infoEnemy.MovementChangeCount++;
			switch (infoEnemy.MovePattern)
			{
			case NORMAL:
				moveDirection.y += 1.f;
				m_EnemyMoveSpeed = 4.f;
				break;
			case NORMAL2:
				if (infoEnemy.m_MovementChange)
				{
					moveDirection.y += 2.f;
					moveDirection.x += 1.f;
					m_EnemyMoveSpeed = 4.f;
				}
				if (!infoEnemy.m_MovementChange)
				{
					moveDirection.y += 2.f;
					moveDirection.x -= 1.f;
					m_EnemyMoveSpeed = 4.f;
				}
				if (infoEnemy.MovementChangeCount == 30)
				{
 					infoEnemy.m_MovementChange = !infoEnemy.m_MovementChange;
					infoEnemy.MovementChangeCount = 0;
				}
				break;
			}
			//単位ベクトルを求める関数
			D3DXVec2Normalize(&moveDirection, &moveDirection);
			moveDirection *= m_EnemyMoveSpeed;
			m_pDirectX->MoveCustomVertex(infoEnemy.Enemy, moveDirection);
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
				switch (m_EnemyData.Type)
				{
				case NORMAL:
					m_pDirectX->InitSquareCustomVertex(m_EnemyData.Enemy, m_EnemyData.X, m_EnemyData.Y, ENEMY_SIZE);
					break;
				case NORMAL2:
					m_pDirectX->InitSquareCustomVertex(m_EnemyData.Enemy, m_EnemyData.X, m_EnemyData.Y, ENEMY_SIZE * 2.f);
					break;
				}
				break;
			case MOVEPATTERN:
				staggStream >> m_EnemyData.MovePattern;
				break;
			}
		}
		m_Enemies.push_back(m_EnemyData);
	}
}
