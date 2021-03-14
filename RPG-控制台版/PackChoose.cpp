 #include "stdafx.h"
#include "PackChoose.h"
#include "GameMgr.h"

CPackChoose::CPackChoose() :m_nIndex(0)
{
	itemType.push_back("װ��");
	itemType.push_back("ҩƷ");
	itemType.push_back("����");
	itemType.push_back("����");
	itemType.push_back("�˳�");
}


CPackChoose::~CPackChoose()
{
}

void CPackChoose::update()
{
	MOVE_UP_DOWN(itemType, m_nIndex);
	if (KEY_DOWN(VK_RETURN))
	{
		if (m_nIndex==itemType.size()-1)
		{
			CGameMgr::getInstance()->setState(E_STATE_MAP);
		}
		else
		{
			// enter Pack
			CGameMgr::getInstance()->getPack()->setFromWhere(0);
			CGameMgr::getInstance()->getPack()->setPackChoose(m_nIndex);
			CGameMgr::getInstance()->setState(E_STATE_PACK);
		}
		m_nIndex = 0;
	}
	//else if (KEY_DOWN(VK_ESCAPE))
	//{
	//	CGameMgr::getInstance()->setState(E_STATE_MAP);
	//}
}

void CPackChoose::render()
{
	Set_Color(LightWhite);
	cout << setw(CONSOLE_WIDTH*0.56)<<"***********\n";
	for (int i = 0; i < itemType.size(); i++)
	{
		cout << setw(CONSOLE_WIDTH*0.46)<<"  ";
		if (m_nIndex == i)
		{
			Set_Color(GreenBlue);
			cout << "-->" << itemType[i] << "****" << endl;
			Set_Color(LightWhite);
		}
		else
		{
			cout << "***" << itemType[i] << "****" << endl;
		}
	}
	cout << setw(CONSOLE_WIDTH*0.56) << "***********\n";
}