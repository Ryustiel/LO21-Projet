#pragma once
#include "../exception/ShottenTottenException.h"
#include <string>
#include <iostream>

using namespace std;
enum class Version { legacy, tactic };
extern std::initializer_list<Version> Versions;

extern Version current_version;
const Version& getVersion();
void setVersion(const Version& v);
string toString(const Version& v);
Version toVersion(const string s);
std::ostream& operator<<(std::ostream& f, const Version& v);

