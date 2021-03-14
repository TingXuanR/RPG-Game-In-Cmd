#pragma once
#include "DataClass.h"
class CPack
{
public:
	CPack();
	~CPack();
	void update();
	void render();
	void getAllData();
	void printWithoutCount(vector<SItemDt*> m_pVecData);	// ���װ��������
	void printWithCount(vector<SItemDt*> m_pVecData);	// ���ҩƷ������
	SYN_THE_SIZE(int, m_nFromWhere, FromWhere);	// 0-map, 1-fight, 2-shop
	SYN_THE_SIZE(int, m_nPackChoose, PackChoose);	// 0-װ����1-ҩƷ����
private:
	vector<SItemDt*> m_pVecData;
	int m_nIndex;
};

