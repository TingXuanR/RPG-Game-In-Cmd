#include "stdafx.h"
#include "Equipment.h"
#include "GameMgr.h"

CEquipment::CEquipment()
{
	m_nIndex = 0;
}


CEquipment::~CEquipment()
{
	SAFE_DEL_VEC(m_pVevData);
}



void CEquipment::wearOnEquipment(SItemDt* pItem)
{
	if (pItem->nTypeID == 0)
	{
		m_pEquiment[0] = pItem;
	}
	else if (pItem->nTypeID == 1)
	{
		m_pEquiment[1] = pItem;
	}
	else if (pItem->nTypeID == 2)
	{
		m_pEquiment[2] = pItem;
	}
	else if (pItem->nTypeID == 3)
	{
		m_pEquiment[3] = pItem;

	}
	else if (pItem->nTypeID == 4)
	{
		m_pEquiment[4] = pItem;
	}
	CGameMgr::getInstance()->getGameMap()->getPlayer()->useItem(pItem);
	if (pItem->nCount == 1) //如果有两个item,删掉最后一个item前需要让index回退一个.不然m_pEquipment数组会越界(size=1, index=1).
	{
		m_nIndex = m_nIndex == 0 ? 0 : m_nIndex - 1;
	}
	removeEquipment(pItem);
}

void CEquipment::takeOffEquipment(SItemDt* pItem)
{
	if (pItem) // 如果对应装备栏有装备,先卸掉旧装备
	{
		if (m_pEquiment[pItem->nTypeID])
		{
			if (pItem->nTypeID == 0)
			{
				int newAck = (CGameMgr::getInstance()->getGameMap()->getPlayer()->getAck() - m_pEquiment[pItem->nTypeID]->nAck);
				CGameMgr::getInstance()->getGameMap()->getPlayer()->setAck(newAck);
			}
			else
			{
				int newDfd = (CGameMgr::getInstance()->getGameMap()->getPlayer()->getDfd() - m_pEquiment[pItem->nTypeID]->nDef);
				CGameMgr::getInstance()->getGameMap()->getPlayer()->setDfd(newDfd);
			}
			addEquipment(m_pEquiment[pItem->nTypeID]);
		}
	}
}

void CEquipment::getAllEquiment()
{
	m_pVevData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendEquipmentItem();
}

void CEquipment::addEquipment(SItemDt* pItem)
{
	CGameMgr::getInstance()->getGameMap()->getPlayer()->addItem(pItem);
}

void CEquipment::removeEquipment(SItemDt* pItem)
{
	CGameMgr::getInstance()->getGameMap()->getPlayer()->removeItem(pItem);
}

string CEquipment::showEquipment(SItemDt* pItem)
{
	if (pItem)
	{
		return pItem->strName;
	}
	else
	{
		return "未佩戴装备";
	}
}

void CEquipment::update()
{
	MOVE_UP_DOWN(m_pVevData, m_nIndex);
	if (KEY_DOWN(VK_RETURN))
	{
		if (m_pVevData.size())
		{
			takeOffEquipment(m_pVevData[m_nIndex]);
			wearOnEquipment(m_pVevData[m_nIndex]);
		}
		
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setState(E_STATE_MAP);
	}

	//	脱装备。空出装备栏。
	else if (KEY_DOWN(VK_1))
	{
		if (m_pEquiment[0])
		{
			takeOffEquipment(m_pEquiment[0]);
			m_pEquiment[0] = nullptr;
		}
	}
	else if (KEY_DOWN(VK_2))
	{
		if (m_pEquiment[1])
		{
			takeOffEquipment(m_pEquiment[1]);
			m_pEquiment[1] = nullptr;
		}
	}
	else if (KEY_DOWN(VK_3))
	{
		if (m_pEquiment[2])
		{
			takeOffEquipment(m_pEquiment[2]);
			m_pEquiment[2] = nullptr;
		}
	}
	else if (KEY_DOWN(VK_4))
	{
		if (m_pEquiment[3])
		{
			takeOffEquipment(m_pEquiment[3]);
			m_pEquiment[3] = nullptr;
		}
	}
	else if (KEY_DOWN(VK_5))
	{
		if (m_pEquiment[4])
		{
			takeOffEquipment(m_pEquiment[4]);
			m_pEquiment[4] = nullptr;
		}
	}
}

void CEquipment::render()
{
	getAllEquiment();
	Set_Color(White);
	cout <<setw(CONSOLE_WIDTH*0.6)<< "--------------玩家状态------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.4) << "攻击力: ";
	Set_Color(LightGreen);
	cout << CGameMgr::getInstance()->getGameMap()->getPlayer()->getAck() << "\t";
	Set_Color(LightWhite); cout << "防御力: ";
	Set_Color(LightGreen);
	cout << CGameMgr::getInstance()->getGameMap()->getPlayer()->getDfd() << endl;
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.6) << "--------------当前装备------------" << endl;
	Set_Color(LightWhite);  cout << setw(CONSOLE_WIDTH*0.39) << "武器: ";
	Set_Color(PaleGreen);	cout << showEquipment(m_pEquiment[0]) << endl;
	Set_Color(LightWhite);	cout << setw(CONSOLE_WIDTH*0.39) << "防具: ";
	Set_Color(PaleGreen);	cout << showEquipment(m_pEquiment[1]) << endl;
	Set_Color(LightWhite);	cout << setw(CONSOLE_WIDTH*0.39) << "帽子: ";
	Set_Color(PaleGreen);	cout << showEquipment(m_pEquiment[2]) << endl;
	Set_Color(LightWhite);	cout << setw(CONSOLE_WIDTH*0.39) << "鞋子: ";
	Set_Color(PaleGreen);	cout << showEquipment(m_pEquiment[3]) << endl;
	Set_Color(LightWhite);	cout << setw(CONSOLE_WIDTH*0.39) << "宠物: ";
	Set_Color(PaleGreen);	cout << showEquipment(m_pEquiment[4]) << endl;
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.6) << "--------------可用装备------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.5) << "  名字\t图片\t等级\t加攻\t加防" << endl;;
	for (int i = 0; i < m_pVevData.size(); i++)
	{
		cout << setw(CONSOLE_WIDTH*0.3);
		if (m_pVevData[i]->nTypeID < 5)
		{
			if (i == m_nIndex)
			{
				Set_Color(LightGreen);
				cout << "->";
			}
			else
			{
				Set_Color(LightWhite);
				cout << "  ";
			}
			cout << m_pVevData[i]->strName << "\t" << m_pVevData[i]->strPic << "\t" << m_pVevData[i]->nLv
				<< "\t" << m_pVevData[i]->nAck << "\t" << m_pVevData[i]->nDef << endl;
		}
	}
	Set_Color(White);
	cout << endl<<setw(CONSOLE_WIDTH*0.6) << "----------------------------------" << endl;
	Set_Color(Green);
	cout << setw(CONSOLE_WIDTH*0.63) << "提示：按1 - 5键可脱下对应装备栏的装备。" << endl;
}


