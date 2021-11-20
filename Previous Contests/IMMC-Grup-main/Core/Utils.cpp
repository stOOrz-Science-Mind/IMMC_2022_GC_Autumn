#include "Utils.h"

void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

string toLowerCase(string s)
{
	for (size_t i = 0; i < s.size(); ++i)
	{
		s.at(i) = tolower(s.at(i));
	}
	return s;
}

string getCurrentDateAndTime()
{
	auto now = std::chrono::system_clock::now();

	time_t end_time = chrono::system_clock::to_time_t(now);

	string output = string(ctime(&end_time));
	return output.substr(0, output.size() - 1);
}

bool is_number(const std::string& s)
{
	char* end = nullptr;
	double val = strtod(s.c_str(), &end);
	return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

bool areNumbersEqual(double n, double n2, size_t precision)
{
	double factor = pow(10, precision);
	return (int)(n * factor) == (int)(n2 * factor);
}