#pragma once
class CPackChoose
{
public:
	CPackChoose();
	~CPackChoose();
	void update();
	void render();
private:
	vector<string> itemType;
	int m_nIndex;
};

