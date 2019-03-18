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
	for (auto& centerEnemy : m_Enemie)
	{
		centerEnemy.AppearCount++;
	}
	MoveOperation();
}

void GameEnemy::Render()
{
	for (auto& centerEnemy : m_Enemie)
	{
		if (centerEnemy.AppearCount >= centerEnemy.AppearTimeSec * 60)
		{
			m_pDirectX->DrawTexture("GAME_ENEMY_TEX", centerEnemy.Enemy);
		}
	}
}

void GameEnemy::MoveOperation()
{
	for (auto& centerEnemy : m_Enemie)
	{
		D3DXVECTOR2 moveDirection(0.f, 0.f);
		if (centerEnemy.AppearCount >= centerEnemy.AppearTimeSec * 60)
		{
			centerEnemy.MovementChangeCount++;
			switch (centerEnemy.MovePattern)
			{
			case NORMAL:
				moveDirection.y += 1.f;
				EnemyMoveSpeed = 4.f;
				break;
			case NORMAL2:
				if (centerEnemy.MovementChange)
				{
					moveDirection.y += 2.f;
					moveDirection.x += 1.f;
					EnemyMoveSpeed = 4.f;
				}
				if (!centerEnemy.MovementChange)
				{
					moveDirection.y += 2.f;
					moveDirection.x -= 1.f;
					EnemyMoveSpeed = 4.f;
				}
				if (centerEnemy.MovementChangeCount == 30)
				{
					switch (centerEnemy.MovementChange)
					{
					case true:
						centerEnemy.MovementChange = false;
						break;
					case false:
						centerEnemy.MovementChange = true;
						break;
					}
					centerEnemy.MovementChangeCount = 0;
				}
				break;
			}
			//単位ベクトルを求める関数
			D3DXVec2Normalize(&moveDirection, &moveDirection);
			moveDirection *= EnemyMoveSpeed;
			m_pDirectX->MoveCustomVertex(centerEnemy.Enemy, moveDirection);
		}
	}
}

void GameEnemy::LoadDate(const char* fileName)
{
	FILE *fp;
	char data[4];
	int csvData = 0, i = 0, csvX = 0, csvY = 0;

	if ((fopen_s(&fp, fileName, "r")) != 0)
	{
		exit(1);
	}

	while ((csvData = getc(fp)) != EOF)
	{
		if (isdigit(csvData))
		{
			data[i] = (char)csvData;
			i++;
		}
		else
		{
			data[i] = '\0';
			switch (csvX)
			{
			case APPEARTIME:
				m_EnemyData.AppearTimeSec = atoi(data);
				break;
			case POSX:
				m_EnemyData.X = atoi(data);
				break;
			case POSY:
				m_EnemyData.Y = atoi(data);
				break;
			case HP:
				m_EnemyData.HP = atoi(data);
				break;
			case ITEM:
				m_EnemyData.Item = atoi(data);
				break;
			case TYPE:
				m_EnemyData.Type = atoi(data);
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
				m_EnemyData.MovePattern = atoi(data);
				break;
			}
		

			csvX++;
			i = 0;
			if (csvX == MOVEPATTERN +1) {
				csvY++;
				csvX = 0;
				m_Enemie.push_back(m_EnemyData);
			}
		}
	}
	fclose(fp);
}
