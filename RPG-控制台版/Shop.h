#pragma once
#include "DataClass.h"
class CShop
{
public:
	CShop();
	~CShop();
	void update();
	void render();
	void getItemsByNpcID(int nNpcID);
	SItemDt* getItemByID(int nID);
	void MyCopy(SItemDt* pTemp1, SItemDt* pTemp2);
	SYN_THE_SIZE(int, m_nFromWhere, FromWhere);	// 0-map,  1-buyOrsell
private:
	int m_nState;
	vector<SItemDt*> m_pVecData;
};

