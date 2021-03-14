#pragma once
#include "GameMenu.h"
#include "GameMap.h"
#include "RoleSel.h"
#include "NpcMgr.h"
#include "Shop.h"
#include "Fight.h"
#include "Pack.h"
#include "Equipment.h"
#include "Player.h"
#include "MissionMgr.h"
#include "BuyOrSell.h"
#include "Sell.h"
#include "Stronger.h"
#include "PackChoose.h"
class CGameMgr
{
public:
	
	~CGameMgr();
	void update();
	void render(); // 放到SYN_THE_SIZE后面则为私有方法
	static CGameMgr* getInstance();
	static void destroy();

	SYN_THE_SIZE(int, m_nState, State);
	SYN_THE_SIZE(CGameMenu*, m_pGameMenu, GameMenu);
	SYN_THE_SIZE(CGameMap*, m_pGameMap, GameMap);
	SYN_THE_SIZE(CRoleSel*, m_pRoleSel, RoleSel);
	SYN_THE_SIZE_READONLY(CShop*, m_pShop, Shop);
	SYN_THE_SIZE_READONLY(CFight*, m_pFight, Fight);
	SYN_THE_SIZE_READONLY(CPack*, m_pPack, Pack);
	SYN_THE_SIZE_READONLY(CEquipment*, m_pEquipment, Equipment);
	SYN_THE_SIZE_READONLY(CMissionMgr*, m_pMissionMgr, MissionMgr);
	SYN_THE_SIZE_READONLY(CBuyOrSell*, m_pBuyOrSell, BuyOrSell);
	SYN_THE_SIZE_READONLY(CSell*, m_pSell, Sell);
	SYN_THE_SIZE_READONLY(CStronger*, m_pStronger, Stronger);
	
	SYN_THE_SIZE_READONLY(CPackChoose*, m_pPackChoose, PackChoose);
private:
	CGameMgr();
	static CGameMgr* m_pInstance;
};
