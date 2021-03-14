#pragma once
#include "stdafx.h"
template <class T>
class CDataTpt
{
public:
	CDataTpt(){};
	~CDataTpt();
	void loadFile(string strPath);
	T* getDataByID(int nID);
	T* getDataByIndex(int i);
	int getSize();
	vector<T*>& getAllData();
	vector<T*> getDataByNpcID(int nNpcID);
	vector<T*> getDataByRoleID(int nRoleID);
private:
	vector<T*> m_pVecData;

};

template <class T>
CDataTpt<T>::~CDataTpt()
{

	for (int i = 0; i < m_pVecData.size(); i++)
	{
		if (m_pVecData[i])
		{
			delete m_pVecData[i];
			m_pVecData[i] = nullptr;
		}
	}
	m_pVecData.clear();

}
template <class T>
vector<T*>& CDataTpt<T>::getAllData()
{
	return m_pVecData;
}

template <class T>
T* CDataTpt<T>::getDataByID(int nID)
{
	for each (T* data in m_pVecData)
	{
		if (data->nID == nID)
		{
			return data;
		}
	}
	return nullptr;
}

template <class T>
vector<T*> CDataTpt<T>::getDataByNpcID(int nNpcID)
{
	vector<T*> VecData;
	for (T* pData : m_pVecData)
	{
		if (pData->nNpcID == nNpcID)
		{
			VecData.push_back(pData);
		}
	}
	return VecData;
}

template <class T>
vector<T*> CDataTpt<T>::getDataByRoleID(int nRoleID)
{
	vector<T*> VecData;
	for (T* pData : m_pVecData)
	{
		if (pData->nRoleID == nRoleID)
		{
			VecData.push_back(pData);
		}
		else if (pData->nRoleID == 4000)
		{
			VecData.push_back(pData);
		}
	}
	return VecData;
}

template <class T>
int CDataTpt<T>::getSize()
{
	return m_pVecData.size();
}

template <class T>
T* CDataTpt<T>::getDataByIndex(int nIndex)
{
	if (nIndex < 0 || nIndex > m_pVecData.size() - 1)
	{
		return nullptr;
	}
	return m_pVecData[nIndex];
}


template <class T>
void CDataTpt<T>::loadFile(string strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string strTmp;
		getline(inFile, strTmp);
		int nCatagories = 0;
		inFile >> nCatagories;
		for (int i = 0; i < nCatagories; i++)
		{
			T* data = new T();
			data->input(inFile);
			m_pVecData.push_back(data);
		}
	}
	inFile.close();
}



