if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.0.0)
    project(stot_lib VERSION 0.1.0)    
endif()

function(stot_set_prop REQUIRED_ARG REQUIRED_FILE)
        set(${REQUIRED_ARG} ${${REQUIRED_ARG}} "${REQUIRED_FILE}" PARENT_SCOPE)
endfunction()

add_subdirectory("src")