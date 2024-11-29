
cmake_minimum_required(VERSION 3.28.3)
project(Rope)

# Set the build type and runtime output directory
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Set sources
set(SOURCES ${CMAKE_SOURCE_DIR}/src/rope.c)

# Include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Enable testing with CTest
enable_testing()

# Define the test directory
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Find all test files
file(GLOB TEST_FILES ${TEST_DIR}/*.c)

# Loop through each test file and create a test target
foreach(TEST_FILE ${TEST_FILES})
    # Extract the test name (e.g., test1 from test1.c)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Add an executable for this test
    add_executable(${TEST_NAME} ${SOURCES} ${TEST_FILE})

    # Add the test to CTest
    add_test(NAME ${TEST_NAME} COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}.bin)

    # Conditionally add memory testing based on platform
    if(UNIX AND NOT APPLE) # Linux-specific setup
        set_target_properties(${TEST_NAME} PROPERTIES SUFFIX ".bin") 

        add_custom_command(
            OUTPUT valgrind_report_${TEST_NAME}.txt
            COMMAND valgrind --leak-check=full --error-exitcode=1 
                    --log-file=valgrind_report_${TEST_NAME}.txt 
                    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_NAME}.bin
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            COMMENT "Running Valgrind on ${TEST_NAME}..."
        )

        add_custom_target(run_valgrind_${TEST_NAME}
            DEPENDS valgrind_report_${TEST_NAME}.txt
        )

        # Make the custom target depend on the test executable
        add_dependencies(run_valgrind_${TEST_NAME} ${TEST_NAME})
    endif()
endforeach()

# Create an aggregate target to run all memory tests (if on Linux)
if(UNIX AND NOT APPLE)
    add_custom_target(run_valgrind ALL
        COMMENT "Running Valgrind on all test executables..."
    )

    foreach(TEST_FILE ${TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        add_dependencies(run_valgrind run_valgrind_${TEST_NAME})
    endforeach()
endif()

