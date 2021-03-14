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
	SYN_THE_SIZE(int, m_nReceived, Received); //判断该任务是否已经领取过奖励了，防止重复领奖

};

