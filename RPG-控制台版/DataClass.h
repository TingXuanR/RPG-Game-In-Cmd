#pragma once
#include "DataTpt.h"
class CDataClass
{
public:
	CDataClass();
	~CDataClass();
};

struct SLevelDt
{
	~SLevelDt(){
		for (int i = 0; i < nRowSize; i++)
		{
			delete[] pArrMap[i];
		}
		delete[] pArrMap;
		delete[] arrEnemyBirth;
	}
	int nID;
	int nRowSize;
	int nColSize;
	int nBirthRow;
	int nBirthCol;
	string strName;
	int** pArrMap;
	int* arrEnemyBirth;	// 敌人出生点
	int* arrEnemyStep;	// 敌人能走的总步数
	int* arrEnemyDir;
	void input(fstream &inFile)
	{
		inFile >> strName >> nID >> nRowSize >> nColSize >> nBirthRow >> nBirthCol;
		arrEnemyBirth = new int[6];
		for (int i = 0; i < 6; i++)
		{
			inFile >> arrEnemyBirth[i];
		}

		arrEnemyStep = new int[3];
		for (int i = 0; i < 3; i++)
		{
			inFile >> arrEnemyStep[i];
		}

		arrEnemyDir = new int[3];
		for (int i = 0; i < 3; i++)
		{
			inFile >> arrEnemyDir[i];
		}

		pArrMap = new int*[nRowSize];  
		for (int i = 0; i < nRowSize; i++)
		{
			pArrMap[i] = new int[nColSize];
		}
		for (int m = 0; m < nRowSize; m++)
		{
			for (int n = 0; n < nColSize; n++)
			{
				inFile >> pArrMap[m][n];
			}
		}
	};
};

class CLevelDtMgr : public CDataTpt<SLevelDt>
{
public:
};

struct SRoleDt
{
	int nID;
	int nHp;
	int nAck;
	int nDfd;
	string strName;
	string strPic;
	int nExp;
	int nMoney;
	int nLv;
	int nMp;
	void input(fstream &inFile)
	{
		inFile >> nID >> nHp>> nMp >> nAck >> nDfd >> strName >> strPic >> nMoney >> nExp >> nLv;
	};
};

class CRoleDtMgr : public CDataTpt<SRoleDt>
{
public:
};

struct SNpcDt
{
	int nID;
	int nRow;
	int nCol;
	int nMapID;
	string strName;
	string strPic;
	
	void input(fstream &inFile)
	{
		inFile >> nID >> nMapID >> nRow >> nCol >> strName >> strPic;
	};
};

class CNpcDtMgr : public CDataTpt<SNpcDt>
{
public:

};

struct SItemDt
{
	int nID;
	int nHp;
	int nMp;
	int nAck;
	int nDef;
	int nPrice;
	int nNpcID;
	string strName;
	string strPic;
	int nTypeID;
	int nCount;
	int nLv;
	int nMaterialId;
	int nNeed = 1;	// 需要升级材料的数目
	int nNum = 0;	// 每个item的独有编号，作为识别标志。防止在技能升级时同一个ID的技能由于地址相同，一改全改。
	void input(fstream &inFile)
	{
		nCount = 1;
		inFile >> nID >> nHp >> nMp >> nAck >> nDef >> nPrice >> nNpcID >> strName >> strPic >> nTypeID >> nLv >> nMaterialId;
	};
};

class CItemDtMgr : public CDataTpt<SItemDt>
{
public:

};

struct SEnemyDt
{
	int nID;
	int MapID;
	int nHp;
	int nAck;
	string strName;
	string strPic;
	int nExp;
	int nMoney;
	int nDir;
	int nSpeed;
	int nDfd;
	void input(fstream &inFile)
	{
		inFile >> nID >> MapID >> nHp >> nAck >> nDfd >> strName >> strPic >> nExp >> nMoney >> nDir >> nSpeed;
	};
};

class CEnemyDtMgr : public CDataTpt<SEnemyDt>
{
public:
	
};

struct SLv
{
	int nLv;
	int nMaxHp;
	int	nMaxMp;
	int nExp; //升级所需经验
	SLv* arrLv[20];
	void init(){
		//memset(arrLv, 0, sizeof(arrLv));
		arrLv[0] = new SLv();
		arrLv[0]->nMaxHp = 500;
		arrLv[0]->nMaxMp = 125;
		arrLv[0]->nExp = 30;
		for (int i = 1; i < 20; i++)
		{
			arrLv[i] = new SLv();
			arrLv[i]->nMaxHp = arrLv[i - 1]->nMaxHp + 100;
			arrLv[i]->nMaxMp = arrLv[i - 1]->nMaxMp + 80;
			arrLv[i]->nExp = arrLv[i - 1]->nExp * 2;
			//arrLv[i]->nExp = arrLv[i - 1]->nExp * 2;
		}
	};
};

struct SPet
{
	int nRow;
	int nRowBk;
	int nCol;
	int nColBk;
	string strName;
	string strPic;
	void setBackUp();
	void getBackUp();
	void setPosition(int nRow, int nCol);
};

struct SMagicDt
{
	int nID;
	int nRoleID;
	int nHp;
	int nMp;
	int nAck;
	int nDfd;
	string strName;
	string strPic;
	int nLv;
	int nUsing = 0;
	int nRow = 2;
	int nCol = -1; 
	int nTypeID;
	void input(fstream &inFile)
	{
		inFile >> nID >> nRoleID >> nHp >> nMp >> nAck >> nDfd >> strName >> strPic >> nLv >> nTypeID;
	};
};

class CMagicDtMgr : public CDataTpt<SMagicDt>
{
};

struct SMissionDt
{
	int nID;
	string strName;
	string strDescription;
	int nState=0;
	void input(fstream &inFile)
	{
		inFile >> nID >> strName >> strDescription >> nState;
	}
};

class CMissionDtMgr : public CDataTpt<SMissionDt>
{
};

struct SRewardDt
{
	int nID;
	string strName;
	int nItemID;
	int nEnemyID;
	void input(fstream &inFile)
	{
		inFile >> nID >> strName >> nItemID >> nEnemyID;
	}
};

class CRewardDtMgr : public CDataTpt<SRewardDt>
{
};

