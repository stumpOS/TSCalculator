#include "Symbol.h"

bool operator<(Symbol<double> const& lhs, Symbol<double> const& rhs)
{
	if(lhs._rank < rhs._rank)
		return true;
	else
		return false;
}