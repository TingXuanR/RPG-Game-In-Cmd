#pragma once
#include "Player.h"
class CSell
{
public:
	CSell();
	~CSell();
	void update();
	void render();
	void init(int nNpcId);
private:
	int m_nState;
	int m_nTypeId;
	CPlayer* m_pPlayer;
	vector<SItemDt*> m_pVecItems;
};

