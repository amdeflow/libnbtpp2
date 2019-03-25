Setting up nbtpp2 with CMake
============================

## Dependencies
This library currently only requires zlib and a working C++ compiler. On most UNIX-like systems this will already be installed, and you could use a
package manager like vcpkg on Windows to fetch it (or just download the sources or binaries).

## Installing libnbtpp2 in your project

1. Clone nbtpp2 into a directory in your project (for example, lib).  
   You probably want libnbtpp2 to be a submodule if you're using Git.
2. Add the directory of libnbtpp2 directory as a subdirectory in your project's CMakeLists.txt 

```cmake
add_subdirectory(lib/libnbtpp2)
```

3. Link the library to your own library or executable

```cmake
target_link_libraries(<your target> nbtpp2)
```