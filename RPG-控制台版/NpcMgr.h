#pragma once
#include "Npc.h"
class CNpcMgr
{
public:
	CNpcMgr();
	~CNpcMgr();

	void createAllNpc();
	CNpc* getNpc(int nRow, int nCol, int nMapID);
	vector<CNpc*> getAllNpc();
private:
	vector<CNpc*> m_VecData;
};

