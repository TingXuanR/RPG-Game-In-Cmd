#pragma once
#include "Player.h"
#include "Enemy.h"

class CFight
{
public:
	CFight();
	~CFight();
	CEnemy* m_pEnemy;
	CPlayer* m_pPlayer;
	void init(CEnemy* pEnemy, CPlayer* pPlayer);
	void update();
	void render();
	void checkPlayerHp();
	bool checkEnemyHp();
	SMagicDt* getMagic(int nRow, int nCol);
	void Pangbai();
	void fighting();
	void playerAck();	// 玩家攻击
	void EnemyAck();	// 敌人攻击
	SMagicDt* getEMagic(int nRow, int nCol);

	void getAllReward();
	void clearRewards();
	
	void showFightingState();
private:
	int arrMap[3][15];
	vector<SMagicDt*> m_pVecPMagic;
	vector<SMagicDt*> m_pVecEMagic;
	int m_nIndex; 
	int m_nIsAck;  // 判断玩家使用的是物理攻击--1，还是魔法攻击--2，或者未攻击--0。
	int m_nWhoIsAck; // 判断是该玩家攻击还是敌人攻击
	SMagicDt* m_pEMagic; // 存储敌人的技能
	int m_nNum;

	vector<SRewardDt*> m_pVecReward;
};

