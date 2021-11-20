#pragma once
#include "Utils.h"

class Exception : public exception
{
	std::string _msg;
public:
	Exception();
	Exception(const char* message);

	virtual const char* what() const noexcept override;
};