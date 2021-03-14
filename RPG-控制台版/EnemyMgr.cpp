#include "stdafx.h"
#include "EnemyMgr.h"
#include "ConfigMgr.h"
#include "GameMgr.h"
CEnemyMgr::CEnemyMgr() :m_nTimer(0)
{
}


CEnemyMgr::~CEnemyMgr()
{
	SAFE_DEL_VEC(m_pVecData);
}

void CEnemyMgr::createEnemies(int mapId)
{
	vector<SEnemyDt*> pData = CConfigMgr::getInstance()->getEnemyDtMgr()->getAllData();
	int* BirthPoint = new int[6];
	BirthPoint = CGameMgr::getInstance()->getGameMap()->getLevelDt()->arrEnemyBirth;
	int* StepLength = new int[3];
	StepLength = CGameMgr::getInstance()->getGameMap()->getLevelDt()->arrEnemyStep;
	int* Dirs = CGameMgr::getInstance()->getGameMap()->getLevelDt()->arrEnemyDir;
	for (SEnemyDt* enemyDt : pData)
	{
		if (enemyDt->MapID == mapId)
		{
			for (int i = 0; i < 3; i++)	// 创建三个敌人
			{
				CEnemy* enemy = new CEnemy(enemyDt);
				enemy->setNum(i);
				if (i == 0)
				{
					enemy->setRow(BirthPoint[0]);
					enemy->setCol(BirthPoint[1]);
				}
				else
				{
					enemy->setRow(BirthPoint[i * 2]);
					enemy->setCol(BirthPoint[i * 2 + 1]);
				}
				enemy->setDir(Dirs[i]);
				enemy->setRowBk(enemy->getRow());
				enemy->setColBk(enemy->getCol());
				enemy->setBirthRow(enemy->getRow());
				enemy->setBirthCol(enemy->getCol());
				enemy->setStep(StepLength[i]);
				enemy->setStepBk(StepLength[i]);
				m_pVecData.push_back(enemy);
			}

		}
	}
}



CEnemy* CEnemyMgr::getEnemy(int row, int col)
{
	for (CEnemy* enemy : m_pVecData)
	{
		if (enemy->getRow() == row && enemy->getCol() == col)
		{
			return enemy;
		}
	}
	return nullptr;
}

void CEnemyMgr::deleteEnemy(int row, int col)
{
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		if (m_pVecData[i]->getRow() == row && m_pVecData[i]->getCol() == col)
		{
			m_pVecData.erase(m_pVecData.begin() + i);
		}
	}
}

int CEnemyMgr::getDataSize()
{
	return m_pVecData.size();
}

void CEnemyMgr::release()
{
	for (int i = m_pVecData.size() - 1; i >= 0; i--)
	{
		m_pVecData.erase(m_pVecData.begin() + i);
	}
}

void reverseDir(CEnemy* pEnemy)
{
	if (pEnemy->getDir() == 0)	// 0-Up, 1-Down, 2-Left, 3-Right
	{
		pEnemy->setDir(1);
	}
	else if (pEnemy->getDir() == 1)
	{
		pEnemy->setDir(0);
	}
	else if (pEnemy->getDir() == 2)
	{
		pEnemy->setDir(3);
	}
	else if (pEnemy->getDir() == 3)
	{
		pEnemy->setDir(2);
	}
	//pEnemy->setRow(pEnemy->getRowBk());
	//pEnemy->setCol(pEnemy->getColBk());
}

void check(CEnemy* pEnemy)
{
	/*int nMapRowSize = CGameMgr::getInstance()->getGameMap()->getLevelDt()->nRowSize;
	int nMapColSize = CGameMgr::getInstance()->getGameMap()->getLevelDt()->nColSize;*/
	//if (pEnemy->getRow() == 0 || pEnemy->getRow() == nMapRowSize - 1) //撞墙
	//{
	//	reverseDir(pEnemy);
	//}
	//else if (pEnemy->getCol() == 0 || pEnemy->getCol() == nMapColSize - 1)
	//{
	//	reverseDir(pEnemy);
	//}
	if (pEnemy->getStep() == 0)
	{
		pEnemy->setStep(pEnemy->getStepBk());
		reverseDir(pEnemy);
	}
	else if (pEnemy->getRow() == pEnemy->getBirthRow() && pEnemy->getCol() == pEnemy->getBirthCol()) //回出生点
	{
		pEnemy->setStep(pEnemy->getStepBk());
		reverseDir(pEnemy);
	}
}

void CEnemyMgr::update()
{
	m_nTimer++;
	if (m_pVecData.size() && m_nTimer >= m_pVecData[0]->getSpeed())
	{

		for (int i = 0; i < m_pVecData.size(); i++)
		{
			/*m_pVecData[i]->setRowBk(m_pVecData[i]->getRow());
			m_pVecData[i]->setColBk(m_pVecData[i]->getCol());*/
			if (m_pVecData[i]->getDir() == 0)
			{
				m_pVecData[i]->moveUp();
			}
			else if (m_pVecData[i]->getDir() == 1)
			{
				m_pVecData[i]->moveDown();
			}
			else if (m_pVecData[i]->getDir() == 2)
			{
				m_pVecData[i]->moveLeft();
			}
			else if (m_pVecData[i]->getDir() == 3)
			{
				m_pVecData[i]->moveRight();
			}
			//if (m_pVecData[i]->getNum() == 0) // 第一个向右走,碰障碍物后反方向
			//{

			//	if (m_pVecData[i]->getDir() == 1)
			//	{
			//		m_pVecData[i]->moveRight();
			//	}
			//	else
			//	{
			//		m_pVecData[i]->moveLeft();
			//	}
			//	
			//}
			//else if (m_pVecData[i]->getNum() == 1) //第二个向下走
			//{

			//	if (m_pVecData[i]->getDir() == 1)
			//	{
			//		m_pVecData[i]->moveDown();
			//	}
			//	else
			//	{
			//		m_pVecData[i]->moveUp();
			//	}
			//}
			//else if (m_pVecData[i]->getNum() == 2) //第三个向上走
			//{

			//	if (m_pVecData[i]->getDir() == 1)
			//	{
			//		m_pVecData[i]->moveUp();
			//	}
			//	else
			//	{
			//		m_pVecData[i]->moveDown();
			//	}
			//}
			m_pVecData[i]->setStep(m_pVecData[i]->getStep() - 1);	// 每走一步，可走的步数便减1
			check(m_pVecData[i]);
		}
		m_nTimer = 0;
	}

}


//template <class T>
//void CEnemyMgr::checkEnemyCollision(T* t)
//{
//	for (int i = 0; i < m_pVecData.size(); i++)
//	{
//		if (m_pVecData[i]->getRow == t->getRow() && m_pVecData[i] == t->getCol())
//		{
//			if (m_pVecData[i]->getDir == 0)
//			{
//				m_pVecData[i]->setDir(1);
//			}
//			else if (m_pVecData[i]->getDir == 1)
//			{
//				m_pVecData[i]->setDir(0);
//			}
//		}
//	}
//}