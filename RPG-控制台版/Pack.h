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
	void printWithoutCount(vector<SItemDt*> m_pVecData);	// 输出装备，宠物
	void printWithCount(vector<SItemDt*> m_pVecData);	// 输出药品，材料
	SYN_THE_SIZE(int, m_nFromWhere, FromWhere);	// 0-map, 1-fight, 2-shop
	SYN_THE_SIZE(int, m_nPackChoose, PackChoose);	// 0-装备，1-药品……
private:
	vector<SItemDt*> m_pVecData;
	int m_nIndex;
};

