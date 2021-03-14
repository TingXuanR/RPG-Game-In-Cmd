#pragma once
#include "DataClass.h"
class CConfigMgr
{
public:
	
	~CConfigMgr();
	static CConfigMgr* getInstance();
	static void destroy();
	SYN_THE_SIZE_READONLY(CItemDtMgr*, m_pItemDtMgr, ItemDtMgr);
	SYN_THE_SIZE_READONLY(CLevelDtMgr*, m_pLevelDtMgr, LevelDtMgr);
	SYN_THE_SIZE_READONLY(CRoleDtMgr*, m_pRoleDtMgr, RoleDtMgr);
	SYN_THE_SIZE_READONLY(CNpcDtMgr*, m_pNpcDtMgr, NpcDtMgr);
	SYN_THE_SIZE_READONLY(CEnemyDtMgr*, m_pEnemyDtMgr, EnemyDtMgr);
	SYN_THE_SIZE_READONLY(CMagicDtMgr*, m_pMagicMgr, MagicDtMgr);
	SYN_THE_SIZE_READONLY(CMissionDtMgr*, m_pMissionDtMgr, MissionDtMgr);
	SYN_THE_SIZE_READONLY(CRewardDtMgr*, m_pRewardDtMgr, RewardDtMgr);
private:
	CConfigMgr();
	static CConfigMgr* m_pInstance;
};

