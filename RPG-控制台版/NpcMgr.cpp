#include "stdafx.h"
#include "NPCMgr.h"
#include "ConfigMgr.h"

CNpcMgr::CNpcMgr()
{
	createAllNpc();
}


CNpcMgr::~CNpcMgr()
{
	SAFE_DEL_VEC(m_VecData);
}

void CNpcMgr::createAllNpc()
{
	int nSize = CConfigMgr::getInstance()->getNpcDtMgr()->getSize();
	for (int i = 0; i < nSize; i++)
	{
		SNpcDt* pData = CConfigMgr::getInstance()->getNpcDtMgr()->getDataByIndex(i);
		CNpc* pNpc = new CNpc(pData);
		m_VecData.push_back(pNpc);
	}
}

CNpc* CNpcMgr::getNpc(int nRow, int nCol, int nMapID)
{
	for (CNpc* pNpc : m_VecData)
	{
		if (pNpc->getRow() == nRow && pNpc->getCol() == nCol && pNpc->getMapID() == nMapID)
		{
			return pNpc;
		}
	}
	return nullptr;
}
