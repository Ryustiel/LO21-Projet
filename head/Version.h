#pragma once

enum class Version { legacy, tactic};


extern Version current_version;
const Version& getVersion();
void setVersion(const Version& v);


