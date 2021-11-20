#pragma once

class Report
{
	static const string LOG_FILE;

public:
	virtual void log(string component, string message) = 0;
};