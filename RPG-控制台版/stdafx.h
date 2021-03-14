// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <math.h>
using namespace std;

#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code)&0x8000?1:0)

#define CONSOLE_WIDTH 120

// VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
#define VK_E 0x45
#define VK_I 0x49
#define VK_M 0x4D
#define VK_P 0x50
#define VK_D 0x44
// VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35

#define MAGIC_RATE 5	// 敌人发动技能的概率--50%

#define REWARD_RATE 2	// 20%的概率得到特殊奖励

#define PACK_SIZE 20

#define SAFE_DEL(p)	if(p){delete p; p = nullptr;}

#define  SAFE_DEL_VEC(vec)	if (vec.size())\
{\
	for (int i = 0; i < vec.size(); i++)\
	{\
		delete vec[i];\
	}\
	vec.clear();\
}


#define MOVE_UP_DOWN(vec, m_nIndex)	\
if (KEY_DOWN(VK_DOWN))\
{\
	m_nIndex++;\
if (m_nIndex > vec.size() - 1)\
	{\
		m_nIndex = 0;\
	}\
}\
else if (KEY_DOWN(VK_UP))\
{\
	m_nIndex--;\
	if (m_nIndex < 0)\
	{\
	m_nIndex = vec.size() - 1; \
	}\
}\

//自定义函根据参数改变字体颜色 
#define Set_Color(x) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x)
/*
0=黑色                8=灰色　
1=蓝色                9=淡蓝色        十六进制        　
2=绿色                10=淡绿色       0x0a
3=湖蓝色             11=淡浅绿色     0x0b　
4=红色                12=淡红色       0x0c　　　　
5=紫色                13=淡紫色       0x0d        　　　
6=黄色                14=淡黄色       0x0e        　　　
7=白色                15=亮白色       0x0f
*/
#define Black 0
#define Blue 1
#define Green 2
#define LakeBlue 3
#define Red 4
#define Purple 5
#define Yellow	6
#define White	7
#define Grey	8
#define LightBlue 9
#define LightGreen	10
#define PaleGreen  11
#define LightRed	12
#define LightPurple	13
#define LightYellow	14
#define LightWhite	15
#define GreenBlue FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define RedBlue	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
enum
{
	E_STATE_MENU,
	E_STATE_ROLE,
	E_STATE_MAP,
	E_STATE_SHOP,
	E_STATE_FIGHT,
	E_STATE_PACK,
	E_STATE_EQUIPMENT,
	E_STATE_PLAYERINFO,
	E_STATE_MISSION,
	E_STATE_BUYORSELLL,
	E_STATE_SELLL,
	E_STATE_STRONGER,
	E_STATE_PACKCHOOSE
};

enum
{
	E_MENU_START,
	E_MENU_SETTING,
	E_MENU_EXIT
};

enum 
{
	E_ROLE_ZHANSHI,
	E_ROLE_FASHI,
	E_ROLE_CIKE,
	E_ROLE_SHESHOU

};
// TODO:  在此处引用程序需要的其他头文件

#define SYN_THE_SIZE(VarType, VarName, FuncName) \
public:\
	void set##FuncName(VarType InVarName)\
{\
	VarName = InVarName; \
	}\
	VarType get##FuncName()\
{\
	return VarName; \
	}\
private:\
	VarType VarName;

#define SYN_THE_SIZE_READONLY(VarType, VarName, FuncName) \
public:\
	VarType get##FuncName()\
{\
	return VarName; \
	}\
private:\
	VarType VarName;

// TODO:  在此处引用程序需要的其他头文件
