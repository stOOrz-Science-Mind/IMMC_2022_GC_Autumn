#include "Database.h"

string Database::dbName = "Database";
bool Database::isNameSet = false;

void Database::setName(string name)
{
	if (!isNameSet)
	{
		isNameSet = true;
		dbName = name;
	}
	else
	{
		cout << "Baza de date a fost deja denumita " << dbName << "!" << endl;
	}
}

void Database::IntrerpretareComanda(string comanda)
{
	string tableName;

	string delimiter = " ";
	size_t pos = comanda.find(delimiter);
	if (pos == std::string::npos)
	{
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda invalida: " + comanda);
		throw Exception("Comanda invalida!");
	}

	string token = comanda.substr(0, pos);
	comanda.erase(0, pos + delimiter.length());

	token = toLowerCase(token);
	if (!token.compare("insert"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("into"))
					{
						throw Exception("Eroare in sintaxa comenzii INSERT! -> into");
					}

					break;
				}
				case 1:
				{
					tableName = token;
					break;
				}
				default: break;
			}

			string temp = comanda;

			if (!toLowerCase(temp.substr(0, 6)).compare("values"))break;
			++i;

		}

		if (!Database::get().getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		if (i != 1 && i != 6)
		{
			throw Exception("Eroare in sintaxa comenzii INSERT!");
		}

		token = comanda;

		if (toLowerCase(token).substr(0, 6).compare("values"))
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> values");
		}

		token = token.substr(6, token.size());
		ltrim(token);

		if (token.at(0) != '(')
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> paranteza");
		}

		if (token.at(token.length() - 1) != ')')
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> paranteza");
		}

		token = token.substr(1, token.length() - 1);
		ltrim(token);
		token = token.substr(0, token.length() - 1);

		if (token.length() == 0)
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> valori nule");
		}

		string delimiter2 = ",";

		vector<string> values;

		pos = 0;
		string token2;

		ltrim(token);

		while ((pos = token.find(delimiter2)) != string::npos) {
			token2 = token.substr(0, pos);
			values.push_back(token2);
			token.erase(0, pos + delimiter2.length() + 1);
		}
		values.push_back(token);
		Database::get().getAtByName(tableName)->addRecord(values);
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda insert a fost executata: " + comanda);
	}
	else if (!token.compare("update"))
	{
		size_t i = 0;
		string celula, val, celula2, val2;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					tableName = token;
					if (!Database::get().getAtByName(tableName))
					{
						string tmp = "Nu exista tabelul " + tableName + " !";
						throw Exception(tmp.c_str());
					}

					break;
				}
				case 1:
				{
					token = toLowerCase(token);
					if (token.compare("set"))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> set");
					}
					break;
				}
				case 2:
				{
					if (!Database::get().getAtByName(tableName)->checkForCelula(token))
					{
						string tmp = "Eroare in sintaxa comenzii UPDATE! -> nu exista celula " + token;
						throw Exception(tmp.c_str());
					}

					celula = token;

					break;
				}
				case 3:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> primul =");
					}
					break;
				}
				case 4:
				{
					val = token;
					break;
				}
				case 5:
				{
					token = toLowerCase(token);
					if (token.compare("where"))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> where");
					}
					break;
				}
				case 6:
				{
					if (!Database::get().getAtByName(tableName)->checkForCelula(token))
					{
						string tmp = "Eroare in sintaxa comenzii UPDATE! -> nu exista celula " + token;
						throw Exception(tmp.c_str());
					}
					celula2 = token;
					break;
				}
				case 7:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> al doilea =");
					}
					break;
				}
				default: break;
			}
			++i;

		}

		if (i != 8)
		{
			throw Exception("Eroare in sintaxa comenzii UPDATE!");
		}

		val2 = comanda;

		Database::get().getAtByName(tableName)->setInregistrareByCondition(celula, val, celula2, val2);
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda update a fost executata: " + comanda);
	}
	else if (!token.compare("delete"))
	{
		size_t i = 0;
		string celula, val;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("from"))
					{
						throw Exception("Eroare in sintaxa comenzii DELETE! -> from");
					}

					break;
				}
				case 1:
				{
					tableName = token;
					if (!Database::get().getAtByName(tableName))
					{
						string tmp = "Nu exista tabelul " + tableName + " !";
						throw Exception(tmp.c_str());
					}

					break;
				}
				case 2:
				{
					token = toLowerCase(token);
					if (token.compare("where"))
					{
						throw Exception("Eroare in sintaxa comenzii DELETE! -> where");
					}
					break;
				}
				case 3:
				{
					if (!Database::get().getAtByName(tableName)->checkForCelula(token))
					{
						string tmp = "Eroare in sintaxa comenzii DELETE! -> nu exista celula " + token;
						throw Exception(tmp.c_str());
					}

					celula = token;

					break;
				}
				case 4:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii DELETE! -> =");
					}
					break;
				}
				default: break;
			}
			++i;

		}

		if (i != 5)
		{
			throw Exception("Eroare in sintaxa comenzii DELETE!");
		}

		val = comanda;

		Database::get().getAtByName(tableName)->deleteRecords(celula, val);
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda delete a fost executata: " + comanda);
	}
	else if (!token.compare("display"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("table"))
					{
						throw Exception("Eroare in sintaxa comenzii DISPLAY! -> table");
					}

					tableName = comanda;

					break;
				}
				default: break;
			}

			++i;

			if (i > 1)
			{
				throw Exception("Eroare in sintaxa comenzii DISPLAY! -> prea multe argumente");
			}
		}

		if (!Database::get().getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		vector<string> filters;
		Database::get().getAtByName(tableName)->printRecords(filters);
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda display a fost executata: " + comanda);
	}
	else if (!token.compare("drop"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("table"))
					{
						throw Exception("Eroare in sintaxa comenzii DROP! -> table");
					}

					tableName = comanda;

					break;
				}
				default: break;
			}

			++i;

			if (i > 1)
			{
				throw Exception("Eroare in sintaxa comenzii DROP! -> prea multe argumente");
			}
		}

		if (!Database::get().getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		Database::get().deleteAtByName(tableName);
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda drop a fost executata: " + comanda);
	}
	else if (!token.compare("select"))
	{
		size_t i = 0;
		string celula, val;
		vector<string> values;
		bool all = false, whereToken = false;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (!token.compare("all"))
					{
						all = true;
					}
					else
					{
						string delimiter2 = ",";

						size_t pos2 = comanda.find(delimiter2);
						string token2;

						if (pos2 != string::npos)
						{
							values.push_back(token.substr(0, token.size() - 1));

							ltrim(token);
							while ((pos2 = comanda.find(delimiter2)) != string::npos) {
								token2 = comanda.substr(0, pos2);
								values.push_back(token2);
								comanda.erase(0, pos2 + delimiter2.length() + 1);
							}

							string next = comanda.substr(0, comanda.find(" "));
							next = toLowerCase(next);

							if (next.compare("from"))
							{
								values.push_back(next);
								comanda = comanda.substr(comanda.find(" ") + 1, comanda.size());
								ltrim(comanda);
							}
							else
							{
								throw Exception("Eroare in sintaxa comenzii SELECT! -> from");
							}
						}
						else
						{
							if (token.at(token.size() - 1) == ',')token.erase(token.size() - 1, token.size());
							values.push_back(token);

							string next = comanda.substr(0, comanda.find(" "));
							next = toLowerCase(next);

							if (next.compare("from"))
							{
								values.push_back(next);
								comanda = comanda.substr(comanda.find(" ") + 1, comanda.size());
								ltrim(comanda);
							}
						}
					}

					break;
				}
				case 1:
				{
					token = toLowerCase(token);
					if (token.compare("from"))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> from");
					}

					break;
				}
				case 2:
				{
					tableName = token;
					break;
				}
				case 3:
				{
					token = toLowerCase(token);
					if (token.compare("where"))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> where");
					}

					whereToken = true;

					break;
				}
				case 4:
				{
					celula = token;

					break;
				}
				case 5:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> =");
					}

					break;
				}
				default: break;
			}
			if (all)
			{
				if (i == 1)
				{
					tableName = comanda;
				}
				else if (i == 5)
				{
					val = comanda;
				}
			}
			else
			{
				if (i == 1)
				{
					if (!whereToken)
					{
						tableName = comanda;
					}
				}
				else if (i == 5)
				{
					val = comanda;
				}
			}
			++i;

		}

		if (!Database::get().getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		if (i != 6 && i != 2)
		{
			throw Exception("Eroare in sintaxa comenzii SELECT!");
		}

		if (all)
		{
			if (!whereToken)
			{
				Database::get().getAtByName(tableName)->printRecords(values);
			}
			else
			{
				if (!Database::get().getAtByName(tableName)->getCelulaByName(celula))
				{
					string tmp = "Eroare in sintaxa comenzii SELECT! -> nu exista celula " + celula;
					throw Exception(tmp.c_str());
				}

				bool number = false;
				TipCelula tipCelulaCautata = Database::get().getAtByName(tableName)->getTipCelulaByName(celula);
				if (tipCelulaCautata == TipCelula::NUMBER)
				{
					if (!is_number(val))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> tipul coloanei nu se potriveste");
					}
					number = true;
				}

				vector<Celula*> celule = Database::get().getAtByName(tableName)->getCelule();
				size_t len = celule.size(), index;
				for (size_t i = 0; i < len; ++i)
				{
					if (!celule.at(i)->getNume().compare(celula))
					{
						index = i;
						break;
					}
				}

				Database::get().getAtByName(tableName)->printRecords(values, Filter(celula, val), index);
			}
		}
		else
		{
			size_t valuesSize = values.size();
			for (size_t i = 0; i < valuesSize; ++i)
			{
				if (!Database::get().getAtByName(tableName)->getCelulaByName(values.at(i)))
				{
					throw Exception("Eroare in sintaxa comenzii SELECT! -> nu exista coloanele selectate");
				}
			}
			if (!whereToken)
			{
				Database::get().getAtByName(tableName)->printRecords(values);
			}
			else
			{
				if (!Database::get().getAtByName(tableName)->getCelulaByName(celula))
				{
					string tmp = "Eroare in sintaxa comenzii SELECT! -> nu exista celula " + celula;
					throw Exception(tmp.c_str());
				}

				bool number = false;
				TipCelula tipCelulaCautata = Database::get().getAtByName(tableName)->getTipCelulaByName(celula);
				if (tipCelulaCautata == TipCelula::NUMBER)
				{
					if (!is_number(val))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> tipul coloanei nu se potriveste");
					}
					number = true;
				}

				vector<Celula*> celule = Database::get().getAtByName(tableName)->getCelule();
				size_t len = celule.size(), index;
				for (size_t i = 0; i < len; ++i)
				{
					if (!celule.at(i)->getNume().compare(celula))
					{
						index = i;
						break;
					}
				}

				Database::get().getAtByName(tableName)->printRecords(values, Filter(celula, val), index);
			}
		}
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda select a fost executata: " + comanda);
	}
	else if (!token.compare("create"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("table"))
					{
						throw Exception("Eroare in sintaxa comenzii CREATE! -> table");
					}

					break;
				}
				case 1:
				{
					tableName = toLowerCase(token);
					break;
				}
				default: break;
			}
			if (i == 1)break;
			++i;

		}

		if (i != 1)
		{
			throw Exception("Eroare in sintaxa comenzii CREATE!");
		}

		if (Database::get().getAtByName(tableName))
		{
			throw Exception(string("Tabelul " + tableName + " deja exista!").c_str());
		}

		token = comanda;
		token = toLowerCase(token);
		ltrim(token);

		if (token.at(0) != '(')
		{
			throw Exception("Eroare in sintaxa comenzii CREATE! -> paranteza");
		}

		if (token.at(token.length() - 1) != ')')
		{
			throw Exception("Eroare in sintaxa comenzii CREATE! -> paranteza");
		}

		token = token.substr(1, token.length() - 1);
		token = token.substr(0, token.length() - 1);

		if (token.length() == 0)
		{
			throw Exception("Eroare in sintaxa comenzii CREATE! -> valori nule");
		}

		string scheme = token;
		string delimiter2 = ",";

		vector<Celula*> values;

		pos = 0;
		string token2;

		ltrim(token);

		while ((pos = token.find(delimiter2)) != string::npos) {
			token2 = token.substr(0, pos);
			values.push_back(new Celula(token2.substr(0, token2.find(" ")), token2.substr(token2.find(" ") + 1, token2.length() - 1)));
			token.erase(0, pos + delimiter2.length() + 1);
		}
		values.push_back(new Celula(token.substr(0, token.find(" ")), token.substr(token.find(" ") + 1, token.length() - 1)));

		Database::get().add(new Tabela(tableName.c_str(), Database::get().getId(), values), scheme);
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda create a fost executata: " + comanda);
	}
	else
	{
		DatabaseReport::log("Method IntrerpretareComanda(string comanda)", "Comanda curenta nu exista: " + comanda);
		throw Exception("Comanda inexistenta!");
	}
}

void Database::add(Tabela *t, string scheme)
{
	v.push_back(t);

	cout << "Tabelul " << t->getNumeTabela() << "(#" << nextIdTabela++ << ") a fost creat. Structura:" << endl;

	size_t len = t->getCeluleSize();
	vector<Celula*> celule = t->getCelule();
	for (size_t i = 0; i < len; ++i)
	{
		cout << celule.at(i)->getNume() << " -> " << celule.at(i)->getTipCelulaAsString();
		if (i != len - 1) cout << " | ";
	}

	cout << endl;
	FileManager::createSchema(t->getNumeTabela(), scheme);
	DatabaseReport::log("Method add(Tabela *t, string scheme)", "O noua tabela a fost adaugata: " + string(t->getNumeTabela()));
}

Tabela* Database::getAt(size_t index)
{
	return v.at(index);
}

Tabela* Database::getAtByName(string name)
{
	size_t len = v.size();
	for (size_t i = 0; i < len; ++i)
	{
		if (!name.compare(v.at(i)->getNumeTabela())) return v.at(i);
	}
	return nullptr;
}

void Database::deleteAtByName(string name)
{
	size_t len = v.size();

	for (size_t i = 0; i < len; ++i)
	{
		if (!name.compare(v.at(i)->getNumeTabela()))
		{
			v.erase(v.begin() + i);
			break;
		}
	}

	FileManager::serializeTable(name, "");
	FileManager::deleteSchema(name);
	cout << "Tabelul " << name << " a fost sters!" << endl;
	DatabaseReport::log("Method deleteAtByName(string name)", "Tabela " + name + " a fost stearsa.");
}

int Database::getId()
{
	return nextIdTabela;
}

void Database::deleteAt(size_t index)
{
	v.erase(v.begin() + index);
	DatabaseReport::log("Method deleteAtByName(string name)", "Tabela " + string(v.at(index)->getNumeTabela()) + " a fost stearsa.");
}