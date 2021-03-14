#include "stdafx.h"
#include "ConfigMgr.h"

CConfigMgr* CConfigMgr::m_pInstance = nullptr;

CConfigMgr* CConfigMgr::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CConfigMgr();
	}
	return m_pInstance;
}
CConfigMgr::CConfigMgr()
{
	m_pLevelDtMgr = new CLevelDtMgr();
	m_pLevelDtMgr->loadFile("Configs/LevelDt.txt");
	m_pRoleDtMgr = new CRoleDtMgr();
	m_pRoleDtMgr->loadFile("Configs/RoleDt.txt");
	m_pNpcDtMgr = new CNpcDtMgr();
	m_pNpcDtMgr->loadFile("Configs/NpcDt.txt");
	m_pItemDtMgr = new CItemDtMgr();
	m_pItemDtMgr->loadFile("Configs/ItemDt.txt");
	m_pEnemyDtMgr = new CEnemyDtMgr();
	m_pEnemyDtMgr->loadFile("Configs/EnemyDt.txt");
	m_pMagicMgr = new CMagicDtMgr();
	m_pMagicMgr->loadFile("Configs/MagicDt.txt");
	m_pMissionDtMgr = new CMissionDtMgr();
	m_pMissionDtMgr->loadFile("Configs/MissionDt.txt");
	m_pRewardDtMgr = new CRewardDtMgr();
	m_pRewardDtMgr->loadFile("Configs/RewardDt.txt");

}

CConfigMgr::~CConfigMgr()
{
	SAFE_DEL(m_pLevelDtMgr);
	SAFE_DEL(m_pRoleDtMgr);
	SAFE_DEL(m_pNpcDtMgr);
	SAFE_DEL(m_pItemDtMgr);
	SAFE_DEL(m_pEnemyDtMgr);
	SAFE_DEL(m_pMagicMgr); 
	SAFE_DEL(m_pMissionDtMgr);
	SAFE_DEL(m_pRewardDtMgr);
}

void CConfigMgr::destroy()
{
	SAFE_DEL(m_pInstance);
}