project(tests)

include_directories(../CppHttpClient)
include_directories(../CppHttpServer)

set(test1_source main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(test1 ${test1_source})

target_link_libraries(test1 cpphttpclient cpphttpserver)

add_test(NAME TestingNormalParameters
        COMMAND test1
        127.0.0.1 8000 ../bin/ 127.0.0.1 8000 HttpClient.exe)
set_tests_properties(TestingNormalParameters
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Test passed")

add_test(NAME TestingBadAddress
        COMMAND test1
        277.0.0.1 8000 ../bin/ 127.0.0.1 8000 HttpClient.exe)
set_tests_properties(TestingBadAddress
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Initing address error")

add_test(NAME TestingDifferentServerAndClientAddress
        COMMAND test1
        127.0.0.1 8000 ../bin/ 127.0.0.2 8000 HttpClient.exe)
set_tests_properties(TestingDifferentServerAndClientAddress
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Client connection error")

add_test(NAME TestingDifferentServerAndClientPort
        COMMAND test1
        127.0.0.1 8000 ../bin/ 127.0.0.2 8001 HttpClient.exe)
set_tests_properties(TestingDifferentServerAndClientPort
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Client connection error")

add_test(NAME TestingBadSocket
        COMMAND test1
        127.0.0.0 8000 ../bin/ 127.0.0.1 8000 HttpClient.exe)
set_tests_properties(TestingBadSocket
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Initing socket error")

add_test(NAME TestingBadSharePath
        COMMAND test1
        127.0.0.1 8000 ./BadPath 127.0.0.1 8000 HttpClient.exe)
set_tests_properties(TestingBadSharePath
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Share path error")

add_test(NAME TestingBadFilename
        COMMAND test1
        127.0.0.1 8000 ../bin/ 127.0.0.1 8000 HttpClient2.exe)
set_tests_properties(TestingBadFilename
                    PROPERTIES
                    PASS_REGULAR_EXPRESSION "Download file error")


