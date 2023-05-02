#pragma once

enum class Version { legacy, expert };


extern Version current_version;
const Version& getVersion();
void setVersion(const Version& v);


