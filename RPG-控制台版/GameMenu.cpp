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
			cout << setw(CONSOLE_WIDTH*0.5) << "即将退出游戏……" << endl;
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
	// setw(n)，向左边空n格。如cout<<setfill('#')<<setw(3)<<9; 结果为##9.
	cout <<setw(CONSOLE_WIDTH*0.6)<< "■■■■■■■■■■■■■■■" << endl; 
	cout << setw(CONSOLE_WIDTH*0.6) << "■■■■■■■■■■■■■■■" << endl;

	if (E_MENU_START == m_nState)
	{
		Set_Color(GreenBlue);
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■    ->游戏开始    ■■■" << endl;
		Set_Color(White);
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■      游戏设置    ■■■" << endl;
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■      游戏退出    ■■■" << endl;
	}
	else if (E_MENU_SETTING == m_nState)
	{
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■      游戏开始    ■■■" << endl;
		Set_Color(GreenBlue);
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■    ->游戏设置    ■■■" << endl;
		Set_Color(White);
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■      游戏退出    ■■■" << endl;
	}
	else
	{
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■      游戏开始    ■■■" << endl;
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■      游戏设置    ■■■" << endl;
		Set_Color(GreenBlue);
		cout << setw(CONSOLE_WIDTH*0.6) << "■■■    ->游戏退出    ■■■" << endl;
		Set_Color(White);
	}
	cout << setw(CONSOLE_WIDTH*0.6) << "■■■■■■■■■■■■■■■" << endl;
	cout << setw(CONSOLE_WIDTH*0.6) << "■■■■■■■■■■■■■■■" << endl;
}

