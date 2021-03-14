#pragma once
#include "DataClass.h"
#include "Mission.h"
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	void initConfig(SRoleDt* pConfig);
	void setBackUp(int row, int col);
	void setPosition(int row, int col);
	void getBackUp();
	void useItem(SItemDt* pItem);
	void addItem(SItemDt* pItem);
	SItemDt* findItem(SItemDt* pItem);
	void removeItem(SItemDt* pItem);
	void addPet(SItemDt* pPet);
	vector<SItemDt*> getAllItem();
	void update();
	void render();
	
	void enterEquipment();
	void enterPack(int isFromWhere);
	void showInfomation();
	SPet* getPet();
	vector<SItemDt*> sendEquipmentItem();
	vector<SMagicDt*> getMagic();
	void useMagic(SMagicDt* pMagic);
	void addMission(CMission* pMission);
	void showMission();
	vector<SItemDt*> sendItems(int nTypeId);	// �õ�����ҩƷ���Ա�ս��ʱʹ�á�
	bool checkHp(); // ���HP�Ƿ��������������޷�ʹ�ò�Ѫ��ҩƷ��
	bool checkMp();
	bool CheckLvUp();
	void setLevelUp();
	vector<SItemDt*> sendMaterial();
	void sortItems();
	vector<SItemDt*> sendPets(int nTypeId);
	int getPackData();
	SYN_THE_SIZE(int, m_nRow, Row);
	SYN_THE_SIZE(int, m_nRowBk, RowBk);
	SYN_THE_SIZE(int, m_nCol, Col);
	SYN_THE_SIZE(int, m_nColBk, ColBk);
	SYN_THE_SIZE(int, m_nHp, Hp);
	SYN_THE_SIZE(int, m_nMp, Mp);
	SYN_THE_SIZE(int, m_nMaxHp, MaxHp);
	SYN_THE_SIZE(int, m_nMaxMp, MaxMp);
	SYN_THE_SIZE(int, m_nAck, Ack);
	SYN_THE_SIZE(int, m_nDfd, Dfd);
	SYN_THE_SIZE(int, m_nLv, Lv);
	SYN_THE_SIZE(int, m_nExp, Exp);
	SYN_THE_SIZE(int, m_nMoney, Money);
	SYN_THE_SIZE(string, m_strName, Name);
	SYN_THE_SIZE(string, m_strPic, Pic);
	SYN_THE_SIZE(SLv*, m_pLv, PLv);
	SYN_THE_SIZE(int, m_nKillEnemy1, KillEnemy1);	// ɱ������С��
	SYN_THE_SIZE(int, m_nKillEnemy3, KillEnemy3);	// ɱ��һͷħ
	SYN_THE_SIZE(int, m_nFnegYuZhi, FnegYuZhi);
private:
	int m_nID;
	vector<SItemDt*> m_pVecData;
	SPet* m_pPet;
	vector<SMagicDt*> m_pVecAllMagic;
	vector<SMagicDt*> m_pVecUseableMagic;
	vector<CMission*> m_pVecMission;
};

