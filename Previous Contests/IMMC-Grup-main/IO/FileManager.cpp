#include "FileManager.h"

const string FileManager::DB_FILE_IDENTIFIER = "_db";
const string FileManager::DB_TABLE_FILE_IDENTIFIER = "_schema.scheme";
const string FileManager::DB_TABLE_DATA_IDENTIFIER = "data.bin";
string FileManager::DatabasePath;
string FileManager::currentPath;

vector<string> FileManager::tablePaths;

string FileManager::findCurrentProgramPath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

bool FileManager::createTableFromScheme(string tableName, ifstream &fileHandle)
{
	string schema;
	getline(fileHandle, schema);
	if (!schema.empty())
	{
		ltrim(schema);
		Database::get().IntrerpretareComanda("create table " + tableName + " (" + schema + ")");
		return true;
	}
	return false;
}

void FileManager::loadDataFromTables()
{
	size_t len = Database::get().getId();
	for (size_t i = 0; i < len; ++i)
	{
		string numeTabela = string(Database::get().getAt(i)->getNumeTabela());
		string fileName = DatabasePath + "\\" + numeTabela + "\\" + DB_TABLE_DATA_IDENTIFIER;
		ifstream fileHandle(fileName);
		if (!fileHandle.fail())
		{
			string data;
			while (getline(fileHandle, data))
			{
				if (!data.empty())
				{
					Database::get().IntrerpretareComanda("insert into " + numeTabela + " values(" + data + ")");
				}
			}
		}
	}
}

void FileManager::generateReport(string tableName, string output, string fileName)
{
	string fullFileName = DatabasePath + "\\" + tableName + "\\" + fileName;
	ofstream fileHandle(fullFileName);
	fileHandle << output;
}

void FileManager::generateReport(const char* tableName, string output, string fileName)
{
	string fullFileName = DatabasePath + "\\" + tableName + "\\" + fileName;
	ofstream fileHandle(fullFileName);
	fileHandle << output;
}

void FileManager::serializeTable(const char* tableName, string output)
{
	string fullFileName = DatabasePath + "\\" + tableName + "\\" + DB_TABLE_DATA_IDENTIFIER;
	ofstream fileHandle(fullFileName);
	fileHandle << output;
}

void FileManager::serializeTable(string tableName, string output)
{
	string fullFileName = DatabasePath + "\\" + tableName + "\\" + DB_TABLE_DATA_IDENTIFIER;
	ofstream fileHandle(fullFileName);
	fileHandle << output;
}

void FileManager::deleteSchema(string tableName)
{
	string fullFileName = DatabasePath + "\\" + tableName + "\\" + DB_TABLE_FILE_IDENTIFIER;
	ofstream fileHandle(fullFileName);
	fileHandle << "";
}

void FileManager::createSchema(string tableName, string schema)
{
	string path = DatabasePath + "\\" + tableName;
	CreateDirectory(path.c_str(), NULL);
	string fullFileName = path + "\\" + DB_TABLE_FILE_IDENTIFIER;
	ofstream fileHandle(fullFileName);
	fileHandle << schema;
}

void FileManager::loadTables()
{
	if (DatabasePath.empty()) return;
	string path = DatabasePath;
	WIN32_FIND_DATA findfiledata;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	char fullpath[MAX_PATH];
	GetFullPathName(path.c_str(), MAX_PATH, fullpath, 0);
	std::string fp(fullpath);

	hFind = FindFirstFile((LPCSTR)(fp + "\\*").c_str(), &findfiledata);

	bool first = false;

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((findfiledata.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY
				&& (findfiledata.cFileName[0] != '.'))
			{
				string fullPathName = DatabasePath;
				string dirName = findfiledata.cFileName;
				fullPathName += "\\" + dirName + "\\" + DB_TABLE_FILE_IDENTIFIER;
				ifstream fileHandle(fullPathName);
				if (!fileHandle.fail())
				{
					if (!first)
					{
						first = true;
					}
					if (createTableFromScheme(dirName, fileHandle))
					{
						cout << "S-a gasit tabelul " << dirName << "." << endl;
					}
				}
			}
		} while (FindNextFile(hFind, &findfiledata) != 0);
	}

	if (!first)
	{
		cout << "Nu s-a gasit niciun tabel in baza de date." << endl;
	}
	else
	{
		loadDataFromTables();
	}
}

void FileManager::createDatabase(string dbName)
{
	string path = getCurrentPath() + "\\" + dbName;
	CreateDirectory(path.c_str(), NULL);
	ofstream dbFile(path + "\\" + DB_FILE_IDENTIFIER);
	DatabasePath = path;
}

string FileManager::getCurrentPath()
{
	return currentPath;
}

bool FileManager::findDatabaseDirectory()
{
	string path = findCurrentProgramPath();
	WIN32_FIND_DATA findfiledata;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	char fullpath[MAX_PATH];
	GetFullPathName(path.c_str(), MAX_PATH, fullpath, 0);
	std::string fp(fullpath);

	currentPath = fullpath;
	hFind = FindFirstFile((LPCSTR)(fp + "\\*").c_str(), &findfiledata);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((findfiledata.dwFileAttributes | FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY
				&& (findfiledata.cFileName[0] != '.'))
			{
				string fullPathName = fullpath;


				string dirName = findfiledata.cFileName;
				fullPathName += "\\" + dirName + "\\" + DB_FILE_IDENTIFIER;
				ifstream fileHandle(fullPathName);
				if (!fileHandle.fail())
				{
					DatabasePath = fullpath + string("\\") + dirName;
					return true;
				}
			}
		} while (FindNextFile(hFind, &findfiledata) != 0);
	}
	return false;
}

void FileManager::log(string file, string output)
{
	string path = getCurrentPath() + "\\" + file;
	ofstream fileHandle(file, ios::app);
	string buffer = "[" + getCurrentDateAndTime() + "] " + output + "\n";
	fileHandle << buffer;
}
