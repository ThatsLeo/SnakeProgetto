#include "file_manager.h"

void FileManager::writeFile(std::string toWrite) {
    std::ofstream outputFile; 
    outputFile.open("SaveFile.txt"); 
    outputFile << toWrite;
    outputFile.close();
}

void FileManager::writeFileAppend(const std::string toWrite) {
    std::ofstream outputFile; 
    outputFile.open("SaveFile.txt", std::ios_base::app); // Open in append mode
    outputFile << toWrite;
    outputFile.close();
}

void FileManager::readFile(char* buffer, int bufferSize) {
    std::ifstream inputFile; 
    inputFile.open("SaveFile.txt");
    if (!inputFile.is_open()) {
        buffer[0] = '\0'; 
        return;
    }
    inputFile.read(buffer, bufferSize - 1); // Read up to bufferSize - 1 characters (null-terminator)
    buffer[inputFile.gcount()] = '\0'; 
    inputFile.close();
}