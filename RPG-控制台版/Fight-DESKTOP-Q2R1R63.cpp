#include "stdafx.h"
#include "Fight.h"
#include "GameMgr.h"


void CFight::init(CEnemy* pEnemy, CPlayer* pPlayer)
{
	m_pEnemy = pEnemy;
	m_pPlayer = pPlayer;
}
CFight::CFight()
{
	//m_pEnemy = new CEnemy();
}

CFight::~CFight()
{
}

void CFight::update()
{
	m_pPlayer->setBackUp(m_pPlayer->getRowBk(), m_pPlayer->getColBk());
	m_pPlayer->setRow(2);
	m_pPlayer->setCol(0);
	
	m_pEnemy->setRowBk(m_pEnemy->getRow()); m_pEnemy->setColBk(m_pEnemy->getCol());
	m_pEnemy->setRow(2);
	m_pEnemy->setCol(9);
	if (KEY_DOWN(VK_SPACE))
	{
		m_pPlayer->setCol(8);
		int nEmy_HP = m_pEnemy->getHp() - m_pPlayer->getAck();
		m_pEnemy->setHp(nEmy_HP);

		int nPly_HP = m_pPlayer->getHp() - m_pEnemy->getAck() + m_pPlayer->getDfd();
		m_pPlayer->setHp(nPly_HP);

	}

	if (m_pEnemy->getHp() <= 0)
	{
		m_pPlayer->getBackUp();
		CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->deleteEnemy(m_pEnemy->getRowBk(), m_pEnemy->getColBk());
		CGameMgr::getInstance()->setState(E_STATE_MAP);
	}
	else if (m_pPlayer->getHp() <= 0)
	{
		cout << "角色死亡，游戏结束" << endl;
		system("pause");
		exit(0);
	}
}

void CFight::render()
{
	cout << "按回车键进行战斗" << endl;
	cout << "玩家血量：" << m_pPlayer->getHp() << "\t 敌人血量：" << m_pEnemy->getHp()<<endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == m_pPlayer->getRow() && j == m_pPlayer->getCol())
			{
				m_pPlayer->render();
			}
			else if (i == m_pEnemy->getRow() && j == m_pEnemy->getCol())
			{
				cout<<m_pEnemy->getPic();
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}