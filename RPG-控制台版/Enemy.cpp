#include "stdafx.h"
#include "Enemy.h"
#include "ConfigMgr.h"

CEnemy::CEnemy(SEnemyDt* pData)
{
	m_nID = pData->nID;
	MapID = pData->MapID;
	m_nHp = pData->nHp;
	m_nHpBk = m_nHp;
	m_nAck = pData->nAck;
	m_nDfd = pData->nDfd;
	strName = pData->strName;
	m_strPic = pData->strPic;
	//m_nDir = pData->nDir;
	m_nExp = pData->nExp;
	m_nMoney = pData->nMoney;
	m_nSpeed = pData->nSpeed;
	m_pVecData = CConfigMgr::getInstance()->getMagicDtMgr()->getDataByRoleID(pData->nID);
	//int randRow = (CConfigMgr::getInstance()->getLevelDtMgr()->getDataByID(MapID)->nRowSize);
	//int randCol = (CConfigMgr::getInstance()->getLevelDtMgr()->getDataByID(MapID)->nColSize);
	//m_nRow = rand() % (randRow - 3) + 1;
	//m_nCol = rand() % (randCol - 4) + 1;
	
}

CEnemy::CEnemy()
{
}
CEnemy::~CEnemy()
{
}


void CEnemy::moveUp()
{
	m_nRow--;
}

void CEnemy::moveDown()
{
	m_nRow++;
}

void CEnemy::moveLeft()
{
	m_nCol--;
}

void CEnemy::moveRight()
{
	m_nCol++;
}

vector<SMagicDt*> CEnemy::getMagic()
{
	vector<SMagicDt*> pVecMagic;
	for (auto pMagic:m_pVecData)
	{
		if (pMagic->nRoleID<4000)
		{
			pVecMagic.push_back(pMagic);
		}
	}
	return pVecMagic;
}

void CEnemy::useMagic(SMagicDt* pMagic)
{
	m_nAck = pMagic->nAck;
	m_nHp += pMagic->nHp;
}

int CEnemy::getHpBk()
{
	return m_nHpBk;
}

