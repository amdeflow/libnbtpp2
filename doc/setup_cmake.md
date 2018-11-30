Setting up nbtpp2 with CMake
============================

## Dependencies
This library requires Boost (iostreams) and zlib. Zlib will probably already
be installed if you're running a Linux distribution, but Boost (iostreams) might not.

To install on Arch Linux: `# pacman -S boost`  
On Ubuntu you might have some problems, because at the time of writing
Ubuntu does not provide static versions of the Boost libraries, which libnbtpp2
currently requires.

## Installing libnbtpp2 in your project

1. Clone nbtpp2 into a directory in your project (for example, lib).  
   You probably want libnbtpp2 to be a submodule if you're using git.
2. Add the direcotry of libnbtpp2 directory as a subdirectory in your project's CMakeLists.txt 

```cmake
add_subdirectory(lib/libnbtpp2)
```

3. Link the library to your own library or executable

```cmake
target_link_libraries(<your target> nbtpp2)
```