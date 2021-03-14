#pragma once
#include "Enemy.h"
class CEnemyMgr
{
public:
	CEnemyMgr();
	~CEnemyMgr();
	void createEnemies(int mapId);
	CEnemy* getEnemy(int row, int col);
	void deleteEnemy(int row, int col);
	int getDataSize();
	void release();
	void update();

private:
	vector<CEnemy*> m_pVecData;
	int m_nTimer;

};

