#include <loader/file_reader.hpp>

FileReader &FileReader::read(std::string filename){
    std::stringstream ss;
    std::ifstream my_read_file;
    my_read_file.open(filename);
    char read_buffer[2048];
    if(my_read_file.is_open()){
        // Success Path
        while (!my_read_file.eof())
        {
            my_read_file.getline(read_buffer, 2048);
            ss << read_buffer;
            if(!my_read_file.eof()){
                ss << "\n";
            }
        }  
        my_read_file.close();
        m_file_read_status = FileReadStatus::FileRead_Success;    
        m_content = ss.str();
    }else{
        // Fail Path
        m_file_read_status = FileReadStatus::FileRead_Failed;
    }
    
    return *this;
} 

std::string FileReader::getContent(){
    return m_content;
}

std::string& FileReader::refContent(){
    return m_content;
}

bool FileReader::failed(){
    return m_file_read_status == FileReadStatus::FileRead_Failed;
}

bool FileReader::success(){
    return m_file_read_status == FileReadStatus::FileRead_Success;
}
