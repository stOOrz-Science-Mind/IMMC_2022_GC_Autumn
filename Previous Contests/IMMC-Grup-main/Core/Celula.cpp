#include "Celula.h"

Celula::Celula(string nume, string tipCelula)
{
	if (!toLowerCase(tipCelula).compare("number") || !toLowerCase(tipCelula).compare("numeric")) this->tipCelula = TipCelula::NUMBER;
	else this->tipCelula = TipCelula::TEXT;
	this->nume = nume;
}

Celula& Celula::operator=(const Celula& c)
{
	this->nume = c.nume;
	this->tipCelula = c.tipCelula;
	return *this;
}

const bool Celula::operator < (const Celula &c) const {
	return (nume < c.nume);
}

string Celula::getNume()
{
	return nume;
}

TipCelula Celula::getTipCelula()
{
	return tipCelula;
}

string Celula::getTipCelulaAsString()
{
	return tipCelula == TipCelula::NUMBER ? "NUMBER" : "TEXT";
}