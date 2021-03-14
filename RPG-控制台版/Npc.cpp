#include "stdafx.h"
#include "Npc.h"


CNpc::CNpc(SNpcDt* pData)
{
	m_nID = pData->nID;
	m_nMapID = pData->nMapID;
	m_nRow = pData->nRow;
	m_nCol = pData->nCol;
	m_strName = pData->strName;
	m_strPic = pData->strPic;
}


CNpc::~CNpc()
{
}
