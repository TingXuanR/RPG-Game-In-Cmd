#pragma once
#include "DataClass.h"
class CMission
{
public:
	CMission(SMissionDt* pData);
	~CMission();

	/*void init();*/
	string getStateDescription();
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(int, m_nState, State);
	SYN_THE_SIZE(string, m_nName, Name);
	SYN_THE_SIZE(string, m_nDescription, Description);
	SYN_THE_SIZE(int, m_nReceived, Received); //�жϸ������Ƿ��Ѿ���ȡ�������ˣ���ֹ�ظ��콱

};

