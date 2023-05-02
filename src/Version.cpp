#include "..\head\Version.h"

Version current_version = Version::legacy;

const Version& getVersion() { return current_version; };
void setVersion(const Version& v) { current_version = v; };
