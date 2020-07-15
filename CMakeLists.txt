if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.0.0)
    project(stot_lib VERSION 0.1.0)

    set(INCL_BASEDIR "")
    set(INCL_BASEDIR_CACHE "")
    set(INCL_BASEDIR_STATE 0)

    function(incl_basedir_push BASE_DIR)
        if (NOT ${INCL_BASEDIR_STATE} EQUAL 0)
            message(FATAL_ERROR "Didn't pop last basedir")
        else()
        set(INCL_BASEDIR_STATE 1 PARENT_SCOPE)
        set(INCL_BASEDIR_CACHE ${INCL_BASEDIR} PARENT_SCOPE)
        set(INCL_BASEDIR ${BASE_DIR} PARENT_SCOPE)
        endif()    
    endfunction()

    function(incl_basedir_pop)
        set(INCL_BASEDIR_STATE 0 PARENT_SCOPE)
        set(INCL_BASEDIR ${INCL_BASEDIR_CACHE} PARENT_SCOPE)
    endfunction()

    function(incl_src REQUIRED_ARG REQUIRED_FILE)
        set(${REQUIRED_ARG} ${${REQUIRED_ARG}} "${INCL_BASEDIR}${REQUIRED_FILE}.h" "${INCL_BASEDIR}${REQUIRED_FILE}.c" PARENT_SCOPE)
    endfunction()

    function(incl_file REQUIRED_ARG REQUIRED_FILE)
        set(${REQUIRED_ARG} ${${REQUIRED_ARG}} "${INCL_BASEDIR}${REQUIRED_FILE}" PARENT_SCOPE)
    endfunction()
else()
    # I am called from other project with add_subdirectory().
    message(STATUS "BOTTOM DOG")
endif()

add_subdirectory("src")