#pragma once
#include "Utils.h"

class Celula
{
	string nume;
	TipCelula tipCelula;

public:
	Celula(string nume, string tipCelula);

	Celula& operator=(const Celula& c);
	const bool operator < (const Celula &c) const;

	string getNume();
	string getTipCelulaAsString();

	TipCelula getTipCelula();
};