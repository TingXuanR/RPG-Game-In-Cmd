#include "stdafx.h"
#include "GameMgr.h"

CGameMgr* CGameMgr::m_pInstance = nullptr;
CGameMgr::CGameMgr() :m_nState(E_STATE_MENU)
{
	m_pGameMenu = new CGameMenu();
	m_pGameMap = new CGameMap();
	m_pRoleSel = new CRoleSel();
	m_pShop = new CShop();
	m_pFight = new CFight();
	m_pPack = new CPack();
	m_pEquipment = new CEquipment();
	m_pMissionMgr = new CMissionMgr();
	m_pBuyOrSell = new CBuyOrSell();
	m_pSell = new CSell();
	m_pStronger = new CStronger();
	m_pPackChoose = new CPackChoose();

}

CGameMgr* CGameMgr::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CGameMgr();
	}
	return m_pInstance;
}

void CGameMgr::destroy()
{
	SAFE_DEL(m_pInstance);
}

CGameMgr::~CGameMgr()
{
	SAFE_DEL(m_pGameMenu);
	SAFE_DEL(m_pGameMap);
	SAFE_DEL(m_pRoleSel);
	SAFE_DEL(m_pShop);
	SAFE_DEL(m_pFight);
	SAFE_DEL(m_pPack);
	SAFE_DEL(m_pEquipment);
	SAFE_DEL(m_pMissionMgr); 
	SAFE_DEL(m_pBuyOrSell);
	SAFE_DEL(m_pSell);
	SAFE_DEL(m_pStronger);
	SAFE_DEL(m_pPackChoose);
}

void CGameMgr::update()
{
	if (E_STATE_MENU == m_nState)
	{
		m_pGameMenu->update();
	}
	else if (E_STATE_ROLE == m_nState)
	{
		m_pRoleSel->update();
	}
	else if (E_STATE_MAP == m_nState)
	{
		m_pGameMap->update();
	}
	else if (E_STATE_SHOP == m_nState)
	{
		m_pShop->update();
	}
	else if (E_STATE_FIGHT == m_nState)
	{
		m_pFight->update();
	}
	else if (E_STATE_PACK == m_nState)
	{
		m_pPack->update();
	}
	else if (E_STATE_EQUIPMENT == m_nState)
	{
		m_pEquipment->update();
	}
	else if (E_STATE_MISSION == m_nState)
	{
		m_pMissionMgr->update();
	}
	else if (E_STATE_BUYORSELLL == m_nState)
	{
		m_pBuyOrSell->update();
	}
	else if (E_STATE_SELLL == m_nState)
	{
		m_pSell->update();
	}
	else if (E_STATE_STRONGER == m_nState)
	{
		m_pStronger->update();
	}
	else if (E_STATE_PACKCHOOSE == m_nState)
	{
		m_pPackChoose->update();
	}
}

void CGameMgr::render()
{
	if (E_STATE_MENU == m_nState)
	{
		m_pGameMenu->render();
	}
	else if (E_STATE_ROLE == m_nState)
	{
		m_pRoleSel->render();
	}
	else if (E_STATE_MAP == m_nState)
	{
		m_pGameMap->render();
	}
	else if (E_STATE_SHOP == m_nState)
	{
		m_pShop->render();
	}
	else if (E_STATE_FIGHT == m_nState)
	{
		m_pFight->render();
	}
	else if (E_STATE_PACK == m_nState)
	{
		m_pPack->render();
	}
	else if (E_STATE_EQUIPMENT == m_nState)
	{
		m_pEquipment->render();
	}
	else if (E_STATE_MISSION == m_nState)
	{
		m_pMissionMgr->render();
	}
	else if (E_STATE_BUYORSELLL == m_nState)
	{
		m_pBuyOrSell->render();
	}
	else if (E_STATE_SELLL == m_nState)
	{
		m_pSell->render();
	}
	else if (E_STATE_STRONGER == m_nState)
	{
		m_pStronger->render();
	}
	else if (E_STATE_PACKCHOOSE == m_nState)
	{
		m_pPackChoose->render();
	}
}


