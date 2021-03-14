#include "stdafx.h"
#include "Sell.h"
#include "GameMgr.h"

CSell::CSell() :m_nState(0), m_nTypeId(-1)
{
	
}


CSell::~CSell()
{
	SAFE_DEL_VEC(m_pVecItems);
	SAFE_DEL(m_pPlayer);
}

void CSell::update()
{
	MOVE_UP_DOWN(m_pVecItems, m_nState);
	if (KEY_DOWN(VK_RETURN))
	{
		if (m_pVecItems.size())
		{
			bool flag = false;	// �����Ʒ�����Ƿ�Ϊ1, ��1���ʾ��Ʒ�����Ƴ���
			if (m_pVecItems[m_nState]->nCount == 1)
			{
				flag = true;
			}
			CGameMgr::getInstance()->getGameMap()->getPlayer()->setMoney(m_pVecItems[m_nState]->nPrice/10 + m_pPlayer->getMoney());
			m_pPlayer->removeItem(m_pVecItems[m_nState]);
			if (flag) // ����±�δ��ԭ�����⡣
			{
				if (m_nState == 0)
				{
					m_nState = 0;
				}
				else
				{
					m_nState = m_nState == m_pVecItems.size() - 1 ? m_nState - 1 : m_nState;
				}
			}
		}
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setState(E_STATE_BUYORSELLL);
		m_nState = 0;
	}
}

void CSell::render()
{
	m_pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
	m_pVecItems = m_pPlayer->sendItems(m_nTypeId);

	cout << setw(CONSOLE_WIDTH*0.75) << "-----------------------��ѡ��Ҫ��������Ʒ---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.5) << "NAME\tACK\tDFD\tHP\tMP\tPRICE\tPIC\tCOUNT  " << endl;
	for (int i = 0; i < m_pVecItems.size(); ++i)
	{
		cout << setw(CONSOLE_WIDTH*0.19)<<i+1<<":";
		SItemDt* pDt = m_pVecItems[i];
		if (m_nState == i)
		{
			Set_Color(GreenBlue);
			cout << "->";
		}
		else
		{
			Set_Color(LightWhite);
			cout << "  ";
		}
		cout << pDt->strName << "\t" << pDt->nAck << "\t" << pDt->nDef << "\t" << pDt->nHp << "\t" << pDt->nMp << "\t"
			<< pDt->nPrice/10 << "\t" << pDt->strPic << "\t" << pDt->nCount << endl;
		Set_Color(White);
	}
	
	cout << setw(CONSOLE_WIDTH*0.75) << "--------------------------------------------------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.3) << " ��Ŀǰ�Ľ�Ǯ����"; Set_Color(LightYellow); cout << m_pPlayer->getMoney() << endl;
	Set_Color(White);
}

void CSell::init(int nNpcId)
{
	m_nTypeId = nNpcId;
	//m_pVecItems = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendItems(m_nTypeId);
}
