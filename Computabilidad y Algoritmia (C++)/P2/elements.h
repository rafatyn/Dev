#ifndef elements_H_
#define elements_H_

// The Set STL template requires overloading operators =, == and <.
#include <string>
#include <iostream>
using namespace std;

class elements
{
	friend ostream &operator<<(ostream &, const elements &);
public:
  string sum;
	string s;
	
	elements();
	elements(char cadena);
	elements(const char*);
	elements(string cadena);
	elements(string cadena1, string cadena2);
	elements(const elements &);
	virtual ~elements();
	elements &operator=(const elements &rhs);
	int operator==(const elements &rhs) const;
	int operator<(const elements &rhs) const;
};

#endif /*elements_H_*/
