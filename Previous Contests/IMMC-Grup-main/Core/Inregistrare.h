#pragma once
#include "Utils.h"
#include "DataCelula.h"

class Inregistrare
{
	vector<DataCelula*> values;

public:
	Inregistrare(vector<DataCelula*> values);

	void setAtIndex(size_t index, DataCelula* celula);
	void setDataAtIndex(size_t index, TipCelula tipCelula, void* data);

	DataCelula* getAtIndex(size_t index);

	size_t getCeluleSize();
};