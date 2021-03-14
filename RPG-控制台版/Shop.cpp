#include "stdafx.h"
#include "Shop.h"
#include "GameMgr.h"

CShop::CShop() : m_nState(0), m_nFromWhere(0)
{
	
}


CShop::~CShop()
{
	SAFE_DEL_VEC(m_pVecData);
}
void CShop::update()
{
	MOVE_UP_DOWN(m_pVecData, m_nState);
	if (KEY_DOWN(VK_RETURN))
	{
		if (CGameMgr::getInstance()->getGameMap()->getPlayer()->getMoney() >= m_pVecData[m_nState]->nPrice)
		{
			SItemDt* pTemp = new SItemDt();	// 如果不new，则一只都只有一个pTemp指针，每次都是将同一个地址传给player，和没定义一样。
			MyCopy(pTemp, m_pVecData[m_nState]);	// 如果不定义一个临时指针，则每次插入的item地址都是相同的。升级装备时一改全改。
			CGameMgr::getInstance()->getGameMap()->getPlayer()->addItem(pTemp);
			CGameMgr::getInstance()->getGameMap()->getPlayer()->setMoney(CGameMgr::getInstance()->getGameMap()->getPlayer()->getMoney() - m_pVecData[m_nState]->nPrice);
		}
		else
		{
			Set_Color(LightYellow);
			cout <<setw(CONSOLE_WIDTH*0.5)<< "您的金币不够啦" << endl;
			cout << endl << setw(CONSOLE_WIDTH*0.35) << " ";
			system("pause");
			Set_Color(White);
		}
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		if (m_nFromWhere == 0)
		{
			CGameMgr::getInstance()->setState(E_STATE_MAP);
		}
		else if (m_nFromWhere == 1)
		{
			
			CGameMgr::getInstance()->setState(E_STATE_BUYORSELLL);
		}
	}
}

void CShop::render()
{
	
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.75) << "---------------------------选择商品---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.5) << "  NAME\tHP\tMP\tACK\tDEF\tPRICE\tPIC" << endl;
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		cout << setw(CONSOLE_WIDTH*0.25);
		SItemDt* pDt = m_pVecData[i];
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
		cout << pDt->strName << "\t" << pDt->nHp << "\t" << pDt->nMp
			<< "\t" << pDt->nAck << "\t" << pDt->nDef << "\t"
			<< pDt->nPrice << "\t" << 
			pDt->strPic << endl;
	}
	Set_Color(White);
}

void CShop::getItemsByNpcID(int nNpcID)
{
	m_nState = 0;
	m_pVecData = CConfigMgr::getInstance()->getItemDtMgr()->getDataByNpcID(nNpcID);
}

SItemDt* CShop::getItemByID(int nID)
{
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		if (nID == m_pVecData[i]->nID)
		{
			return m_pVecData[i];
		}
	}
	return nullptr;
}

void CShop::MyCopy(SItemDt* pTemp1, SItemDt* pTemp2)  // 直接pTemp = pTEmp2会把2的地址给1。
{
	pTemp1->nID = pTemp2->nID;
	pTemp1->nHp = pTemp2->nHp;
	pTemp1->nMp = pTemp2->nMp;
	pTemp1->nAck = pTemp2->nAck;
	pTemp1->nDef = pTemp2->nDef;
	pTemp1->nPrice = pTemp2->nPrice;
	pTemp1->nNpcID = pTemp2->nNpcID;
	pTemp1->strName = pTemp2->strName;
	pTemp1->strPic = pTemp2->strPic;
	pTemp1->nTypeID = pTemp2->nTypeID;
	pTemp1->nCount = pTemp2->nCount;
	pTemp1->nLv = pTemp2->nLv;
	pTemp1->nMaterialId = pTemp2->nMaterialId;
	pTemp1->nNeed = pTemp2->nNeed;	// 需要升级材料的数目
	pTemp1->nNum = pTemp2->nNum;
}
/*
int nID;
int nHp;
int nMp;
int nAck;
int nDef;
int nPrice;
int nNpcID;
string strName;
string strPic;
int nTypeID;
int nCount;
int nLv;
int nMaterialId;
int nNeed = 1;	// 需要升级材料的数目
int nNum = 0;
*/