#pragma once
#include "Utils.h"
#include "Celula.h"
#include "Inregistrare.h"
#include "Filter.h"
#include "Tabela.h"
#include "../IO/FileManager.h"
#include "../Reports/DatabaseReport.h"

class Database
{
	int nextIdTabela;
	vector<Tabela*> v;

	static string dbName;

	static bool isNameSet;

	Database() {};//constructor private deoarece avem voie numai o baza de date
public:
	Database(Database const&) = delete;
	void operator=(Database const&) = delete;

	static Database& get()
	{
		static Database instance;
		return instance;
	}

	static void setName(string name);

	void IntrerpretareComanda(string comanda);
	void add(Tabela *t, string scheme);

	Tabela* getAt(size_t index);
	Tabela* getAtByName(string name);

	void deleteAtByName(string name);
	void deleteAt(size_t index);

	int getId();

};