#include "TableReport.h"
#include "../IO/FileManager.h"

const string TableReport::LOG_FILE = "Log_Table.txt";

void TableReport::log(string component, string message)
{
	string output = "(Table report -> " + component + "):" + message;
	FileManager::log(LOG_FILE, output);
}