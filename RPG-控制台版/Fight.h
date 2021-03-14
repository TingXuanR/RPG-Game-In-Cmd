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
	void playerAck();	// ��ҹ���
	void EnemyAck();	// ���˹���
	SMagicDt* getEMagic(int nRow, int nCol);

	void getAllReward();
	void clearRewards();
	
	void showFightingState();
private:
	int arrMap[3][15];
	vector<SMagicDt*> m_pVecPMagic;
	vector<SMagicDt*> m_pVecEMagic;
	int m_nIndex; 
	int m_nIsAck;  // �ж����ʹ�õ���������--1������ħ������--2������δ����--0��
	int m_nWhoIsAck; // �ж��Ǹ���ҹ������ǵ��˹���
	SMagicDt* m_pEMagic; // �洢���˵ļ���
	int m_nNum;

	vector<SRewardDt*> m_pVecReward;
};

