cmake_minimum_required(VERSION 3.10)
project(HashTable C)


set(CMAKE_C_STANDARD_REQUIRED ON)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")


set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)


set(LIB_SOURCES
    ${SRC_DIR}/forward_list.c
    ${SRC_DIR}/hash_implementation.c
    ${SRC_DIR}/hash_functions.c
)

set(LIB_HEADERS
    ${INCLUDE_DIR}/forward_list.h
    ${INCLUDE_DIR}/ht_interface.h
    ${INCLUDE_DIR}/hash_functions.h
)


add_library(hashtable STATIC ${LIB_SOURCES} ${LIB_HEADERS})
target_include_directories(hashtable PUBLIC ${INCLUDE_DIR})

add_executable(hash_tests ${TESTS_DIR}/main_test.c)
target_link_libraries(hash_tests hashtable)

enable_testing()
add_test(NAME HashTableTests COMMAND hash_tests)

option(USE_MURMUR_HASH "Use MurmurHash2 instead of simple sum hash" OFF)
if(USE_MURMUR_HASH)
    target_compile_definitions(hashtable PRIVATE MURMUR2)
    target_compile_definitions(hash_tests PRIVATE MURMUR2)
endif()

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS hash_tests
    COMMENT "Running hash table tests"
)
