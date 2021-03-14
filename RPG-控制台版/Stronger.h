#pragma once
#include "Player.h"
class CStronger	// 火凤羽给攻击道具升级，凤凰珠给防具升级
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
	//int m_nAckNeed;	// 攻击武器升级所需道具数
	//int m_nDfdNeed;	// 防具升级所需道具数
	//int m_nPetNeed;
	
	int m_nIndex;
	int m_nCount;
	int getLevelMatrial();
	vector<SItemDt*> m_pVecData;
	vector<SItemDt*> m_pVecMaterial;
};

