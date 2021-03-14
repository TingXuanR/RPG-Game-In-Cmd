#pragma once
#include "DataClass.h"
class CEnemy
{
public:
	CEnemy(SEnemyDt* pData);
	CEnemy();
	~CEnemy();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	vector<SMagicDt*> getMagic();
	void useMagic(SMagicDt* pMagic);
	int getHpBk();
	SYN_THE_SIZE(int, m_nRow, Row);
	SYN_THE_SIZE(int, m_nRowBk, RowBk);
	SYN_THE_SIZE(int, m_nBirthRow, BirthRow);
	SYN_THE_SIZE(int, m_nBirthCol, BirthCol);
	SYN_THE_SIZE(int, m_nCol, Col);
	SYN_THE_SIZE(int, m_nColBk, ColBk);
	SYN_THE_SIZE(int, m_nHp, Hp);
	SYN_THE_SIZE(int, m_nAck, Ack);
	SYN_THE_SIZE(int, m_nDfd, Dfd);
	SYN_THE_SIZE(int, m_nDir, Dir);
	SYN_THE_SIZE(int, m_nExp, Exp);
	SYN_THE_SIZE(int, m_nMoney, Money);
	SYN_THE_SIZE(int, m_nSpeed, Speed);
	SYN_THE_SIZE(int, m_nNum, Num); //标记是第几个生成的
	SYN_THE_SIZE(string, m_strPic, Pic);
	SYN_THE_SIZE(int, m_nID, ID);
	SYN_THE_SIZE(int, m_nStep, Step);
	SYN_THE_SIZE(int, m_nStepBk, StepBk);
private:
	//int nID;
	int MapID;
	string strName;
	vector<SMagicDt*> m_pVecData;

	int m_nHpBk = 0;
};

