#include "Tabela.h"
#include "../IO/FileManager.h"

const string Tabela::REPORT_PREFIX = "select_";
const string Tabela::REPORT_EXTENSION = ".txt";

Tabela::Tabela(const char *numeTabela, int id, vector<Celula*> celule) : ID_TABELA(id)
{
	strcpy(this->numeTabela, numeTabela);
	this->celule = celule;
}

//operatorul =
Tabela& Tabela::operator=(const Tabela& t)
{
	strcpy(this->numeTabela, t.numeTabela);

	this->celule = t.celule;
	return *this;
}
Tabela::~Tabela()
{

}

//setterii si getteri

void Tabela::addRecord(vector<string> values)//delimitatorul e constant, virgula spatiu -> ", "
{
	size_t len = values.size();
	string tmp = "Eroare in sintaxa comenzii INSERT! -> numarul valorilor nu corespunde numarul campurilor tabelului ";
	tmp += numeTabela;
	if (len != celule.size())throw Exception(tmp.c_str());
	vector<DataCelula*> dataValues;
	for (size_t i = 0; i < len; ++i)
	{
		string val = values.at(i);
		DataCelula *dataCelula;
		if (celule.at(i)->getTipCelula() == TipCelula::NUMBER)
		{
			if (!is_number(val))
			{
				tmp = "Eroare in sintaxa comenzii INSERT! -> tipurile valorilor nu corespund tipurilor campurilor tabelului ";
				tmp += numeTabela;
				throw Exception(tmp.c_str());
			}
			double *tempVal = new double;
			*tempVal = atof(val.c_str());
			void * tempVoidVal = (void*)tempVal;
			dataCelula = new DataCelula(TipCelula::NUMBER, tempVoidVal);
		}
		else
		{
			string *tempVal = new string;
			*tempVal = val;
			void * tempVoidVal = (void*)tempVal;
			dataCelula = new DataCelula(TipCelula::TEXT, tempVoidVal);
		}

		dataValues.push_back(dataCelula);
	}
	inregistrari.push_back(new Inregistrare(dataValues));

	cout << "Inserarea in tabelul " << numeTabela << " a fost efectuata cu succes. ID: " << inregistrari.size() - 1 << endl;

	FileManager::serializeTable(numeTabela, getSerialisedTable());
	TableReport::log("Metoda addRecord(vector<string> values)", "S-a inserat o noua inregistrare in tabelul " + string(numeTabela) + " ID: " + to_string(inregistrari.size() - 1));
}

void Tabela::deleteAtIndex(size_t index)
{
	celule.erase(celule.begin() + index);
	TableReport::log("Metoda deleteAtIndex(size_t index)", "S-a sters o celula din tabelul " + string(numeTabela) + " la indexul: " + to_string(index));
}

void Tabela::setAtIndex(size_t index, Celula *c)
{
	celule.at(index) = c;
	TableReport::log("Metoda setAtIndex(size_t index, Celula *c)", "S-a modificat o celula din " + string(numeTabela) + " la indexul: " + to_string(index));
}

char* Tabela::getNumeTabela()
{
	return numeTabela;
}

Celula* Tabela::getCelulaAtIndex(size_t index)
{
	return celule.at(index);
}

Celula* Tabela::getCelulaByName(string name)
{
	size_t len = celule.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (!celule.at(i)->getNume().compare(name))
		{
			return celule.at(i);
		}
	}
	return nullptr;
}

TipCelula Tabela::getTipCelulaByName(string name)
{
	size_t len = celule.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (!celule.at(i)->getNume().compare(name))
		{
			return celule.at(i)->getTipCelula();
		}
	}
	return TipCelula::TEXT;
}

bool Tabela::checkForCelula(string name)
{
	size_t len = celule.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (!celule.at(i)->getNume().compare(name))
		{
			return true;
		}
	}
	return false;
}

void Tabela::deleteRecords(string celula, string value)
{
	size_t len = celule.size(), index;
	TipCelula tipCelula;
	for (size_t i = 0; i < len; ++i)
	{
		if (!celule.at(i)->getNume().compare(celula))
		{
			index = i;
			tipCelula = celule.at(i)->getTipCelula();
			break;
		}
	}

	bool first = false;
	len = inregistrari.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (tipCelula == TipCelula::NUMBER)
		{
			if (!areNumbersEqual(inregistrari.at(i)->getAtIndex(index)->dData, atof(value.c_str())))
			{
				continue;
			}
		}
		else
		{
			if (inregistrari.at(i)->getAtIndex(index)->sData.compare(value))
			{
				continue;
			}
		}
		if (!first)first = true;

		inregistrari.erase(inregistrari.begin() + i);
		--i;
		--len;
	}
	if (first)
	{
		cout << "Inregistrarile cu coloana '" << celula << "' cu valoarea '" << value << "' au fost sterse." << endl;
		FileManager::serializeTable(numeTabela, getSerialisedTable());
		TableReport::log("Metoda deleteRecords(string celula, string value)", "Inregistrarile cu coloana '" + celula + "' cu valoarea '" + value + "' au fost sterse.");
	}
	else
	{
		cout << "Nu s-a sters nimic deoarece nu exista nici o valoare '" << value << "' pe coloana '" << celula << "'. " << endl;
	}
}

void Tabela::setInregistrareByCondition(string celula, string valueCelula, string celulaCautare, string valueCelulaCautare)
{
	size_t len = celule.size(), index = -1, index2 = -1;
	bool foundFirst = false, foundSecond = false;
	for (size_t i = 0; i < len; ++i)
	{
		if (!celule.at(i)->getNume().compare(celula))
		{
			index = i;
			foundFirst = true;
			if (foundSecond)break;
		}
		if (!celule.at(i)->getNume().compare(celulaCautare))
		{
			index2 = i;
			foundSecond = true;
			if (foundFirst)break;
		}
	}

	bool first = false;
	len = inregistrari.size();
	for (size_t i = 0; i < len; ++i)
	{
		TipCelula tipCelulaCautare = celule.at(index2)->getTipCelula();
		if (tipCelulaCautare == TipCelula::NUMBER)
		{
			if (!areNumbersEqual(inregistrari.at(i)->getAtIndex(index2)->dData, atof(valueCelulaCautare.c_str())))
			{
				continue;
			}
		}
		else
		{
			if (inregistrari.at(i)->getAtIndex(index2)->sData.compare(valueCelulaCautare))
			{
				continue;
			}
		}
		if (!first)first = true;
		TipCelula tipCelula = celule.at(index)->getTipCelula();

		if (tipCelula == TipCelula::NUMBER)
		{
			if (!is_number(valueCelula))
			{
				throw Exception("Eroare in sintaxa comenzii UPDATE! -> tipul celulei care trebuie actualizata este diferita de tipul valorii");
			}

			double *tempVal = new double;
			*tempVal = atof(valueCelula.c_str());
			void * tempVoidVal = (void*)tempVal;

			inregistrari.at(i)->setDataAtIndex(index, tipCelula, tempVoidVal);
		}
		else
		{
			string *tempVal = new string;
			*tempVal = valueCelula;
			void * tempVoidVal = (void*)tempVal;

			inregistrari.at(i)->setDataAtIndex(index, tipCelula, tempVoidVal);
		}
	}
	if (first)
	{
		cout << "Celulele cu numele '" << celula << "' cu conditia ca celula '" << celulaCautare << "' sa aiba valoarea '" << valueCelulaCautare << "' au fost actualizate cu valoarea '" << valueCelula << "'." << endl;
		FileManager::serializeTable(numeTabela, getSerialisedTable());
		TableReport::log("Metoda setInregistrareByCondition(string celula, string valueCelula, string celulaCautare, string valueCelulaCautare)", "Celulele cu numele '" + celula + "' cu conditia ca celula '" + celulaCautare + "' sa aiba valoarea '" + valueCelulaCautare + "' au fost actualizate cu valoarea '" + valueCelula + "'.");
	}
	else
	{
		cout << "Nu s-a actualizat nimic deoarece nu exista nici o valoare '" << valueCelulaCautare << "' pe coloana '" << celulaCautare << "'. " << endl;
	}
}

Inregistrare* Tabela::getAtIndex(size_t index)
{
	return inregistrari.at(index);
}

string Tabela::printRecordAt(size_t index, vector<string> filters)
{
	string output;
	size_t filtersLen = filters.size();
	if (filtersLen)
	{
		size_t celuleLen = celule.size();
		string msg = "\nInregistrarea #";
		msg += to_string(index);
		msg += "\n";

		for (size_t i = 0; i < filtersLen; ++i)
		{
			for (size_t j = 0; j < celuleLen; ++j)
			{
				if (!celule.at(j)->getNume().compare(filters.at(i)))
				{
					if (celule.at(j)->getTipCelula() == TipCelula::NUMBER)
					{
						msg += to_string(inregistrari.at(index)->getAtIndex(j)->dData);
						msg += " | ";
					}
					else
					{
						msg += inregistrari.at(index)->getAtIndex(j)->sData;
						msg += " | ";
					}
				}
			}
		}
		msg.erase(msg.size() - 2, msg.size() - 1);
		cout << msg << endl;
		output += msg + "\n";

	}
	else
	{
		size_t celuleLen = celule.size();
		string msg = "\nInregistrarea #";
		msg += to_string(index);
		msg += "\n";

		for (size_t i = 0; i < celuleLen; ++i)
		{
			if (celule.at(i)->getTipCelula() == TipCelula::NUMBER)
			{
				msg += to_string(inregistrari.at(index)->getAtIndex(i)->dData);
				msg += " | ";
			}
			else
			{
				msg += inregistrari.at(index)->getAtIndex(i)->sData;
				msg += " | ";
			}
		}
		msg.erase(msg.size() - 2, msg.size() - 1);
		output += msg + "\n";
		cout << msg << endl;
	}
	return output;
}

void Tabela::printRecords(vector<string> filters, Filter filter, size_t celulaIndex)
{
	string output;
	if (celulaIndex != -1 && !filter.celula.empty() && !filter.value.empty())
	{
		size_t len = inregistrari.size();
		bool first = false;
		for (size_t i = 0; i < len; ++i)
		{
			if (!inregistrari.at(i)->getAtIndex(celulaIndex)->sData.compare(filter.value) ||
				celule.at(celulaIndex)->getTipCelula() == TipCelula::NUMBER && areNumbersEqual(inregistrari.at(i)->getAtIndex(celulaIndex)->dData, atof(filter.value.c_str())))
			{
				if (!first)
				{
					first = true;

					string msg = "Se afiseaza tabelul " + string(numeTabela) + " cu conditia ca '" + filter.celula + "' sa fie '" + filter.value + "'.";
					output += msg + "\n";
					cout << msg << endl;

					size_t filtersLen = filters.size();
					if (filtersLen)
					{
						msg.clear();
						msg.assign("Se afiseaza coloanele ");
						output += msg;
						cout << msg;

						for (size_t j = 0; j < filtersLen; ++j)
						{
							msg.clear();
							msg.assign(filters.at(j));
							output += msg;
							cout << msg;

							if (j != filtersLen - 1)
							{
								msg.clear();
								msg.assign(", ");
								output += msg;
								cout << msg;
							}
						}
						output += "\n";
						cout << endl;
					}
				}
				++inregistrariGasite;
				output += printRecordAt(i, filters);
			}
		}
	}
	else
	{
		string msg = "Se afiseaza tot tabelul " + string(numeTabela) + ".";
		output += msg + "\n";
		cout << msg << endl;

		size_t filtersLen = filters.size();
		if (filtersLen)
		{
			msg.clear();
			msg.assign("Se afiseaza coloanele ");
			output += msg;
			cout << msg;
			for (size_t j = 0; j < filtersLen; ++j)
			{
				msg.clear();
				msg.assign(filters.at(j));
				output += msg;

				cout << msg;
				if (j != filtersLen - 1)
				{
					msg.clear();
					msg.assign(", ");
					output += msg;
					cout << msg;
				}
			}
			output += "\n";
			cout << endl;
		}
		size_t len = inregistrari.size();
		for (size_t i = 0; i < len; ++i)
		{
			output += printRecordAt(i, filters);
		}
		inregistrariGasite = len;
	}
	if (!inregistrariGasite)
	{
		if (!filter.celula.empty() && !filter.value.empty())
		{
			string msg = "Nu s-au gasit inregistrari cu coloana '" + filter.celula + "' sa aiba valoarea '" + filter.value + "'!";

			output += msg + "\n";
			cout << msg << endl;
		}
		else
		{
			string msg = "Tabelul este gol!";
			TableReport::log("Meotda printRecordAt(size_t index, vector<string> filters)", msg);
			output += msg + "\n";
			cout << msg << endl;
		}
	}
	else
	{
		if (inregistrariGasite != inregistrari.size())
		{
			string msg = "S-au gasit " + to_string(inregistrariGasite) + " inregistrari cu coloana '" + filter.celula + "' avand valoarea '" + filter.value + "'.";
			TableReport::log("Meotda printRecordAt(size_t index, vector<string> filters)", msg);
			output += "\n" + msg + "\n";
			cout << endl << msg << endl;
		}
	}
	output += "\n";
	cout << endl;
	inregistrariGasite = 0;

	FileManager::generateReport(numeTabela, output, REPORT_PREFIX + to_string(queries++) + REPORT_EXTENSION);
}

size_t Tabela::getCeluleSize()
{
	return celule.size();
}

vector<Celula*> Tabela::getCelule()
{
	return celule;
}

size_t Tabela::getLast()
{
	return inregistrari.size() - 1;
}

int Tabela::getId()
{
	return ID_TABELA;
}

string Tabela::getSerialisedTable()
{
	string output;
	size_t len = inregistrari.size();
	for (size_t i = 0; i < len; ++i)
	{
		size_t len2 = getCeluleSize();
		for (size_t j = 0; j < len2; ++j)
		{
			if (celule.at(j)->getTipCelula() == TipCelula::NUMBER)
			{
				output += to_string(inregistrari.at(i)->getAtIndex(j)->dData);
			}
			else
			{
				output += inregistrari.at(i)->getAtIndex(j)->sData;
			}
			if (j != len2 - 1)
			{
				output += ", ";
			}
		}
		if (i != len - 1)
		{
			output += "\n";
		}
	}
	return output;
}