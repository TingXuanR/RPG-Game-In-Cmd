#pragma once
#include "DataClass.h"
class CEquipment
{
public:
	CEquipment();
	~CEquipment();
	void wearOnEquipment(SItemDt* pItem);
	void takeOffEquipment(SItemDt* pItem);
	void getAllEquiment();
	void addEquipment(SItemDt* pItem);
	void removeEquipment(SItemDt* pItem);
	string showEquipment(SItemDt* pItem);
	void update();
	void render();
private:
	SItemDt* m_pEquiment[5];
	vector<SItemDt*> m_pVevData;
	int m_nIndex;
};

