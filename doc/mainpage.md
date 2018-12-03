nbtpp2 {#mainpage}
======

## Getting started
Please read [including nbtpp2 in your CMake project](doc/setup_cmake.md) before continuing.

```cpp
#include <nbtpp2/nbt_file.hpp>
#include <iostream>

using namespace nbtpp2;

int main() {
    auto file = NbtFile("bigtest.nbt", Endianness::Big);
    std::cout << file.get_root()["intTest"]->as<tags::TagInt>().value
              << std::endl;
}
```
Download [bigtest.nbt](https://gitlab.com/rutgerbrf/libnbtpp2/raw/702681a21fdf627c1ff0bc85cee466e11d76b2a3/assets/bigtest.nbt)