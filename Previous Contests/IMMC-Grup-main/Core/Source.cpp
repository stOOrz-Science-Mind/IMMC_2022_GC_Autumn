#include "Database.h"
#include "../IO/FileManager.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (FileManager::findDatabaseDirectory())
	{
		FileManager::loadTables();
	}
	else
	{
		cout << "Nu exista o baza de date, se va crea una noua, dati numele acesteia: " << endl;
		string dbName;
		getline(cin, dbName);
		Database::setName(dbName);
		FileManager::createDatabase(dbName);
	}

	try
	{
		if (argc > 1)
			for (int i = 1; i < argc; ++i)
			{
				ifstream file(argv[i]);
				if (file.fail())
				{
					throw Exception(string("Nu exista fisierul " + string(argv[i]) + "!").c_str());
				}

				cout << endl << "Se executa fisierul " << argv[i] << ":" << endl << endl;
				string data;
				bool first = false;

				while (getline(file, data))
				{
					if (!data.empty())
					{
						if (!first)first = true;
						Database::get().IntrerpretareComanda(data);
					}
				}
				if (!first)cout << "Fisierul " << argv[i] << " este gol." << endl;
			}

	}
	catch (Exception &e)
	{
		cout << e.what() << endl;
	}

	return 0;
}