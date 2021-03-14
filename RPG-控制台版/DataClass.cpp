#include "stdafx.h"
#include "DataClass.h"


CDataClass::CDataClass()
{
}


CDataClass::~CDataClass()
{
}

void SPet::setBackUp()
{
	nRowBk = nRow;
	nColBk = nCol;
}
void SPet::getBackUp()
{
	nRow = nRowBk;
	nCol = nColBk;
}

void SPet::setPosition(int nRow, int nCol)
{
	this->nRow = nRow+1;
	this->nCol = nCol;
}
