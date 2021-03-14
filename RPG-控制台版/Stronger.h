#pragma once
#include "Player.h"
class CStronger	// ����������������������������������
{
public:
	CStronger();
	~CStronger();
	void update();
	void render();
	void init();
	void judge(SItemDt* pItem);
	SItemDt* findItemById(int nId);
	void showNeed(SItemDt* pItem);
	void getItemsCount();

private:
	//int m_nAckNeed;	// ���������������������
	//int m_nDfdNeed;	// �����������������
	//int m_nPetNeed;
	
	int m_nIndex;
	int m_nCount;
	int getLevelMatrial();
	vector<SItemDt*> m_pVecData;
	vector<SItemDt*> m_pVecMaterial;
};

