#include "stdafx.h"
#include "GameMgr.h"
#include "GameMap.h"

CGameMap::CGameMap()
{
	m_pLevelDt = CConfigMgr::getInstance()->getLevelDtMgr()->getDataByID(1001);
	m_pPlayer = new CPlayer();
	m_pPlayer->setRow(m_pLevelDt->nBirthRow);
	m_pPlayer->setCol(m_pLevelDt->nBirthCol);
	m_pNpcMgr = new CNpcMgr();
	m_pEnemyMgr = new CEnemyMgr();	
	m_vecTips.push_back("按E进入装备界面");
	m_vecTips.push_back("按P进入背包界面");
	m_vecTips.push_back("按I查看个人信息");
	m_vecTips.push_back("按M查看个人任务");
}

CGameMap::~CGameMap()
{
	SAFE_DEL(m_pLevelDt);
	SAFE_DEL(m_pPlayer);
	SAFE_DEL(m_pNpcMgr);
}

void CGameMap::check()
{
	CNpc* pNpc = m_pNpcMgr->getNpc(m_pPlayer->getRow(), m_pPlayer->getCol(), m_pLevelDt->nID);
	int nValue = m_pLevelDt->pArrMap[m_pPlayer->getRow()][m_pPlayer->getCol()];
	//检查玩家是否碰墙
	if ( nValue == 1)
	{
		m_pPlayer->getBackUp();
		if (m_pPlayer->getPet())
		{
			m_pPlayer->getPet()->getBackUp();
		}
		
	}
	else if (nValue > 1000) // 切换地图
	{
		changeMap(nValue);
	}
	else if (pNpc) //碰到NPC
	{
		encounterNpc(pNpc);
	}
	

	int nRow = m_pPlayer->getRow();
	int nCol = m_pPlayer->getCol();

	if (m_pEnemyMgr->getEnemy(nRow, nCol)) //进入战斗界面
	{
		if (nRow == m_pEnemyMgr->getEnemy(nRow, nCol)->getRow() && nCol == m_pEnemyMgr->getEnemy(nRow, nCol)->getCol())
		{
			CGameMgr::getInstance()->getFight()->init(m_pEnemyMgr->getEnemy(nRow, nCol), m_pPlayer);
			CGameMgr::getInstance()->setState(E_STATE_FIGHT);
		}
	}
	
}

void CGameMap::creatEnemies()
{
	m_pEnemyMgr->createEnemies(m_pLevelDt->nID);
}

void CGameMap::changeMap(int nMapID)
{
	m_pLevelDt = CConfigMgr::getInstance()->getLevelDtMgr()->getDataByID(nMapID);
	m_pPlayer->setPosition(m_pLevelDt->nBirthRow, m_pLevelDt->nBirthCol);
	if (m_pPlayer->getPet())
	{
		m_pPlayer->getPet()->setPosition(m_pLevelDt->nBirthRow, m_pLevelDt->nBirthCol);
	}
	//先释放前一关的敌人,再重新生成.
	m_pEnemyMgr->release();
	creatEnemies();
}

void CGameMap::encounterNpc(CNpc* pNpc)
{
	CGameMgr::getInstance()->getShop()->getItemsByNpcID(pNpc->getID());
	m_pPlayer->getBackUp();
	if (m_pPlayer->getPet())
	{
		m_pPlayer->getPet()->getBackUp();
	}
	if (pNpc->getID() < 5005)
	{
		CGameMgr::getInstance()->getBuyOrSell()->setNpcId(pNpc->getID());
		CGameMgr::getInstance()->setState(E_STATE_BUYORSELLL);
	}
	else if (pNpc->getID() == 5005) // 碰到任务NPC进入任务选择界面
	{
		CGameMgr::getInstance()->setState(E_STATE_MISSION);
	}
	else if (pNpc->getID() == 5006) // 碰到铸造师进入铸造界面
	{
		CGameMgr::getInstance()->getStronger()->init();
		CGameMgr::getInstance()->setState(E_STATE_STRONGER);
	}
}

void CGameMap::update()
{
	if (m_pEnemyMgr->getDataSize()==0)
	{
		m_pEnemyMgr->createEnemies(m_pLevelDt->nID);
	}
	m_pPlayer->update();
	m_pEnemyMgr->update();
	CGameMap::check();
}

void CGameMap::render()
{
	cout << setw(CONSOLE_WIDTH*0.47) << "当前所在地：";
	Set_Color(LightWhite);
	cout <<m_pLevelDt->strName << endl;

	//cout << setw(CONSOLE_WIDTH*0.65)<<"帮助:按E进入装备界面,按P进入背包界面,按i查看个人信息，" << endl;

	for (int i = 0; i < m_pLevelDt->nRowSize; i++)
	{
		cout << setw(CONSOLE_WIDTH*0.3); 
		for (int j = 0; j < m_pLevelDt->nColSize; j++)
		{
			
			if (1 == m_pLevelDt->pArrMap[i][j])
			{
				Set_Color(LightWhite);
				cout << "■";
			}
			else if (m_pPlayer->getRow() == i && m_pPlayer->getCol() == j)
			{
				Set_Color(GreenBlue);
				m_pPlayer->render();
				Set_Color(LightWhite);
			}
			else if (m_pPlayer->getPet() && m_pPlayer->getPet()->nRow == i && m_pPlayer->getPet()->nCol == j)
			{
				Set_Color(PaleGreen);
				cout << m_pPlayer->getPet()->strPic;
				Set_Color(LightWhite);
			}
			else if (m_pNpcMgr->getNpc(i, j, m_pLevelDt->nID))
			{
				Set_Color(LightYellow);
				cout << m_pNpcMgr->getNpc(i, j, m_pLevelDt->nID)->getPic();
				Set_Color(LightWhite);
			}
			else if (m_pEnemyMgr->getEnemy(i, j))
			{
				Set_Color(LightRed);
				cout << m_pEnemyMgr->getEnemy(i, j)->getPic();
				Set_Color(LightWhite);
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	Set_Color(PaleGreen);
	for (int i = 0; i < m_vecTips.size(); i++)
	{
	cout << setw(CONSOLE_WIDTH*0.5) << m_vecTips[i] << endl;
	}
	Set_Color(White);
}

CPlayer* CGameMap::getPlayer()
{
	return m_pPlayer;
}

CEnemyMgr* CGameMap::getEnemyMgr()
{
	return m_pEnemyMgr;
}

SLevelDt* CGameMap::getLevelDt()
{
	return m_pLevelDt;
}
//template <class T>
//void CGameMap::checkEnemyCollision(T* t)
//{
//
//}