#include "stdafx.h"
#include "Fight.h"
#include "GameMgr.h"

void CFight::init(CEnemy* pEnemy, CPlayer* pPlayer)
{
	m_pEnemy = pEnemy;
	m_pPlayer = pPlayer;
	m_pVecPMagic = m_pPlayer->getMagic();
	m_pVecEMagic = m_pEnemy->getMagic();
	m_nWhoIsAck = 0;
	m_nIndex = 0;
	m_nIsAck = 0;
	m_nWhoIsAck = 0;
	m_nNum = 11;
	m_pPlayer->setBackUp(m_pPlayer->getRowBk(), m_pPlayer->getColBk());
	m_pPlayer->setRow(2);
	m_pPlayer->setCol(0);

	m_pEnemy->setRowBk(m_pEnemy->getRow()); m_pEnemy->setColBk(m_pEnemy->getCol());
	m_pEnemy->setRow(2);
	m_pEnemy->setCol(9);

	getAllReward();
}
CFight::CFight()
{
	
}

CFight::~CFight()
{
	SAFE_DEL_VEC(m_pVecEMagic);
	SAFE_DEL_VEC(m_pVecPMagic);
	SAFE_DEL(m_pPlayer);
	SAFE_DEL(m_pEnemy);
	SAFE_DEL(m_pEMagic);
	SAFE_DEL_VEC(m_pVecReward);
}

void CFight::update()
{
	if (m_nWhoIsAck==0) // ����Һ͵����ڽ��й������ƶ���ʱ���°���Ӧ��û�з�Ӧ��
	{
		if (KEY_DOWN(VK_DOWN))
		{
			m_nIndex++;
			if (m_nIndex > m_pVecPMagic.size() - 1)
			{
				m_nIndex = 0;
			}
		}
		else if (KEY_DOWN(VK_UP))
		{
			m_nIndex--;
			if (m_nIndex < 0)
			{
				m_nIndex = m_pVecPMagic.size() - 1;
			}
		}
		else if (KEY_DOWN(VK_SPACE))
		{
			m_nIsAck = 1;
			m_nWhoIsAck = 1;
		}
		else if (KEY_DOWN(VK_RETURN))
		{
			if (m_pVecPMagic.size())
			{
				if (m_pVecPMagic[m_nIndex]->nLv == 0 && m_pPlayer->getMoney() >= 10000)  // �����0��������Ҫ10000�Ľ�Ǯ����ʹ��
				{
					if (m_pVecPMagic[m_nIndex]->nID == 6010) // ���ܼ���
					{
						m_nWhoIsAck = 0;
						m_pEnemy->setHp(m_pEnemy->getHpBk());	// ���ܺ���˵�Ѫ��Ҫ��ԭ�����λ��ҲҪ��ԭ
						m_pPlayer->getBackUp();
						CGameMgr::getInstance()->setState(E_STATE_MAP);
					}
					else  // ��ɱ����
					{
						m_pPlayer->useMagic(m_pVecPMagic[m_nIndex]);
					}
						
				}
				else if (m_pVecPMagic[m_nIndex]->nLv == 0 && m_pPlayer->getMoney() < 10000)
				{
					Set_Color(LightYellow);
					cout << setw(CONSOLE_WIDTH*0.6) << "���Ľ�Ǯ����10000���޷�ʹ�øü��ܡ�" << endl;
					cout << endl << setw(CONSOLE_WIDTH*0.35)<<" ";// setw�޷�ֱ�Ӷ�system("pause")�����ã�ֻ����һ���ո�ﵽ�ƶ�Ŀ�ġ� 
					system("pause");	
					
					Set_Color(White);
				}
				else if (m_pPlayer->getMp() >= abs(m_pVecPMagic[m_nIndex]->nMp))
				{
					m_pPlayer->useMagic(m_pVecPMagic[m_nIndex]);
					m_nIsAck = 2;
					m_nWhoIsAck = 1;
				}
				else
				{
					Set_Color(LightYellow);
					cout << setw(CONSOLE_WIDTH*0.6) << "����ħ��ֵ���㣬�޷�ʹ�øü��ܡ�" << endl;
					cout << endl << setw(CONSOLE_WIDTH*0.35) << " ";
					system("pause");
					Set_Color(White);
				}
			}
		}
		else if (KEY_DOWN(VK_P))  // press p
		{
			m_pPlayer->enterPack(1);
		}
	}

	fighting();

}

void CFight::showFightingState()
{
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.7) << "-------------------ս��״̬--------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.36) << "��ҹ�������" << m_pPlayer->getAck() << "\t\t ���˹�������" << m_pEnemy->getAck() << endl;
	cout << setw(CONSOLE_WIDTH*0.36) << "��ҷ�����: " << m_pPlayer->getDfd() << "\t\t ���˷�������" << m_pEnemy->getDfd() << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.36) << "���  Ѫ����"; 
	if (m_pPlayer->getHp()<=m_pPlayer->getMaxHp()*0.2)
	{
		Set_Color(LightRed);
	}
	else
	{
		Set_Color(LightGreen);
	}
	cout << m_pPlayer->getHp();
	Set_Color(LightYellow);
	cout << "/" << m_pPlayer->getMaxHp();
	Set_Color(LightWhite);
	cout << "\t����  Ѫ����"; Set_Color(LightGreen); cout << m_pEnemy->getHp() << endl;

	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.36) << "���  ħ��: "; Set_Color(GreenBlue); cout << m_pPlayer->getMp();
	Set_Color(LightYellow);
	cout << "/" << m_pPlayer->getMaxMp();
}

void CFight::render()
{
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.7) << "---------------------��ʾ----------------------------" << endl;
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.73) << "���ո������������,��Enter��������Ӧħ������, ��P���뱳�� " << endl;
	Set_Color(White);
	cout << setw(CONSOLE_WIDTH*0.7) << "------------------��Ҽ���---------------------------" << endl;

	if (m_pVecPMagic.size() > 0)
	{
		for (int i = 0; i < m_pVecPMagic.size(); ++i)
		{
			cout<<setw(CONSOLE_WIDTH*0.4);
			
			if (i == m_nIndex)
			{
				Set_Color(GreenBlue);
				cout << "->";
			}
			else
			{
				Set_Color(LightWhite);
				cout <<  " ";
			}
			cout << (i + 1) << ": " << m_pVecPMagic[i]->strName <<"\t��������"<<m_pVecPMagic[i]->nAck<< endl;
		}
	}
	else
	{
		cout << setw(CONSOLE_WIDTH*0.7) << "��ʱδ��ü���" << endl;
	}
	showFightingState();
	for (int i = 0; i < 3; i++)
	{
		cout<<setw(CONSOLE_WIDTH*0.4);
		for (int j = 0; j < 15; j++)
		{

			if (i == m_pPlayer->getRow() && j == m_pPlayer->getCol())
			{
				Set_Color(GreenBlue);
				m_pPlayer->render();
				Set_Color(White);
			}
			else if (i == m_pEnemy->getRow() && j == m_pEnemy->getCol())
			{
				Set_Color(LightRed);
				cout << m_pEnemy->getPic();
				Set_Color(White);
			}
			else if (getMagic(i, j))
			{
				Set_Color(RedBlue);
				cout << getMagic(i, j)->strPic;
				Set_Color(White);
			}
			else if (getEMagic(i, j))
			{
				Set_Color(RedBlue);
				cout << m_pEMagic->strPic;
				Set_Color(White);
			}
			/*else if (m_pEMagic)  //������ʹ�õ�i=2ʱ���ո񲻻����
			{
				if (m_pEMagic->nRow == i && m_pEMagic->nCol == j)
				{
					cout << m_pEMagic->strPic;
				}
			}*/
			else
			{
				cout << " "; 
			}
		}
		cout << endl;
	}
	if (m_nWhoIsAck > 0)
	{
		Set_Color(LightGreen);
		Pangbai();
	}
}

void CFight::checkPlayerHp()
{
	if (m_pPlayer->getHp() <= 0)
	{
		Set_Color(Red);
		cout << setw(CONSOLE_WIDTH*0.5) << "��ɫ��������Ϸ����" << endl;
		cout << setw(CONSOLE_WIDTH*0.4) << " "; system("pause");
		exit(0);
	}
}

bool CFight::checkEnemyHp()
{
	if (m_pEnemy->getHp() <= 0)
	{
		m_pPlayer->getBackUp();
		if (m_pPlayer->getPet())
		{
			m_pPlayer->getPet()->getBackUp();
		}

		if (m_pEnemy->getID() == 3001)	// ͳ��ɱ�����������������Ҫ��
		{
			m_pPlayer->setKillEnemy1(m_pPlayer->getKillEnemy1() + 1);
		}
		else if (m_pEnemy->getID() == 3003)
		{
			m_pPlayer->setKillEnemy3(m_pPlayer->getKillEnemy3() + 1);
		}

		CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->deleteEnemy(m_pEnemy->getRow(), m_pEnemy->getCol());

		if (CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->getDataSize() == 0) // ����ȫɱ���ˡ���Ҫ�������ɡ�
		{
			CGameMgr::getInstance()->getGameMap()->creatEnemies();
		}
		if (m_pVecReward.size() > 0)
		{
			Set_Color(GreenBlue);
			cout << setw(CONSOLE_WIDTH*0.69) << "�ޡޡޡޡޡޡ�ս��ʤ���ޡޡޡޡޡޡޡ�" << endl;
			cout << setw(CONSOLE_WIDTH*0.49) << "--------------" << m_pVecReward[0]->strName << m_pEnemy->getMoney() << "--------------" << endl;
			cout << setw(CONSOLE_WIDTH*0.49) << "--------------" << m_pVecReward[1]->strName << m_pEnemy->getExp() << "--------------" << endl;
			m_pPlayer->setExp(m_pEnemy->getExp() + m_pPlayer->getExp());
			m_pPlayer->setMoney(m_pEnemy->getMoney() + m_pPlayer->getMoney());
			for (int i = 2; i < m_pVecReward.size(); ++i)
			{
				if (m_pVecReward[i]->nID > 3000)
				{
					int nNum = rand() % 10;
					if (nNum < REWARD_RATE)
					{
						cout << setw(CONSOLE_WIDTH*0.49) << "--------------" << m_pVecReward[i]->strName << "--------------" << endl;
						m_pPlayer->addItem(CConfigMgr::getInstance()->getItemDtMgr()->getDataByID(m_pVecReward[i]->nItemID));	//ͨ��ID�õ���Ӧ��item�����
					}
				}
			}
			if (m_pPlayer->CheckLvUp())
			{
				m_pPlayer->setLevelUp();
				cout << setw(CONSOLE_WIDTH*0.45) <<"�ޡޡޡޡ�" << "��ϲ��,������" << m_pPlayer->getLv() << "��" << "�ޡޡޡޡޡ�" << endl;
			}
			cout <<  endl<<setw(CONSOLE_WIDTH*0.45)<<" "; system("pause");

			clearRewards();
		}
		

		CGameMgr::getInstance()->setState(E_STATE_MAP);
		return true;
	}
	return false;
}


SMagicDt* CFight::getMagic(int nRow, int nCol)
{
	for (int k = 0; k < m_pVecPMagic.size(); k++)
	{
		if (m_pVecPMagic[k]->nRow == nRow && m_pVecPMagic[k]->nCol == nCol)
		{
			return m_pVecPMagic[k];
		}
	}
	return nullptr;
}

void CFight::Pangbai()
{
	
	if (m_nWhoIsAck == 1)
	{
		if (m_nIsAck == 1)
		{
			cout << setw(CONSOLE_WIDTH*0.55);
			cout << "���ʹ��������, �з���Ѫ: " << m_pPlayer->getAck() - m_pEnemy->getDfd();
		}
		else if (m_nIsAck == 2)
		{
			cout<<setw(CONSOLE_WIDTH*0.6);
			SMagicDt* pMagic = m_pVecPMagic[m_nIndex];
			if (pMagic->nID == 6003)
			{
				cout << "���ʹ��ħ������: " + pMagic->strName + ", ��Ҽ�Ѫ: " << pMagic->nHp;
			}
			else
				cout << "���ʹ��ħ������: " + pMagic->strName + ", �з���Ѫ: " << pMagic->nAck - m_pEnemy->getDfd();
		}
	}
	else if (m_nWhoIsAck == 2)
	{
		if (m_pEMagic)
		{
			cout << setw(CONSOLE_WIDTH*0.45) << "�з�ʹ��ħ������: " << m_pEMagic->strName << ", ��ҵ�Ѫ: " << m_pEnemy->getAck() - m_pPlayer->getDfd();
		}
		else
			cout << setw(CONSOLE_WIDTH*0.55)<< "�з�ʹ��������, ��ҵ�Ѫ: " << m_pEnemy->getAck() - m_pPlayer->getDfd();
	}
	
}

void CFight::fighting()
{
	if (m_nWhoIsAck == 1)
	{
		if (m_nIsAck == 1) // ��ͨ����
		{
			if (m_pPlayer->getCol() == 9)
			{
				m_pPlayer->setCol(0);
				m_nWhoIsAck = 2;
				playerAck();
				m_nIsAck = 0;
			}
			else
				m_pPlayer->setCol(m_pPlayer->getCol() + 1);
		}
		else if (m_nIsAck == 2) // ���ܹ���
		{
			if (m_pVecPMagic[m_nIndex]->nCol == 9) //�������������˺��ٿ�ʼ������
			{
				m_pVecPMagic[m_nIndex]->nCol = -1;
				m_nWhoIsAck = 2;
				playerAck();
				m_nIsAck = 0;
			}
			else
			{
				m_pVecPMagic[m_nIndex]->nCol++;
			}
		}
	}
	
 	else if (m_nWhoIsAck == 2 && !checkEnemyHp())  // �з�����
	{
		
		if (m_nNum >= 8)  // �Ƿ�ʹ�ü���
		{
			srand((unsigned)time(NULL));
			m_nNum = rand() % 10; 
			if (m_nNum < MAGIC_RATE)
			{
				int nIndex = rand() % m_pVecEMagic.size(); //���ʹ��һ���
				m_pEMagic = m_pVecEMagic[nIndex];
				m_pEMagic->nCol = 8;
				m_pEnemy->setAck(m_pEMagic->nAck);
			}
		}
		else 
		{
			if (m_pEMagic)
			{
				
				if (m_pEMagic->nCol == 0)
				{
					m_pEMagic->nCol = -1;
					m_pEMagic = nullptr;
					m_nWhoIsAck = 0;
					EnemyAck();
					m_nNum = 11;
				}
				else
				{
					m_pEMagic->nCol -= 1;
				}
			}
			
			else // ������
			{
				if (m_pEnemy->getCol() == 0)
				{
					m_nWhoIsAck = 0;
					m_pEnemy->setCol(9);
					EnemyAck();
					m_nNum = 11;
				}
				else
					m_pEnemy->setCol(m_pEnemy->getCol() - 1);
			}
		}
		
	}
}

void CFight::playerAck()
{
	int nEmy_HP = m_pEnemy->getHp() - m_pPlayer->getAck() + m_pEnemy->getDfd();
	m_pEnemy->setHp(nEmy_HP);
}

void CFight::EnemyAck()
{
	if (!checkEnemyHp())
	{
		int nPly_HP = m_pPlayer->getHp() - m_pEnemy->getAck() + m_pPlayer->getDfd();
		m_pPlayer->setHp(nPly_HP);
		checkPlayerHp();
	}
}

SMagicDt* CFight::getEMagic(int nRow, int nCol)
{
	for (int k = 0; k < m_pVecEMagic.size(); k++)
	{
		if (m_pVecEMagic[k]->nRow == nRow && m_pVecEMagic[k]->nCol == nCol)
		{
			return m_pVecEMagic[k];
		}
	}
	return nullptr;
}

void CFight::getAllReward()
{
	vector<SRewardDt*> pRewards = CConfigMgr::getInstance()->getRewardDtMgr()->getAllData();
	for (auto pReward : pRewards)
	{
		if (pReward->nEnemyID == m_pEnemy->getID())
		{
			m_pVecReward.push_back(pReward);
		}
		else if (pReward->nEnemyID == 3000)
		{
			m_pVecReward.push_back(pReward);
		}
	}
}

void CFight::clearRewards()
{
	for (int i = m_pVecReward.size()-1; i >= 0; --i)
	{
		m_pVecReward.erase(m_pVecReward.begin() + i);
	}
}

//void CFight::fighting()
//{
//	int nEmy_HP = m_pEnemy->getHp() - m_pPlayer->getAck();
//	m_pEnemy->setHp(nEmy_HP);
//	if (!checkEnemyHp())
//	{
//		int nPly_HP = m_pPlayer->getHp() - m_pEnemy->getAck() + m_pPlayer->getDfd();
//		m_pPlayer->setHp(nPly_HP);
//		checkPlayerHp();
//	}
//}