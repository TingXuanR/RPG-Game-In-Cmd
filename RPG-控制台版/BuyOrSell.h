#pragma once
class CBuyOrSell
{
public:
	CBuyOrSell();
	~CBuyOrSell();
	void update();
	void render();
	void setNpcId(int nNpcId);
private:
	int m_nState;
	int m_nNpcId;
	string s[3];
};

