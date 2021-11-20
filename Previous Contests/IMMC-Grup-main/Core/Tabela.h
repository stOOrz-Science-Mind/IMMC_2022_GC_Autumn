#pragma once
#include "Utils.h"
#include "DataCelula.h"
#include "Celula.h"
#include "Inregistrare.h"
#include "Filter.h"
#include "../Reports/TableReport.h"

class Tabela
{
	const int ID_TABELA;
	const static string REPORT_PREFIX;
	const static string REPORT_EXTENSION;

	char numeTabela[CHAR_MAX];

	vector<Celula*> celule;
	vector<Inregistrare*> inregistrari;

	size_t inregistrariGasite = 0;
	size_t queries = 0;
public:

	Tabela(const char *numeTabela, int id, vector<Celula*> celule);
	Tabela& operator=(const Tabela& t);
	~Tabela();

	void addRecord(vector<string> values);
	void deleteAtIndex(size_t index);
	void setAtIndex(size_t index, Celula *c);
	void deleteRecords(string celula, string value);
	void setInregistrareByCondition(string celula, string valueCelula, string celulaCautare, string valueCelulaCautare);
	void printRecords(vector<string> filters, Filter filter = Filter("", ""), size_t celulaIndex = -1);
	
	string printRecordAt(size_t index, vector<string> filters);

	char* getNumeTabela();

	Celula* getCelulaAtIndex(size_t index);
	Celula* getCelulaByName(string name);

	TipCelula getTipCelulaByName(string name);

	bool checkForCelula(string name);

	Inregistrare* getAtIndex(size_t index);

	size_t getCeluleSize();
	size_t getLast();

	vector<Celula*> getCelule();

	int getId();

	string getSerialisedTable();
};