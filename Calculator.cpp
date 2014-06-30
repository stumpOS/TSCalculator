#include "Calculator.h"
template<>
std::string Calculator<double>::GetStringFromShort(unsigned short number)
{
	std::string result("");
	unsigned short digit = number;
	short numOfDigits = 0;
	while((number >> (numOfDigits*4)) > 0)
	{
		numOfDigits++;
	}
	for(short I = numOfDigits-1; I >= 0; I--)
	{
		digit = (number >> I) & 0xf;
		
		char cDigit = (char)(digit | 0x30);
		result += cDigit;
	}
	if(result=="")
		result = "0";

	return result;
}