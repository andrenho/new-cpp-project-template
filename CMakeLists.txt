#
# project definitions
#

cmake_minimum_required(VERSION 3.30)

project(template-cpp-sdl-lua
    VERSION 0.0.1
    DESCRIPTION "Template for C++/SDL/Lua projects"
    LANGUAGES C CXX ASM
)

#
# configuration
#

set_property(GLOBAL PROPERTY C_STANDARD 17)
set_property(GLOBAL PROPERTY CXX_STANDARD 23)
set_property(GLOBAL PROPERTY CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
set_property(GLOBAL PROPERTY LINK_WHAT_YOU_USE TRUE)

# warnings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(warnings -Wall -Wextra -Wformat-nonliteral -Wundef -Wshadow -Wwrite-strings -Wfloat-equal -Wswitch-default -Wmissing-format-attribute -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=malloc -Wsuggest-attribute=returns_nonnull -Wsuggest-attribute=format -Wsuggest-attribute=cold -Wswitch-enum -Wmissing-noreturn -Wno-unused-parameter -Wno-unused)
endif()

# try to use ccache, if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

#
# libraries
#

#
# executable
#

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cc
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${warnings})
