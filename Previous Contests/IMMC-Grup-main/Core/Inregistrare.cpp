#include "Inregistrare.h"

Inregistrare::Inregistrare(vector<DataCelula*> values)
{
	this->values = values;
}

void Inregistrare::setAtIndex(size_t index, DataCelula* celula)
{
	values.at(index) = celula;
}

void Inregistrare::setDataAtIndex(size_t index, TipCelula tipCelula, void* data)
{
	if (tipCelula == TipCelula::NUMBER)
	{
		double *temp = reinterpret_cast<double*>(data);
		values.at(index)->dData = *temp;
	}
	else
	{
		string * temp = reinterpret_cast<string*>(data);
		values.at(index)->sData = *temp;
	}
}

DataCelula* Inregistrare::getAtIndex(size_t index)
{
	return values.at(index);
}

size_t Inregistrare::getCeluleSize()
{
	return values.size();
}