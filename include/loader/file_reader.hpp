#ifndef GAMES_ENGINE_FILE_READER
#define GAMES_ENGINE_FILE_READER
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <enums/file_read_status.enum.hpp>

struct FileReader
{
    std::string m_content;
    FileReadStatus m_file_read_status = FileReadStatus::FileReader_NotRead;
    /*
        INPUT filename
        CONSTRUCT string stream
        CONSTRUCT input file stream
        OPEN FILE with file input stream with *filename*
        IF File From FILE READER IS OPEN
            WHILE file has not been fully read
            READ A Line from the file
            WRITE line to string stream
            CLOSE file
            SET **this** FILE_READ_STATUS as SUCCESSFUL
        COPY string from the stringstream into the content
        OTHERWISE FileReadStatus to failed
    */
    void read(std::string filename);
};
#endif