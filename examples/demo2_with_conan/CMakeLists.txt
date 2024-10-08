cmake_minimum_required(VERSION 3.7.2)

# This add conan package manager support
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "conan_provider.cmake")

# Export CompileCommands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDK_ENV_NAME "MY_SDK_PATH")
set(CUSTOM_COMPONENTS_PATH_ENV_NAME "CUSTOM_COMPONENTS_PATH")

set(SDK_PATH_ENV $ENV{${SDK_ENV_NAME}})
set(CUSTOM_COMPONENTS_PATH_ENV $ENV{${CUSTOM_COMPONENTS_PATH_ENV_NAME}})

# Get SDK path
if(NOT SDK_PATH)
    # NOTE:Change this to the corret path:'../../'
    get_filename_component(SDK_PATH ../../ ABSOLUTE)
    if(SDK_PATH_ENV)
        if(EXISTS ${SDK_PATH_ENV})
            set(SDK_PATH ${SDK_PATH_ENV})
        else()
            message(FATAL_ERROR "Env variable '${SDK_ENV_NAME}' set, but '${SDK_PATH_ENV}', path not exists")
        endif()
    endif()
endif()
if(NOT CUSTOM_COMPONENTS_PATH)
    if(CUSTOM_COMPONENTS_PATH_ENV)
        if(EXISTS ${CUSTOM_COMPONENTS_PATH_ENV})
            set(CUSTOM_COMPONENTS_PATH ${CUSTOM_COMPONENTS_PATH_ENV})
        else()
            message(FATAL_ERROR "Env variable '${CUSTOM_COMPONENTS_PATH_ENV_NAME}' set, but '${CUSTOM_COMPONENTS_PATH_ENV}', path not exists")
        endif()
    endif()
endif()

# Check SDK Path
if(NOT EXISTS ${SDK_PATH})
    message(FATAL_ERROR "SDK path Error, Please set SDK_PATH or ${SDK_ENV_NAME} variable")
endif()

# Get Toolchain path
if(NOT CONFIG_TOOLCHAIN_PATH)
    if(EXISTS $ENV{MY_TOOLCHAIN_PATH})
        set(CONFIG_TOOLCHAIN_PATH $ENV{MY_TOOLCHAIN_PATH})
    endif()
endif()
## Add preprocessor definitions for whole project
# add_definitions(-DAAAAA=1)

# Call compile
include(${SDK_PATH}/tools/cmake/compile.cmake)


# Project Name, default the same as project directory name
get_filename_component(parent_dir ${CMAKE_PARENT_LIST_FILE} DIRECTORY)
get_filename_component(project_dir_name ${parent_dir} NAME)

set(PROJECT_NAME ${project_dir_name}) # change this var if don't want the same as directory's

message("-- PROJECT_NAME:${PROJECT_NAME}")
project(${PROJECT_NAME})