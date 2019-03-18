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
	MoveOperation();
}

void GameEnemy::Render()
{
	for (auto& centerEnemy : m_Enemie)
	{
		if (centerEnemy.AppearCount >= centerEnemy.AppearTime * 60)
		{
			m_pDirectX->DrawTexture("GAME_ENEMY_TEX", centerEnemy.Enemy);
		}
		centerEnemy.AppearCount++;
	}
}

void GameEnemy::MoveOperation()
{
	for (auto& centerEnemy : m_Enemie)
	{
		D3DXVECTOR2 moveDirection(0.f, 0.f);
		if (centerEnemy.AppearCount >= centerEnemy.AppearTime * 60)
		{
			centerEnemy.MovementChangeCount++;
			switch (centerEnemy.MovePattern)
			{
			case NORMAL:
				moveDirection.y += 1.f;
				ENEMY_MOVE_SPEED = 4.f;
				break;
			case NORMAL2:
				if (centerEnemy.MovementChange)
				{
					moveDirection.y += 2.f;
					moveDirection.x += 1.f;
					ENEMY_MOVE_SPEED = 4.f;
				}
				if (!centerEnemy.MovementChange)
				{
					moveDirection.y += 2.f;
					moveDirection.x -= 1.f;
					ENEMY_MOVE_SPEED = 4.f;
				}
				if (centerEnemy.MovementChangeCount == 30)
				{
					switch (centerEnemy.MovementChange)
					{
					case true:
						centerEnemy.MovementChange = false;
						centerEnemy.MovementChangeCount = 0;
						break;
					case false:
						centerEnemy.MovementChange = true;
						centerEnemy.MovementChangeCount = 0;
						break;
					}
				}
				break;
			}
			//単位ベクトルを求める関数
			D3DXVec2Normalize(&moveDirection, &moveDirection);
			moveDirection *= ENEMY_MOVE_SPEED;
			m_pDirectX->MoveCustomVertex(centerEnemy.Enemy, moveDirection);
		}
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
				m_EnemyData.Type = atoi(data);
				switch (m_EnemyData.Type)
				{
				case NORMAL:
					m_pDirectX->InitSquareCustomVertex(m_EnemyData.Enemy, m_EnemyData.x, m_EnemyData.y,32);
					break;
				case NORMAL2:
					m_pDirectX->InitSquareCustomVertex(m_EnemyData.Enemy, m_EnemyData.x, m_EnemyData.y, 64);
					break;
				}
			}
			if (x == MOVEPATTERN)
			{
				m_EnemyData.MovePattern = atoi(data);
			}

			x++;
			i = 0;
			if (x == MOVEPATTERN +1) {
				y++;
				x = 0;
				m_Enemie.push_back(m_EnemyData);
			}
		}
	}
	fclose(fp);
}
