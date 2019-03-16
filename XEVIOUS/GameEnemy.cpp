#include"GameEnemy.h"


GameEnemy::GameEnemy()
{
	m_pDirectX = DirectX::GetInstance();
}

GameEnemy::~GameEnemy()
{

}


void GameEnemy::Update()
{

}

void GameEnemy::Render()
{
	for (auto& centerEnemy : m_EnemyPos)
	{
		if (centerEnemy.count >= centerEnemy.AppearTime * 60)
		{
			m_pDirectX->DrawTexture("GAME_ENEMY_TEX", centerEnemy.Enemy);
		}
		centerEnemy.count++;
	}
}

void GameEnemy::LoadDate(const char* fileName)
{
	FILE *fp;
	char data[4];
	int c, i = 0, x = 0, y = 0;

	if ((fopen_s(&fp, fileName, "r")) != 0)
	{
		exit(1);
	}

	while ((c = getc(fp)) != EOF)
	{
		if (isdigit(c))
		{
			data[i] = (char)c;
			i++;
		}
		else
		{
			data[i] = '\0';
			if (x == APPEARTIME)
			{
				m_EnemyData.AppearTime = atoi(data);
			}
			if (x == POSX)
			{
				m_EnemyData.x = atoi(data);
			}
			if (x == POSY)
			{
				m_EnemyData.y = atoi(data);
			}
			if (x == HP)
			{
				m_EnemyData.HP = atoi(data);
			}
			if (x == ITEM)
			{
				m_EnemyData.Item = atoi(data);
			}
			if (x == TYPE)
			{
				switch (m_EnemyData.Type)
				{
				case 0:
					m_pDirectX->InitSquareCustomVertex(m_EnemyData.Enemy, m_EnemyData.x, m_EnemyData.y,32);
					m_EnemyData.Type = atoi(data);
					break;
				case 1:
					m_EnemyData.Type = atoi(data);
					break;
				}
			}

			x++;
			i = 0;
			if (x == 6) {
				y++;
				x = 0;
				m_EnemyPos.push_back(m_EnemyData);
			}
		}
	}
	fclose(fp);
}
