#ifndef GAMES_ENGINE_FILE_READER
#define GAMES_ENGINE_FILE_READER
#include <string>
#include <sstream> //To copyf file content that has been read from a file
#include <fstream> // To read files
#include <iostream>
#include <enums/file_read_status.enum.hpp>
/*
    Reads the text content of a file, 
    when given a filename to be read,
*/
class FileReader

{
    std::string m_content; // Stores the content of the file after reading
    FileReadStatus m_file_read_status = FileReadStatus::FileReader_NotRead; //Stores whether the file read status 
    public:
    FileReader& read(std::string filename); //Reads a file based on the given file path
    std::string getContent();
    std::string& refContent();
    bool success(); // Whether the state of the last file read was successful
    bool failed(); // Whether the state of the last file read was failed.
};
#endif