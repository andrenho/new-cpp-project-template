# New project template: C++, SDL, Lua

A template for new C++ projects. Meant mostly for games but can be used for anything else.

It includes:
  - Cmake configuration files
  - Pre-configured set of C++ warnings
  - Automatically download git submodules
  - Create and run a SDL environment
    - Optionally embed SDL resources in final binary
  - Lua library
    - Optionally embed Lua scripts in final binary
  - Testing
  - valgrind leak checking
  - github actions
   
To start:
  - Change project name and version in `CMakeLists.txt`
  - Remove sections that are not going to be used
  - Update the LICENSE file, if necessary
  - Rewrite this README
    - Instruct users to run `./build.sh` first
