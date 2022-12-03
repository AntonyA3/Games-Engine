
#ifndef __BASE_FILE__
#define __BASE_FILE__ "."
#endif

#ifndef TEST_DATA_DIRECTORY
#define TEST_DATA_DIRECTORY "./tests/data/"
#endif


#include <catch2/catch_amalgamated.hpp>
#include <loader/file_reader.hpp>
#include <iostream>

TEST_CASE( "File reader created but not used", "[FileReader][disk-access][default]" ){
    FileReader file_reader;
    REQUIRE(!file_reader.success());
    REQUIRE(!file_reader.failed());
}

TEST_CASE( "Valid File is successfully read", "[FileReader][disk-access][success]" ){
    FileReader file_reader;
    file_reader.read(TEST_DATA_DIRECTORY + std::string("hello_world.txt"));
    REQUIRE(file_reader.success());
    REQUIRE(file_reader.getContent() == std::string("Hello World    \nHello World"));
}

TEST_CASE( "invalid file is failed to read", "[FileReader][disk-access][failure]" ){
    FileReader file_reader;
    file_reader.read(TEST_DATA_DIRECTORY + std::string("does-not-exist.txt"));
    REQUIRE(file_reader.failed());
}
