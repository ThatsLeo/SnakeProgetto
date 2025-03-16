#include "../includes/include.h"



class FileManager {
    public:
        void writeFile(const std::string toWrite);
        void writeFileAppend(const std::string toWrite);
        int readFile(char* buffer, int bufferSize);
};