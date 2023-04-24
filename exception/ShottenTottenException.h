#pragma once
#include <string>

using namespace std;


class stException
{
public:
	stException(const string& i) :info(i) {}
	string getInfo() const { return info; }
private:
	string info;
};

