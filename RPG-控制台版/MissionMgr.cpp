#include "stdafx.h"
#include "MissionMgr.h"
#include "GameMgr.h"
#include "ConfigMgr.h"
CMissionMgr::CMissionMgr():m_nIndex(0)
{
	getAllMission();
}


CMissionMgr::~CMissionMgr()
{
}

void CMissionMgr::getAllMission()
{
	vector<SMissionDt*> p_vecData;
	p_vecData = CConfigMgr::getInstance()->getMissionDtMgr()->getAllData();
	for (auto pDt : p_vecData)
	{
		CMission* pMission = new CMission(pDt);
		m_pVecData.push_back(pMission);
	}
	
}

void CMissionMgr::sendMission(CMission* pMission)
{
	CGameMgr::getInstance()->getGameMap()->getPlayer()->addMission(pMission);
}

void CMissionMgr::update()
{
	m_pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
	for (auto pMission: m_pVecData)
	{
		if (pMission->getState()==1) //只判断已领取的任务是否完成。
		{
			judgeMission(pMission);
		}
	}
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setState(E_STATE_MAP);
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
	else if (KEY_DOWN(VK_RETURN))
	{
		if (m_pVecData[m_nIndex]->getState() == 0) // 任务不可以重复领取
		{
			m_pVecData[m_nIndex]->setState(1);
			sendMission(m_pVecData[m_nIndex]);
		}
		
	}
	else if (KEY_DOWN(VK_SPACE)) //按空格键领取奖励
	{
		if (m_pVecData[m_nIndex]->getState() == 2 && m_pVecData[m_nIndex]->getReceived() == 0)
		{
			getReward(m_pVecData[m_nIndex]);
			m_pVecData[m_nIndex]->setState(3);
		}
		else if (m_pVecData[m_nIndex]->getState() == 2 && m_pVecData[m_nIndex]->getReceived() == 1)
		{
			Set_Color(LightYellow);
			cout << endl<<setw(CONSOLE_WIDTH*0.5) << "您已经领取过奖励了" << endl;
			Set_Color(White);
		}
	}
}

void CMissionMgr::render()
{
	
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.8) << "------------------------任务列表----------------------------\n " << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.54)<<"任务名称\t\t任务描述\t\t任务状态" << endl;
	for (int i = 0; i < m_pVecData.size(); i++)
	{
		cout<<setw(CONSOLE_WIDTH*0.3);
		CMission* pDt = m_pVecData[i];
		if (i == m_nIndex)
		{
			Set_Color(GreenBlue);
			cout << "->";
		}
		else
		{

			cout << "  ";
		}
		cout << pDt->getName() << "\t" << pDt->getDescription() << "\t";
		if (pDt->getState()==0)
		{
			Set_Color(LightWhite);
		}
		else if (pDt->getState() == 1)
		{
			Set_Color(LightRed);
		}
		else if (pDt->getState() == 2)
		{
			Set_Color(LightGreen);
		}
		else if (pDt->getState() == 3)
		{
			Set_Color(RedBlue);
		}
		cout << pDt->getStateDescription() << endl;
		Set_Color(LightWhite);
	}
	cout << endl << setw(CONSOLE_WIDTH*0.8) << "--------提示：按回车键领取任务，按空格键领取完成任务的奖励------" << endl;
}

void CMissionMgr::judgeMission(CMission* &pMission)
{
	if (pMission->getID() == 7001)
	{
		if (m_pPlayer->getLv() >= 2)
		{
			pMission->setState(2);
		}
	}
	else if (pMission->getID() == 7002)
	{
		if (m_pPlayer->getKillEnemy1() >= 2)
		{
			pMission->setState(2);
		}
	}
	else if (pMission->getID() == 7003)
	{
		if (m_pPlayer->getKillEnemy3() >= 1)
		{
			pMission->setState(2);
		}
	}
	else if (pMission->getID() == 7004)
	{
		if (m_pPlayer->getFnegYuZhi() >= 1)
		{
			pMission->setState(2);
		}
	}
	else if (pMission->getID() == 7005)
	{
		if (m_pPlayer->getAck() >= 300)
		{
			pMission->setState(2);
		}
	}
}

void CMissionMgr::getReward(CMission* pMission)
{
	//CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
	Set_Color(LightGreen);
	cout << setw(CONSOLE_WIDTH*0.45);
	if (pMission->getID() == 7001)
	{
		m_pPlayer->setMoney(m_pPlayer->getMoney() + 300);
		cout << "恭喜你完成\"" << pMission->getName() << "\"任务. 奖励金钱300."<< endl;;
	}
	else if (pMission->getID() == 7002)
	{
		m_pPlayer->setExp(m_pPlayer->getExp() + 100);
		cout << "恭喜你完成\"" << pMission->getName() << "\"任务. 奖励经验100." << endl;
		m_pPlayer->CheckLvUp();
	}
	else if (pMission->getID() == 7003)
	{
		m_pPlayer->setMoney(m_pPlayer->getMoney() + 600);
		cout << "恭喜你完成\"" << pMission->getName() << "\"任务. 奖励金钱600." << endl;;

	}
	else if (pMission->getID() == 7004)
	{
		m_pPlayer->addItem(CGameMgr::getInstance()->getShop()->getItemByID(5015));
		cout << "恭喜你完成\"" << pMission->getName() << "\"任务. 奖励小松鼠一只." << endl;

	}
	else if (pMission->getID() == 7005)
	{
		m_pPlayer->addItem(CGameMgr::getInstance()->getShop()->getItemByID(5001));
		cout << "恭喜你完成\"" << pMission->getName() << "\"任务. 奖励宇宙锋一把." << endl;

	}
	pMission->setReceived(1);
	cout << endl << setw(CONSOLE_WIDTH*0.45) << " "; system("pause");
}

