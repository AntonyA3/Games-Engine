Task Consider this what if future test should be added into a common testing file call it common_test for now, and start to do this by renaming rect_test.impl.cpp to common_tests.impl.cpp

Consider Treating Testing as a program that is designed to Check whether functions are being executed with their intended results, by using assertions. It is possible for tests to have errors or some important criteria to be missed. Things like initialising SDL are not well suited to unit tests however within the functions to initialise SDL it is possible to check whether a particular stage has failed, thererfore use these fuctions when testing this application

Will assert terminate the program, if so, How will I be able to detect cascasing errors.