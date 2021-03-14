#include "stdafx.h"
#include "Pack.h"
#include "GameMgr.h"

CPack::CPack()
{
	m_nIndex = 0;
	m_nFromWhere = 0;
}


CPack::~CPack()
{
	//�ͷű�����Դ
	SAFE_DEL_VEC(m_pVecData);
}

void CPack::update()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		if (m_nFromWhere == 0)
		{
			CGameMgr::getInstance()->setState(E_STATE_PACKCHOOSE);
		}
		else if (m_nFromWhere == 1)
		{
			CGameMgr::getInstance()->setState(E_STATE_FIGHT);
		}
		m_nIndex = 0;
		/*else if (m_nFromWhere == 2)
		{
			CGameMgr::getInstance()->setState(E_STATE_BUYORSELLL);
		}*/
	}
	else if (KEY_DOWN(VK_UP))
	{
		m_nIndex--;
		if (m_nIndex < 0)
		{
			m_nIndex = m_pVecData.size() - 1;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nIndex++;
		if (m_nIndex >= m_pVecData.size())
		{
			m_nIndex = 0;
		}
	}
	else if (KEY_DOWN(VK_D)) //  press d to delete
	{
		bool flag = false;
		if (m_pVecData[m_nIndex]->nCount == 1)  // ��ҩƷ�������Ҫ����һ��
		{
			flag = true;
		}
		CGameMgr::getInstance()->getGameMap()->getPlayer()->removeItem(m_pVecData[m_nIndex]);
		// ɾ������Ҫ����index
		if (flag) //���������item,ɾ�����һ��itemǰ��Ҫ��index����һ��.��Ȼm_pEquipment�����Խ��(size=1, index=1).
		{
			if (m_nIndex == 0)
			{
				m_nIndex = 0;
			}
			else // ����������һ��item��ɾ������index�Ͳ���Ҫ��
			{
				m_nIndex = m_nIndex == m_pVecData.size() - 1 ? m_nIndex - 1 : m_nIndex;
			}
		}
	}
	else if (KEY_DOWN(VK_RETURN))
	{
		if (m_pVecData.size())
		{
			bool flag = false;
			if (m_pVecData[m_nIndex]->nTypeID == 5)
			{
				if (m_pVecData[m_nIndex]->nID == 5004) // ��Ѫҩ
				{
					if (!CGameMgr::getInstance()->getGameMap()->getPlayer()->checkHp())	// ��Ѫʱ�޷�ʹ��ҩƷ
					{
						if (m_pVecData[m_nIndex]->nCount == 1)  // ��ҩƷ�������Ҫ����һ��
						{
							flag = true;
						}
						CGameMgr::getInstance()->getGameMap()->getPlayer()->useItem(m_pVecData[m_nIndex]);
						CGameMgr::getInstance()->getGameMap()->getPlayer()->removeItem(m_pVecData[m_nIndex]);
						if (flag)
						{
							if (m_nIndex == 0)
							{
								m_nIndex = 0;
							}
							else
							{
								m_nIndex = m_nIndex == m_pVecData.size() - 1 ? m_nIndex - 1 : m_nIndex;
							}
						}
					}
				}
				else if (m_pVecData[m_nIndex]->nID == 5005)	// ����ҩ
				{
					if (!CGameMgr::getInstance()->getGameMap()->getPlayer()->checkMp())
					{
						if (m_pVecData[m_nIndex]->nCount == 1)  // ��ҩƷ�������Ҫ����һ��
						{
							flag = true;
						}
						CGameMgr::getInstance()->getGameMap()->getPlayer()->useItem(m_pVecData[m_nIndex]);
						CGameMgr::getInstance()->getGameMap()->getPlayer()->removeItem(m_pVecData[m_nIndex]);
						if (flag)
						{
							if (m_nIndex == 0)
							{
								m_nIndex = 0;
							}
							else
							{
								m_nIndex = m_nIndex == m_pVecData.size() - 1 ? m_nIndex - 1 : m_nIndex;
							}
						}
					}
				}
			}
			else if (m_pVecData[m_nIndex]->nTypeID < 5)
			{
				m_nIndex = 0;
				CGameMgr::getInstance()->getGameMap()->getPlayer()->enterEquipment();
			}
		}
	}
}

void CPack::render()
{
	getAllData();
	//CGameMgr::getInstance()->getGameMap()->getPlayer()->showInfomation();
	if (m_nFromWhere == 1)	// ��ս������ֱ�ӽ��룬ֻ��ӡҩƷ
	{
		printWithCount(m_pVecData);
	}
	else
	{
		if (m_nPackChoose == 0 || m_nPackChoose == 3)
		{
			printWithoutCount(m_pVecData);
		}
		else if (m_nPackChoose == 1 || m_nPackChoose == 2)
		{
			printWithCount(m_pVecData);
		}
	}
}

void CPack::printWithoutCount(vector<SItemDt*> m_pVecData)
{
	Set_Color(White);
	cout <<setw(CONSOLE_WIDTH*0.8)<< "------------------------------������Ʒ------------------------------" << endl;
	cout << setw(CONSOLE_WIDTH*0.55) << "NAME\tTYPEID\tLV\tACK\tDEF\tHP\tMP\tPRICE\tPIC" << endl;
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		cout << setw(CONSOLE_WIDTH*0.21)<<i+1<<":";
		SItemDt* pDt = m_pVecData[i];
		if (i == m_nIndex)
		{
			Set_Color(GreenBlue);
			cout << "->";
		}
		else
		{
			Set_Color(LightWhite);
			cout << "  ";
		}
		cout << pDt->strName << "\t" << pDt->nTypeID << "\t" << pDt->nLv << "\t" << pDt->nAck << "\t" << pDt->nDef << "\t" << pDt->nHp << "\t" << pDt->nMp
			<< "\t" << pDt->nPrice << "\t" <<
			pDt->strPic /*<< pDt->nCount */ << endl;
		Set_Color(White);
	}
}

void CPack::printWithCount(vector<SItemDt*> m_pVecData)
{
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.8) << "-------------------------------������Ʒ-------------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.55) << "NAME\tTYPEID\tLV\tACK\tDEF\tHP\tMP\tPRICE\tCount" << endl;
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		cout << setw(CONSOLE_WIDTH*0.19) << i + 1 << ":";
		SItemDt* pDt = m_pVecData[i];
		if (i == m_nIndex)
		{
			Set_Color(GreenBlue);
			cout << "->";
		}
		else
		{
			Set_Color(LightWhite);
			cout << "  ";
		}
		cout << pDt->strName << "\t" << pDt->nTypeID << "\t" << pDt->nLv << "\t" << pDt->nAck << "\t" << pDt->nDef << "\t" << pDt->nHp << "\t" << pDt->nMp
			<< "\t" << pDt->nPrice << "\t" << pDt->nCount  << endl;
		Set_Color(White);
	}
}

void CPack::getAllData()
{
	if (m_nFromWhere==0)
	{
		if (m_nPackChoose == 0)
		{
			m_pVecData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendEquipmentItem();
		}
		else if (m_nPackChoose == 1)
		{
			m_pVecData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendItems(5003);
		}
		else if (m_nPackChoose == 2)
		{
			m_pVecData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendMaterial();
		}
		else if (m_nPackChoose == 3)
		{
			m_pVecData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendPets(4);
		}
	}
	else if (m_nFromWhere == 1)
	{
		m_pVecData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendItems(5003); // �õ�ҩƷ
	}
}
