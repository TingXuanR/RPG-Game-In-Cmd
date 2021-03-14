#pragma once
#include "ConfigMgr.h"
#include "Player.h"
#include "NpcMgr.h"
#include "EnemyMgr.h"
//#include "Fight.h"
class CGameMap
{
public:
	CGameMap();
	~CGameMap();
	CPlayer* getPlayer();
	CEnemyMgr* getEnemyMgr();
	SLevelDt* getLevelDt();
	void update();
	void render();
	void check();
	void creatEnemies();
	void changeMap(int nMapID);
	void encounterNpc(CNpc* pNpc);
private:
	CPlayer* m_pPlayer;
	CNpcMgr* m_pNpcMgr;
	SLevelDt* m_pLevelDt;
	CEnemyMgr* m_pEnemyMgr; 
	//char m_arrTips[5][10];
	vector<string> m_vecTips;
};

