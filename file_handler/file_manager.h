#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../includes/include.h"

/**
 * @brief FileManager class - handles file I/O operations
 * 
 * This class provides methods for reading from and writing to files,
 * particularly for saving and loading game scores and settings.
 */
class FileManager {
public:
    // ========== WRITE OPERATIONS ==========
    /**
     * @brief Write content to file (overwrite mode)
     * @param toWrite String content to write to file
     */
    void writeFile(const std::string toWrite);

    /**
     * @brief Write content to file (append mode)
     * @param toWrite String content to append to file
     */
    void writeFileAppend(const std::string toWrite);

    // ========== READ OPERATIONS ==========
    /**
     * @brief Read content from file into buffer
     * @param buffer Character buffer to store read content
     * @param bufferSize Maximum size of buffer
     * @return Number of characters read, or error code
     */
    int readFile(char* buffer, int bufferSize);
};

#endif // FILE_MANAGER_H