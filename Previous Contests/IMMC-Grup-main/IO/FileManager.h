#pragma once
#define WIN32_LEAN_AND_MEAN
#include "..\Core\Utils.h"
#include <Windows.h>
#include "../Core/Database.h"

class FileManager
{
	static string DatabasePath;
	static string currentPath;
	static const string DB_FILE_IDENTIFIER;
	static const string DB_TABLE_FILE_IDENTIFIER;
	static const string DB_TABLE_DATA_IDENTIFIER;

	static vector<string> tablePaths;

	static string findCurrentProgramPath();

	static void loadDataFromTables();

public:

	static void loadTables();
	static bool createTableFromScheme(string tableName, ifstream &fileHandle);
	static void generateReport(string tableName, string output, string fileName);
	static void generateReport(const char* tableName, string output, string fileName);
	static void serializeTable(string tableName, string output);
	static void serializeTable(const char* tableName, string output);
	static void deleteSchema(string tableName);
	static void createSchema(string tableName, string schema);
	static void createDatabase(string dbName);
	static void log(string file, string output);

	static string getCurrentPath();

	static bool findDatabaseDirectory();
};