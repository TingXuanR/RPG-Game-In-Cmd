#pragma once
#include "Mission.h"
#include "Player.h"
class CMissionMgr
{
public:
	CMissionMgr();
	~CMissionMgr();
	void getAllMission();
	void sendMission(CMission* pMission);
	void update();
	void render();

	void judgeMission(CMission* &pMission);
	void getReward(CMission* pMission);

private:
	vector<CMission*>	m_pVecData;
	int m_nIndex;
	CPlayer* m_pPlayer;
};

