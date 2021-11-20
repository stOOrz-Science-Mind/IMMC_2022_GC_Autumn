#pragma once
#include "Utils.h"

union DataCelula
{
	double dData;
	string sData;

	DataCelula(TipCelula tipCelula, void* data);
	~DataCelula() {}
};