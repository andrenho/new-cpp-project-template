#
# project definitions
#

cmake_minimum_required(VERSION 3.30)

project(template-cpp-sdl-lua
    VERSION 0.0.1
    DESCRIPTION "Template for C++/SDL/Lua projects"
    LANGUAGES C CXX ASM)

#
# configuration
#

set_property(GLOBAL PROPERTY C_STANDARD 17)
set_property(GLOBAL PROPERTY CXX_STANDARD 23)
set(warnings "-Wall -Wextra -Wformat-nonliteral -Wbad-function-cast -Wundef -Wshadow -Wwrite-strings -Wfloat-equal -Wswitch-default -Wmissing-format-attribute -Wsuggest-attribute -Wswitch-enum -Wmissing-noreturn")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(warnings "${warnings} -Wno-unused-parameter -Wno-unused")
endif()

#
# libraries
#

#
# executable
#

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cc)
