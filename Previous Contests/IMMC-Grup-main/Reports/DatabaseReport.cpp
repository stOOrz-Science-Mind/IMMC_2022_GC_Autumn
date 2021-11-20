#include "DatabaseReport.h"
#include "../IO/FileManager.h"

const string DatabaseReport::LOG_FILE = "Log_Database.txt";

void DatabaseReport::log(string component, string message)
{
	string output = "(Database report -> " + component + "):" + message;
	FileManager::log(LOG_FILE, output);
}