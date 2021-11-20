#pragma once
#include "../Core/Utils.h"
#include "../Reports/Report.h"

class DatabaseReport : Report
{
	static const string LOG_FILE;
public:
	static void log(string component, string message);
};

