#pragma once
#ifndef DOMAIN_H_
#define DOMAIN_H_

template<class T>
class Domain{
public:
	Domain():_upper(false,0),_lower(false,0),_hasConstraint(false){}
	virtual ~Domain(){}
	void Set(T up,T low)
	{
		SetUpperBound(up);
		SetLowerBound(low);
	}
	void SetLowerBound(T low)
	{
		_lower.first = true;
		_lower.second = low;
		_hasConstraint = true;
	}
	void SetUpperBound(T high)
	{
		_upper.first = true;
		_upper.second = up;
		_hasConstraint = true;
	}
	void SetUndefined(T discontinuity)
	{
		_discontinuity.first = true;
		_discontinuity.second = discontinuity;
		_hasConstraint = true;
	}
	bool IsWithin(T const& checkMe)
	{
		bool valid = true;

		if(!(_upper.first==false && _lower.first==false))
		{
			if(_upper.first==true && _lower.first==true)
				valid = (checkMe < _upper.second && checkMe > _lower.second);
			else if(_upper.first==false && _lower.first==true)
				valid = (checkMe > _lower.second);
			else if(_upper.first==true && _lower.first==true)
				valid = (checkMe < _upper.second);
		}
		if(_discontinuity.first==true)
			valid = (checkMe != _discontinuity.second);

		return valid;
	}
	bool HasConstraint(){return _hasConstraint;}
private:
	bool _hasConstraint;
	std::pair<bool,T> _upper;
	std::pair<bool,T> _lower;

	std::pair<bool,T> _discontinuity;
};
#endif