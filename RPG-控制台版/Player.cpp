#include "stdafx.h"
#include "Player.h"
#include "GameMgr.h"

CPlayer::CPlayer()
{
	m_nRow = 0;
	m_nCol = 0;
	m_nID = 0;
	m_nHp = 0;
	m_nMp = 0;
	m_nDfd = 0;
	m_nAck = 0;
	m_nLv = 0;
	m_nExp = 0;
	m_pLv = new SLv();
	m_pLv->init();

}

void CPlayer::initConfig(SRoleDt* pConfig)
{
	m_nID = pConfig->nID;
	m_nAck = pConfig->nAck;
	m_nDfd = pConfig->nDfd;
	m_nHp = pConfig->nHp;
	m_nMp = pConfig->nMp;
	m_strName = pConfig->strName;
	m_strPic = pConfig->strPic;
	m_nMoney = pConfig->nMoney;
	m_nMaxHp = m_pLv->arrLv[m_nLv]->nMaxHp;
	m_nMaxMp = m_pLv->arrLv[m_nLv]->nMaxMp;
	m_pVecAllMagic = CConfigMgr::getInstance()->getMagicDtMgr()->getDataByRoleID(m_nID);
}


CPlayer::~CPlayer()
{
	SAFE_DEL_VEC(m_pVecData);
	SAFE_DEL_VEC(m_pVecAllMagic);
	SAFE_DEL_VEC(m_pVecUseableMagic);
}

void CPlayer::setBackUp(int row, int col)
{
	m_nRowBk = row;
	m_nColBk = col;
}

void CPlayer::setPosition(int row, int col)
{
	m_nRow = row;
	m_nCol = col;
}

void CPlayer::getBackUp()
{
	m_nRow = m_nRowBk;
	m_nCol = m_nColBk;
}

SItemDt* CPlayer::findItem(SItemDt* pItem)
{
	for (auto pTemp : m_pVecData)
	{
		if (pItem->nID == pTemp->nID)
		{
			return pTemp;
		}
	}
	return nullptr;
}

int CPlayer::getPackData()
{
	return m_pVecData.size();
}

void CPlayer::addItem(SItemDt* pItem)
{
	bool flag = true;
	if (getPackData()>=PACK_SIZE)
	{
		flag = false;
		Set_Color(LightYellow);
		cout << setw(CONSOLE_WIDTH*0.55)<<"您的背包已满，无法添加物品。" << endl;
		cout << endl << setw(CONSOLE_WIDTH*0.35) << " ";
		system("pause");
	}
	else if (getPackData() >= PACK_SIZE*0.8)
	{
		Set_Color(LightYellow);
		cout << setw(CONSOLE_WIDTH*0.55) << "您的背包将满，请尽快清理。" << endl;
		cout << endl << setw(CONSOLE_WIDTH*0.35) << " ";
		system("pause");
	}
	if (flag)
	{
		if (pItem->nTypeID < 5)
		{
			m_pVecData.push_back(pItem);
		}
		else
		{

			// 使用find函数
			//vector<SItemDt*>::iterator it = find(m_pVecData.begin(), m_pVecData.end(), pItem); // 迭代器没法转换为int，也没法转换为item*
			if (findItem(pItem))
			{
				findItem(pItem)->nCount++;
				return;
			}
			else
			{
				m_pVecData.push_back(pItem);
				return;
			}
		}
		if (pItem->nID == 5017)
		{
			m_nFnegYuZhi++;
		}
		sortItems();
	}
}

void CPlayer::removeItem(SItemDt* pItem)
{
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		if (pItem->nID == m_pVecData[i]->nID)
		{
			//m_pVecData.erase(m_pVecData.begin() + i);
			if (m_pVecData[i]->nCount > 1)
			{
			m_pVecData[i]->nCount--;
			}
			else
			{
			m_pVecData.erase(m_pVecData.begin() + i);
			}
			return;
		}
	}
}
void CPlayer::useItem(SItemDt* pItem)
{
	if (pItem->nTypeID == 0)
	{
		m_nAck += pItem->nAck;
	}
	else if (pItem->nTypeID == 5)
	{
		m_nHp += pItem->nHp;
		if (m_nHp > m_nMaxHp)
		{
			m_nHp = m_nMaxHp;
		}
		m_nMp += pItem->nMp;
		if (m_nMp > m_nMaxMp)
		{
			m_nMp = m_nMaxMp;
		}
	}
	else if (pItem->nTypeID == 4)
	{
		m_pPet = new SPet();
		m_pPet->nRow = m_nRow + 1;
		m_pPet->nCol = (m_nCol);
		m_pPet->strName = (pItem->strName);
		m_pPet->strPic = (pItem->strPic);
	}
	else
	{
		m_nDfd += pItem->nDef;
	}
	/*removeItem(pItem);*/
}



void CPlayer::update()
{

	setBackUp(m_nRow, m_nCol);
	if (getPet())
	{
		m_pPet->setBackUp();
	}
	if (KEY_DOWN(VK_UP))
	{
		m_nRow--;
		if (getPet())
		{
			m_pPet->nRow = m_nRow + 1;
			m_pPet->nCol = m_nCol;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nRow++;
		if (getPet())
		{
			m_pPet->nRow = m_nRow - 1;
			m_pPet->nCol = m_nCol;
		}

	}
	else if (KEY_DOWN(VK_LEFT))
	{
		m_nCol--;
		if (getPet())
		{
			m_pPet->nRow = m_nRow;
			m_pPet->nCol = m_nCol + 1;
		}
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		m_nCol++;
		if (getPet())
		{
			m_pPet->nRow = m_nRow;
			m_pPet->nCol = m_nCol - 1;
		}
	}
	else if (KEY_DOWN(VK_P)) // press p
	{
		enterPack(0);
	}
	else if (KEY_DOWN(VK_E)) //press e
	{
		enterEquipment();
	}
	else if (KEY_DOWN(VK_I)) // press i
	{
		showInfomation();
		cout << endl << setw(CONSOLE_WIDTH*0.4) << " "; system("pause");
	}
	else if (KEY_DOWN(VK_M)) // press m
	{
		showMission();
		cout << endl << setw(CONSOLE_WIDTH*0.4) << " "; system("pause");
	}

}
void CPlayer::render()
{
	cout << m_strPic;
}

bool CPlayer::CheckLvUp()
{

	if (m_nExp >= m_pLv->arrLv[m_nLv]->nExp)
	{
		return true;
	}
	return false;
}

void CPlayer::setLevelUp()
{
	m_nLv++;
	m_nHp = m_pLv->arrLv[m_nLv]->nMaxHp;
	m_nMp = m_pLv->arrLv[m_nLv]->nMaxMp;
	m_nMaxHp = m_pLv->arrLv[m_nLv]->nMaxHp;
	m_nMaxMp = m_pLv->arrLv[m_nLv]->nMaxMp;
	m_nAck += 15;
	m_nDfd += 5;
 }

std::vector<SItemDt*> CPlayer::sendMaterial()
{
	vector<SItemDt*> tempVec;
	for (auto pItem : m_pVecData)
	{
		if (pItem->nTypeID > 5)
		{
			tempVec.push_back(pItem);
		}
	}
	return tempVec;
}

void CPlayer::enterEquipment()
{
	CGameMgr::getInstance()->getEquipment()->getAllEquiment();
	CGameMgr::getInstance()->setState(E_STATE_EQUIPMENT);
}


void CPlayer::enterPack(int isFromWhere)
{
	if (isFromWhere == 0)
	{
		CGameMgr::getInstance()->setState(E_STATE_PACKCHOOSE);
	}
	else	// 打斗时直接进入药品界面
	{
		CGameMgr::getInstance()->getPack()->setFromWhere(isFromWhere);
		CGameMgr::getInstance()->setState(E_STATE_PACK);
	}
}

void CPlayer::showInfomation()
{
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.6) << "-------玩家信息概览-------\n" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "名字:  "; Set_Color(RedBlue);
	cout << getName() << endl;	Set_Color(White); cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "等级:  "; Set_Color(RedBlue);
	cout << getLv() << endl;	Set_Color(White); cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "经验:  "; Set_Color(RedBlue); cout << getExp(); Set_Color(PaleGreen);  cout << "/" << getPLv()->arrLv[getLv()]->nExp << endl; Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "金钱:  "; Set_Color(RedBlue); cout << getMoney() << endl;	Set_Color(White); cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "血量:  "; Set_Color(RedBlue); cout << getHp(); Set_Color(PaleGreen); cout << "/" << getMaxHp() << endl; Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "法力:  "; Set_Color(RedBlue); cout << getMp(); Set_Color(PaleGreen); cout << "/" << getMaxMp() << endl;	Set_Color(White); cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "攻击力: "; Set_Color(RedBlue); cout << getAck() << endl;	Set_Color(White); cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.47) << "防御力: "; Set_Color(RedBlue); cout << getDfd() << endl;	Set_Color(White); cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.49) << "已消灭小怪: "; Set_Color(RedBlue); cout << getKillEnemy1() << endl; Set_Color(White); 	cout << setw(CONSOLE_WIDTH*0.6) << "---------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.49) << "已消灭天魔: "; Set_Color(RedBlue); cout << getKillEnemy3() << endl; Set_Color(White);

}

SPet* CPlayer::getPet()
{
	return m_pPet;
}

vector<SItemDt*> CPlayer::sendEquipmentItem()
{
	vector<SItemDt*> pVecEquipmentItems;
	for (int i = 0; i < m_pVecData.size(); ++i)
	{
		if (m_pVecData[i]->nTypeID < 5)
		{

			pVecEquipmentItems.push_back(m_pVecData[i]);

		}
	}
	return pVecEquipmentItems;
}

vector<SMagicDt*> CPlayer::getMagic()
{

	for (SMagicDt* &magic : m_pVecAllMagic)
	{
		if (m_nLv >= magic->nLv && magic->nUsing == 0)
		{
			magic->nUsing = 1;
			m_pVecUseableMagic.push_back(magic);
		}
	}
	return m_pVecUseableMagic;
}

void CPlayer::useMagic(SMagicDt* pMagic)
{

	if (pMagic->nTypeID == 1 || pMagic->nTypeID == 0) // 攻击系
	{
		m_nAck = pMagic->nAck;
	}
	else if (pMagic->nTypeID == 3)	// 恢复系
	{
		m_nHp += pMagic->nHp;
	}
	m_nMp += pMagic->nMp;
}

void CPlayer::addMission(CMission* pMission)
{
	m_pVecMission.push_back(pMission);
}

void CPlayer::showMission()
{
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.8) << "------------------------任务列表----------------------------\n " << endl;
	if (m_pVecMission.size() == 0)
	{
		Set_Color(LightYellow);
		cout << setw(CONSOLE_WIDTH*0.6) << "暂时未领取任何任务" << endl;
	}
	else
	{
		Set_Color(LightWhite);
		cout << setw(CONSOLE_WIDTH*0.6) << "\t任务名称\t\t任务描述\t\t任务状态" << endl;
		for (int i = 0; i < m_pVecMission.size(); i++)
		{
			Set_Color(LightYellow);
			cout << setw(CONSOLE_WIDTH*0.6);
			cout << i << ":" << "\t" << m_pVecMission[i]->getName() << "\t" << m_pVecMission[i]->getDescription()
				<< "\t" << m_pVecMission[i]->getStateDescription()
				<< endl;
		}
	}
}

std::vector<SItemDt*> CPlayer::sendItems(int nNpcId)
{
	vector<SItemDt*> pVecItems;
	for (auto pItem : m_pVecData)
	{
		if (pItem->nNpcID == nNpcId)
		{
			pVecItems.push_back(pItem);
		}
	}
	return pVecItems;
}

vector<SItemDt*> CPlayer::sendPets(int nTypeId)
{
	vector<SItemDt*> pVecItems;
	for (auto pItem : m_pVecData)
	{
		if (pItem->nTypeID == nTypeId)
		{
			pVecItems.push_back(pItem);
		}
	}
	return pVecItems;
}

bool CPlayer::checkHp()
{
	if (m_nHp == m_nMaxHp)
	{
		return true;
	}
	return false;
}

bool CPlayer::checkMp()
{
	if (m_nMp == m_nMaxMp)
	{
		return true;
	}
	return false;
}

//bool CPlayer::judgeMission(CMission* &pMission)
//{
//	
//}

//void CPlayer::getMissionSchedule(CMission* pMission)
//{
//	switch (pMission->getID())
//	{
//	case 7001:
//		
//		break;
//	case 7002:
//		break;
//	case 7003:
//		break;
//	case 7004:
//		break;
//	case 7005:
//
//		break;
//	default:
//		break;
//	}
//}

vector<SItemDt*> CPlayer::getAllItem()
{
	return m_pVecData;
}

bool Rule1(const SItemDt* pItem1, const SItemDt* pItem2)
{
	return pItem1->strName < pItem2->strName;
}

bool Rule2(const SItemDt* pItem1, const SItemDt* pItem2)
{
	return pItem1->nTypeID < pItem2->nTypeID;
}

void CPlayer::sortItems()
{
	sort(m_pVecData.begin(), m_pVecData.end(), Rule1);
	sort(m_pVecData.begin(), m_pVecData.end(), Rule2);
}