# nbtpp2 [![pipeline status](https://gitlab.com/rutgerbrf/libnbtpp2/badges/master/pipeline.svg)](https://gitlab.com/rutgerbrf/libnbtpp2/commits/master)
A C++14 library for creating, opening and modifying NBT files

## Usage

```cpp
#include <nbtpp2/nbt_file.hpp>
#include <iostream>

using namespace nbtpp2;

int main() {
    auto file = NbtFile("bigtest.nbt", Endianness::Big);
    std::cout << file.get_root_tag_compound()["intTest"]->as<tags::TagInt>().value
              << std::endl;
}
```

## Compiler compatibility
Compilation has been tested on GCC and Clang. Support for other compilers is not guaranteed (though merge requests are welcome).  
At the time of writing nbtpp2 compiles on MSVC (I used vcpkg for compiling with zlib) but the tests do not.
Perhaps you could make them compile with some less aggressive compiler flags.

[Documentation](https://rutgerbrf.gitlab.io/libnbtpp2)