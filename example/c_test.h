#pragma once


#ifdef _WIN32
    #define TEST_API __declspec(dllexport)
#else
    #define TEST_API __attribute__((visibility("default")))
#endif


TEST_API void exampleFunc1(int intVal);
TEST_API void exampleFunc2(int intVal);
TEST_API void exampleFunc3(int intVal);