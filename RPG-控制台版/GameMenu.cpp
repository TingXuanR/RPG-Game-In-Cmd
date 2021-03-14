#include "stdafx.h"
#include "GameMenu.h"
#include "GameMgr.h"

CGameMenu::CGameMenu() :m_nState(E_MENU_START)
{
}


CGameMenu::~CGameMenu()
{
}

void CGameMenu::update()
{
	if (KEY_DOWN(VK_RETURN))
	{
		if (E_MENU_START == m_nState)
		{
			CGameMgr::getInstance()->setState(E_STATE_ROLE);
		}
		else if (E_MENU_EXIT == m_nState)
		{
			Set_Color(LightYellow);
			cout << setw(CONSOLE_WIDTH*0.5) << "�����˳���Ϸ����" << endl;
			cout << endl << setw(CONSOLE_WIDTH*0.35) << " ";
			system("pause");
			exit(0);
		}
	}
	else if (KEY_DOWN(VK_UP))
	{
		m_nState--;
		if (m_nState < E_MENU_START)
		{
			m_nState = E_MENU_EXIT;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nState++;
		if (m_nState > E_MENU_EXIT)
		{
			m_nState = E_MENU_START;
		}
	}
}

void CGameMenu::render()
{
	// setw(n)������߿�n����cout<<setfill('#')<<setw(3)<<9; ���Ϊ##9.
	cout <<setw(CONSOLE_WIDTH*0.6)<< "������������������������������" << endl; 
	cout << setw(CONSOLE_WIDTH*0.6) << "������������������������������" << endl;

	if (E_MENU_START == m_nState)
	{
		Set_Color(GreenBlue);
		cout << setw(CONSOLE_WIDTH*0.6) << "������    ->��Ϸ��ʼ    ������" << endl;
		Set_Color(White);
		cout << setw(CONSOLE_WIDTH*0.6) << "������      ��Ϸ����    ������" << endl;
		cout << setw(CONSOLE_WIDTH*0.6) << "������      ��Ϸ�˳�    ������" << endl;
	}
	else if (E_MENU_SETTING == m_nState)
	{
		cout << setw(CONSOLE_WIDTH*0.6) << "������      ��Ϸ��ʼ    ������" << endl;
		Set_Color(GreenBlue);
		cout << setw(CONSOLE_WIDTH*0.6) << "������    ->��Ϸ����    ������" << endl;
		Set_Color(White);
		cout << setw(CONSOLE_WIDTH*0.6) << "������      ��Ϸ�˳�    ������" << endl;
	}
	else
	{
		cout << setw(CONSOLE_WIDTH*0.6) << "������      ��Ϸ��ʼ    ������" << endl;
		cout << setw(CONSOLE_WIDTH*0.6) << "������      ��Ϸ����    ������" << endl;
		Set_Color(GreenBlue);
		cout << setw(CONSOLE_WIDTH*0.6) << "������    ->��Ϸ�˳�    ������" << endl;
		Set_Color(White);
	}
	cout << setw(CONSOLE_WIDTH*0.6) << "������������������������������" << endl;
	cout << setw(CONSOLE_WIDTH*0.6) << "������������������������������" << endl;
}

