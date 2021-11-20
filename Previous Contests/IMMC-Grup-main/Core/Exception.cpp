#include "Exception.h"

Exception::Exception()
{

}
Exception::Exception(const char* message) : exception(message)
{
	_msg = message;
}

const char* Exception::what() const noexcept
{
	return _msg.c_str();
}