// atof.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>
#include <iostream>
using namespace std;

int toInt(char c)
{
	if (c < '0' || c > '9') throw bad_exception("bad format");

	return c - '0';
}

double atof(const char * p)
{
	if (p == NULL) throw bad_exception("p as null");

	int len = strlen(p);
	if (len == 0) throw bad_exception("p is zero length");

	bool is_negative = p[0] == '-';
	bool is_dot = false;
	double franction = 0;
	int integer = 0;
	double percentage = 1.0;
	 
	len = p[len - 1] == 'f' ? len - 1 : len;

	for (int i = is_negative ? 1 : 0; i < len; i++)
	{
		if (p[i] == '.')
		{
			is_dot = true;
			continue;
		}
		 
		
		
		if (is_dot)
		{
			percentage *= 0.1;
			franction += toInt(p[i]) * percentage;
		}
		else
		{
			integer *= 10;
			integer += toInt(p[i]);
		}
	}

	return ((double)integer + franction)*(is_negative ? -1 : 1);
}

void validate(double expected, const char * input)
{
	double result;
	try
	{
		result = atof(input);
	}
	catch (bad_exception e)
	{
		cout <<"parsing " << input << " failed with " <<e.what() << endl;
		return;
	}
	
	if (expected == result) 
		cout << "\""<< input << "\" = " << expected << endl;
	else
		cout << "\"" << input << "\" != " << expected << endl;
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	validate(1.2, "1.2");
	validate(1.2, "1.2f");
	validate(-1.2, "-1.2");
	validate(-.2, "-.2");
	validate(-1.0, "-1.");
	validate(1.0, "a1.");
	validate(1.0, "1.b");
	return 0;
}

