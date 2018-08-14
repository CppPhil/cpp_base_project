### GLOBAL SETTINGS
# CMake version
cmake_minimum_required(VERSION 3.1)

# C++ version
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

# Warning flags
if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Weffc++ -pedantic -pedantic-errors -Wcast-align -Wcast-qual -Wconversion -Wfloat-equal -Wmissing-field-initializers -Wmissing-include-dirs -Wmissing-noreturn -Wpointer-arith -Wredundant-decls -Wshadow -Wstack-protector -Wstrict-aliasing=2 -Wunreachable-code -Wunused -Wunused-parameter -Wlogical-op -Wold-style-cast -Wformat=2")
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-cond -Wnull-dereference")
    endif()
    
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wduplicated-branches -Wrestrict")
    endif()    
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything")
endif()

if(MSVC)
    # Treat warnings as errors when using msvc.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
endif()

# disable undesirable g++ warnings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-noexcept-type -Wno-unused-function")
endif()

# disable undesirable clang warnings
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++1z-extensions -Wno-c++98-compat -Wno-weak-vtables -Wno-documentation-unknown-command -Wno-padded -Wno-c++98-c++11-compat-pedantic -Wno-c++98-compat-pedantic -Wno-unknown-warning-option -Wno-double-promotion -Wno-unused-template -Wno-missing-prototypes -Wno-exit-time-destructors -Wno-unused-function")
endif()

# Optimization flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
endif()

# NDEBUG preprocessor symbol
if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DNDEBUG)
endif()

### PROJECT
# project name
project(cpp_base_project)

# output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Find platform specific multithreading support
find_package(Threads REQUIRED)

# Find fmt
find_package(fmt CONFIG REQUIRED)

# Find boost
find_package(Boost REQUIRED COMPONENTS atomic chrono container context contract coroutine date_time exception filesystem graph iostreams locale log log_setup math_c99 math_c99f math_c99l math_tr1 math_tr1f math_tr1l program_options random regex serialization signals stacktrace_addr2line stacktrace_backtrace stacktrace_basic stacktrace_noop system thread timer type_erasure wave wserialization)

## STATICALLY LINKED LIBRARY
set(LIBRARY_NAME cpp_base_project_lib)

set(LIB_HEADERS
    ./include/a.hpp
    ./include/philslib_function.hpp
    ./include/expected_lite_function.hpp
    ./include/brigand_function.hpp
    ./include/boost_function.hpp
    ./include/gsl_function.hpp)
    
set(LIB_SOURCES
    ./src/a.cpp
    ./src/philslib_function.cpp
    ./src/expected_lite_function.cpp
    ./src/brigand_function.cpp
    ./src/boost_function.cpp
    ./src/gsl_function.cpp)
    
add_library(${LIBRARY_NAME} STATIC "${LIB_HEADERS}" "${LIB_SOURCES}")

target_link_libraries(${LIBRARY_NAME} PRIVATE Threads::Threads)
target_link_libraries(${LIBRARY_NAME} PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(${LIBRARY_NAME} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${LIBRARY_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
## END STATICALLY LINKED LIBRARY

## APPLICATION
set(APPLICATION_SOURCE_FILES ./src/main.cpp)
add_executable(${PROJECT_NAME} "${LIB_HEADERS}" "${APPLICATION_SOURCE_FILES}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
## END APPLICATION

## TEST
enable_testing()
set(UNIT_TEST_NAME cpp_base_project_unittest)

set(TEST_SOURCES
    ./test/src/test_main.cpp
    ./test/src/philslib_function_test.cpp
    ./test/src/expected_lite_function_test.cpp
    ./test/src/brigand_function_test.cpp
    ./test/src/boost_function_test.cpp
    ./test/src/gsl_function_test.cpp)
    
add_executable(${UNIT_TEST_NAME}
    "${TEST_SOURCES}"
    "${LIB_HEADERS}")
    
add_test(Unittest ${UNIT_TEST_NAME})
    
target_link_libraries(${UNIT_TEST_NAME} PRIVATE ${LIBRARY_NAME})
target_link_libraries(${UNIT_TEST_NAME} PRIVATE Threads::Threads)
target_link_libraries(${UNIT_TEST_NAME} PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(${UNIT_TEST_NAME} PRIVATE ${Boost_LIBRARIES})
target_include_directories(${UNIT_TEST_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
## END TEST

# Include path for philslib
include_directories(${CMAKE_BINARY_DIR}/../deps/libraries/philslib/include)

# Include path for expected-lite
include_directories(${CMAKE_BINARY_DIR}/../deps/libraries/expected-lite/include)

# Include path for brigand
include_directories(${CMAKE_BINARY_DIR}/../deps/libraries/brigand/include/standalone)

# Avoid msvc problems
if(WIN32)
    if(MSVC)
        target_compile_definitions(${LIBRARY_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
        target_compile_definitions(${UNIT_TEST_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS NOMINMAX)
    endif()
endif()

