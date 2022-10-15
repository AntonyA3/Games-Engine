
#ifndef __BASE_FILE__
#define __BASE_FILE__ "."
#endif

#ifndef TEST_DATA_DIRECTORY
#define TEST_DATA_DIRECTORY "./tests/data/"
#endif


#define SDL_MAIN_HANDLED
#include <exotic/cester.h>
#include <loader/file_reader.hpp>
#include <iostream>

/*
    Given An invalid filename
    After Reading File
    Expect the file readstatus to be failed
*/
CESTER_TEST(read_non_existing_file, inst,
    std::string filename = "no_file.txt";
    FileReader file_reader;

    file_reader.read(filename); 
    cester_assert_true(FileReadStatus::FileRead_Failed == file_reader.m_file_read_status);
)

/*
    Given a valid filename
    After Reading File
    Expect the file readstatus to be sucessful
    Expect the file reader content to be same as text file content.

*/
CESTER_TEST(read_existing_file, inst,
    std::string filename = std::string(TEST_DATA_DIRECTORY) + "hello_world.txt";
    FileReader file_reader;
    file_reader.read(filename);
    cester_assert_true(FileReadStatus::FileRead_Success == file_reader.m_file_read_status);
    // Consider: Modifying CESTER FOR Better C++ Tests
    std::cout << "Expected Content: " <<"Hello World\nHello World" << std::endl;
    std::cout << "File     Content: " << file_reader.m_content << "\n\n\n\n";
)
/*
    Given a valid filename
    After reading the file twice
    Expect the file readstatus to be sucessful
    Expect the file reader content to be same as text file content.
*/
CESTER_TEST(read_existing_file_twice, inst,
    std::string filename = std::string(TEST_DATA_DIRECTORY) + "hello_world.txt";
    FileReader file_reader;
    file_reader.read(filename);
    file_reader.read(filename);

    cester_assert_true(FileReadStatus::FileRead_Success == file_reader.m_file_read_status);
)





// CESTER_TEST(expect_successful_file_read, inst,
//     FileReader file_reader;
//     file_reader.m_filename = "C:/Users/anton/DEV/Games-Engine/tests/Sample_Files/hello_world.txt";
//     file_reader.read();
//     cester_assert_true(FileReadStatus::FileRead_Success == file_reader.m_file_read_status);
//     // Consider: Modifying CESTER FOR Better C++ Tests
//     std::cout << "Expected Content: " <<"Hello World\nHello World" << std::endl;
//     std::cout << "File     Content: " << file_reader.m_content << "\n\n\n\n";
// )


// CESTER_TEST(expect_successful_repeat_read, inst,
//     FileReader file_reader;
//     file_reader.m_filename = "C:/Users/anton/DEV/Games-Engine/tests/Sample_Files/hello_world.txt";
//     file_reader.read();
//     file_reader.read();
//     file_reader.read();
//     cester_assert_true(FileReadStatus::FileRead_Success == file_reader.m_file_read_status);
//     // Consider: Modifying CESTER FOR Better C++ Tests
//     std::cout << "Expected Content: " <<"Hello World\nHello World" << std::endl;
//     std::cout << "File     Content: " << file_reader.m_content << "\n\n\n\n";
// )

// CESTER_TEST(expect_failed_file_read, inst,
//     FileReader file_reader;
//     file_reader.m_filename = "no_file.txt";
//     file_reader.read();
//     cester_assert_true(FileReadStatus::FileRead_Failed == file_reader.m_file_read_status);
// )

