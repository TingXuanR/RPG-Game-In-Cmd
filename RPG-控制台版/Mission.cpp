#include "stdafx.h"
#include "Mission.h"
#include "GameMgr.h"

CMission::CMission(SMissionDt* pData)
{
	m_nID = pData->nID;
	m_nName = pData->nState; 
	m_nName = pData->strName;
	m_nState = pData->nState;
	m_nDescription = pData->strDescription;
	m_nReceived = 0;
}


CMission::~CMission()
{
}



string CMission::getStateDescription()
{
	if (m_nState == 0)
	{
		return	"δ��ȡ";
	}
	else if (m_nState == 1)
	{
		return	"δ���";
	}
	else if (m_nState == 2)
	{
		return	"�����";
	}
	else if (m_nState == 3)
	{
		return	"����ȡ";
	}
}

//void CMission::judgeMission()
//{
//	switch (m_nID)
//	{
//	case 7001:
//		break;
//	case 7002:
//		break;
//	case 7003:
//		break;
//	case 7004:
//		break;
//	case 7005:
//
//		break;
//	default:
//		break;
//	}
//}
