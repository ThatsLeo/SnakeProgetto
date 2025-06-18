#pragma once
#include "file_manager.h"

void FileManager::writeFile(std::string toWrite) {
    std::ofstream outputFile; 
    outputFile.open("SaveFile.txt"); 
    outputFile << toWrite;
    outputFile.close();
}

void FileManager::writeFileAppend(const std::string toWrite) {
    std::ofstream outputFile; 
    outputFile.open("SaveFile.txt", std::ios_base::app);
    outputFile << toWrite;
    outputFile.close();
}

int FileManager::readFile(char* buffer, int bufferSize) {
    std::ifstream inputFile; 
    inputFile.open("SaveFile.txt");
    if (!inputFile.is_open()) {
        buffer[0] = '\0'; 
        return 0;
    }
    inputFile.read(buffer, bufferSize - 1);
    buffer[inputFile.gcount()] = '\0'; 
    inputFile.close();

    int charsRead = inputFile.gcount();
    return charsRead;
}