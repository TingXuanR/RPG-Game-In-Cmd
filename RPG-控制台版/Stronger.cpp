#include "stdafx.h"
#include "Stronger.h"
#include "GameMgr.h"

CStronger::CStronger() :m_nIndex(0)
{
	/*m_nAckNeed = m_nDfdNeed = m_nPetNeed = 1; */// 一开始只需要一个就可以升级，之后每升级一次需要的数量加1

}


CStronger::~CStronger()
{
}

void CStronger::update()
{
	MOVE_UP_DOWN(m_pVecData, m_nIndex);
	if (KEY_DOWN(VK_RETURN))
	{
		judge(m_pVecData[m_nIndex]);
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setState(E_STATE_MAP);
	}
}

void CStronger::render()
{

	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.57) << "NAME\tACK\tDFD\tLV\t所需材料\t已有材料数量\n";
	for (int i = 0; i < m_pVecData.size(); ++i)
	{
		cout << setw(CONSOLE_WIDTH*0.25);
		if (m_nIndex == i)
		{
			Set_Color(GreenBlue);
			cout << "->";
		}
		else
		{
			Set_Color(LightWhite);
			cout << "  ";
		}
		cout << m_pVecData[i]->strName << "\t" << m_pVecData[i]->nAck << "\t" << m_pVecData[i]->nDef << "\t"
			<< m_pVecData[i]->nLv << "\t"; showNeed(m_pVecData[i]);

		if (findItemById(m_pVecData[i]->nMaterialId))
		{
			cout << "\t" << findItemById(m_pVecData[i]->nMaterialId)->nCount << endl;
		}
		else
		{
			cout << "\t0" << endl;
		}
		Set_Color(LightWhite);
	}
} 

void CStronger::init()
{
	m_pVecData = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendEquipmentItem();
	m_pVecMaterial = CGameMgr::getInstance()->getGameMap()->getPlayer()->sendMaterial();
}



void CStronger::judge(SItemDt* pItem)
{
	SItemDt* pMItem = findItemById(pItem->nMaterialId);
	if (pMItem)
	{
		if (pItem->nTypeID == 0)
		{
			if (pMItem->nCount >= pItem->nNeed)
			{
				pMItem->nCount -= pItem->nNeed;
				/*m_nAckNeed++;*/
				pItem->nLv++;
				pItem->nNeed++;
				pItem->nAck *= 1.1;
				pItem->nPrice *= 1.5;	// 每次升级都应该增加item的价值
			}
		}
		else if (pItem->nTypeID == 4)
		{
			if (pMItem->nCount >= pItem->nNeed)
			{
				pMItem->nCount -= pItem->nNeed;
				/*m_nPetNeed++;*/
				pItem->nLv++;
				pItem->nNeed++;
				pItem->nPrice *= 1.5;

			}
		}
		else
		{
			if (pMItem->nCount >= pItem->nNeed)
			{
				pMItem->nCount -= pItem->nNeed;
				/*m_nDfdNeed++;*/
				pItem->nLv++;
				pItem->nNeed++;
				pItem->nDef *= 1.1;
				pItem->nPrice *= 1.5;
			}
		}
	}
	
	//SAFE_DEL(pMItem);
}

SItemDt* CStronger::findItemById(int nId)
{
	for (auto pItem : m_pVecMaterial)
	{
		if (pItem->nID == nId)
		{
			return pItem;
		}
	}
	return nullptr;
}

void CStronger::showNeed(SItemDt* pItem)
{
	if (pItem->nTypeID == 0)
	{
		cout << "需要火凤羽: ";
	}
	else if (pItem->nTypeID == 4)
	{
		cout << "需要成长丸: ";
	}
	else
	{
		cout << "需要凤凰珠: ";
	}
	cout << pItem->nNeed;
}

void CStronger::getItemsCount()
{
	m_nCount = 0;
	for (auto pItem:m_pVecData)
	{
		m_nCount += pItem->nCount;
	}
}

