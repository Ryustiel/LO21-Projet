#pragma once
#include <string>
#include <exception>

using namespace std;


class ShottenTottenException : public exception{
private:
    const char* info;
public:
    ShottenTottenException(const char* i): info (i){}
    const char* what() {
        return info;
    }
    
};

