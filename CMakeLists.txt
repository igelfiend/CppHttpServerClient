cmake_minimum_required(VERSION 3.4)

project(CPPHTTPSERVERCLIENT)

enable_testing()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all")

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all")

add_subdirectory(CppHttpServer CppHttpServer)
add_subdirectory(CppHttpClient CppHttpClient)
add_subdirectory(tests tests)
