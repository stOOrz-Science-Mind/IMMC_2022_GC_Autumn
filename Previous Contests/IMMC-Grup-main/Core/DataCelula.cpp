#include "DataCelula.h"

DataCelula::DataCelula(TipCelula tipCelula, void* data)
{
	memset(this, 0, sizeof(DataCelula));

	if (tipCelula == TipCelula::TEXT)
	{
		string * temp = reinterpret_cast<string*>(data);
		sData = string();
		sData = *temp;
	}
	else
	{
		double *temp = reinterpret_cast<double*>(data);
		dData = *temp;
	}
}