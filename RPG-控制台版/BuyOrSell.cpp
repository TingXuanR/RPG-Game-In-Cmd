#include "stdafx.h"
#include "BuyOrSell.h"
#include "GameMgr.h"

CBuyOrSell::CBuyOrSell() :m_nState(0)
{
	s[0] = { "买物品" };
	s[1] = { "卖物品" };
	s[2] = { "退出吧" };
}


CBuyOrSell::~CBuyOrSell()
{
}

void CBuyOrSell::update()
{
	if (KEY_DOWN(VK_UP))
	{
		m_nState--;
		if (m_nState < 0)
		{
			m_nState = 2;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nState++;
		if (m_nState > 2)
		{
			m_nState = 0;
		}
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		if (m_nState == 0)
		{
			CGameMgr::getInstance()->getShop()->setFromWhere(1);	// 说明来自buyOrsell
			CGameMgr::getInstance()->setState(E_STATE_SHOP);
		}
		else if (m_nState == 1)
		{
			CGameMgr::getInstance()->getSell()->init(m_nNpcId);
			CGameMgr::getInstance()->setState(E_STATE_SELLL);
		}
		else if (m_nState == 2)
		{
			CGameMgr::getInstance()->getShop()->setFromWhere(0);
			CGameMgr::getInstance()->setState(E_STATE_MAP);
		}
		m_nState = 0;
	}
}

void CBuyOrSell::render()
{

	cout << setw(CONSOLE_WIDTH*0.55)<<"************\n";
	for (int i = 0; i < 3;i++)
	{
		cout << setw(CONSOLE_WIDTH*0.47);
		if (i==m_nState)
		{
			Set_Color(GreenBlue);
			cout << " ->" << s[i] << "***" << endl;;
		}
		else 
		{
			Set_Color(LightWhite);
			cout << "***" << s[i] << "***" << endl;;
		}
	}
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.55) << "************\n";
	
}

void CBuyOrSell::setNpcId(int nNpcId)
{
	m_nNpcId = nNpcId;
}
