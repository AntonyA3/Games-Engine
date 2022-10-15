#include <loader/file_reader.hpp>

void FileReader::read(std::string filename){
    std::stringstream ss;
    std::ifstream my_read_file;
    my_read_file.open(filename);
    char read_buffer[2048];
    if(my_read_file.is_open()){
        while (!my_read_file.eof())
        {
            my_read_file.getline(read_buffer, 2048);
            ss << read_buffer << " \n";
        }  
        my_read_file.close();
        m_file_read_status = FileReadStatus::FileRead_Success;    
        m_content = ss.str();

    }else{
        m_file_read_status = FileReadStatus::FileRead_Failed;
    }
} 
