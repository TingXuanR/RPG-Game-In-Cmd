#include "stdafx.h"
#include "RoleSel.h"
#include "ConfigMgr.h"
#include "GameMgr.h"

CRoleSel::CRoleSel() :m_nState(E_ROLE_ZHANSHI)
{
	m_pVecData = CConfigMgr::getInstance()->getRoleDtMgr()->getAllData();
}


CRoleSel::~CRoleSel()
{
	SAFE_DEL_VEC(m_pVecData);
}

void CRoleSel::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nState--;
		if (m_nState < E_ROLE_ZHANSHI)
		{
			m_nState = E_ROLE_SHESHOU;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nState++;
		if (m_nState > E_ROLE_SHESHOU)
		{
			m_nState = E_ROLE_ZHANSHI;
		}
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		CGameMgr::getInstance()->getGameMap()->getPlayer()->initConfig(m_pVecData[m_nState]);
		CGameMgr::getInstance()->setState(E_STATE_MAP);
	}
}

void CRoleSel::render()
{
	cout << setw(CONSOLE_WIDTH*0.65) << "----------------½ÇÉ«Ñ¡Ôñ----------------" << endl;
	cout << setw(CONSOLE_WIDTH*0.5) << "ID\tHP\tACK\tNAME\tPic" << endl;
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		cout << setw(CONSOLE_WIDTH*0.35);
		SRoleDt* pDt = m_pVecData[i];
		if (m_nState == i)
		{
			Set_Color(GreenBlue);
			cout << "->";
		}
		else
		{
			Set_Color(White);
			cout << "  ";
		}
		cout << pDt->nID << "\t" << pDt->nHp << "\t" << pDt->nAck
			<< "\t" << pDt->strName << "\t" << pDt->strPic << endl;
		if (i == m_pVecData.size() - 1)	Set_Color(White);
	}
}
