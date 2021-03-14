#pragma once
#include "DataClass.h"
class CRoleSel
{
public:
	CRoleSel();
	~CRoleSel();
	virtual void update();
	virtual void render();
private:
	int m_nState;
	vector<SRoleDt*> m_pVecData;
};

