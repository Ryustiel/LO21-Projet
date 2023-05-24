#include "../head/Version.h"

using namespace std;

std::initializer_list<Version> Versions = { Version::legacy, Version::tactic };

Version current_version = Version::legacy;

const Version& getVersion() { return current_version; };
void setVersion(const Version& v) { current_version = v; };

string toString(const Version& v) {
	string str_version;
	switch (v) {
	case Version::legacy:
		str_version = "Legacy";
		break;
	case Version::tactic:
		str_version = "Tactic";
		break;
	default:
		throw ShottenTottenException("versionToString : incorrect version specified");
	}
	return str_version;

}


std::ostream& operator<<(std::ostream& f, const Version& v) {
	f << toString(v);
	return f;
}