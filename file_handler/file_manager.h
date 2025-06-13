#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H


#include "../includes/include.h"



class FileManager {
    public:
        void writeFile(const std::string toWrite);
        void writeFileAppend(const std::string toWrite);
        int readFile(char* buffer, int bufferSize);
};


#endif // UTILS_H