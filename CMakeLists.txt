cmake_minimum_required(VERSION 3.12)
project(nbtpp2 VERSION 1.0.0 DESCRIPTION "A C++14 library for creating, opening and modifying NBT files" LANGUAGES CXX)

option(NBTPP2_BUILD_TESTS "NBTPP2_BUILD_TESTS" OFF)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(ZLIB REQUIRED)

set(nbtpp2_SRC
        include/nbtpp2/tag.hpp
        include/nbtpp2/tag_type.hpp
        include/nbtpp2/endianness.hpp
        include/nbtpp2/util.hpp
        include/nbtpp2/tags/tag_byte.hpp
        include/nbtpp2/tags/tag_short.hpp
        include/nbtpp2/tags/tag_int.hpp
        include/nbtpp2/tags/tag_long.hpp
        include/nbtpp2/tags/number_tag.hpp
        include/nbtpp2/tags/tag_float.hpp
        include/nbtpp2/tags/tag_double.hpp
        include/nbtpp2/tags/number_array_tag.hpp
        include/nbtpp2/tags/tag_byte_array.hpp
        include/nbtpp2/tags/tag_int_array.hpp
        include/nbtpp2/tags/tag_long_array.hpp
        include/nbtpp2/tags/tag_compound.hpp
        include/nbtpp2/tags/tag_string.hpp
        include/nbtpp2/read_tag.hpp
        include/nbtpp2/tags/tag_list.hpp
        src/read_tag.cpp
        src/tags/tag_type.cpp
        src/util.cpp
        include/nbtpp2/nbt_file.hpp
        src/nbt_file.cpp
        src/tags/tag_compound.cpp
        src/tags/tag_list.cpp
        src/tags/tag_byte.cpp
        src/tags/tag_byte_array.cpp
        src/tags/tag_double.cpp
        src/tags/tag_float.cpp
        src/tags/tag_int.cpp
        src/tags/tag_int_array.cpp
        src/tags/tag_long.cpp
        src/tags/tag_long_array.cpp
        src/tags/tag_short.cpp
        src/tags/tag_string.cpp
        src/tags/tag.cpp
        include/nbtpp2/nbtpp2_def.hpp
        include/nbtpp2/all_tags.hpp
        include/nbtpp2/converters.hpp
        )

option(NBTPP2_BUILD_STATIC "Build nbtpp2 as a static library" OFF)

if (NBTPP2_BUILD_STATIC)
    add_definitions(-DNBTPP2_STATIC_BUILD)
    add_library(${PROJECT_NAME} STATIC ${nbtpp2_SRC})
else (NBTPP2_BUILD_STATIC)
    add_library(${PROJECT_NAME} SHARED ${nbtpp2_SRC})
endif (NBTPP2_BUILD_STATIC)

target_include_directories(nbtpp2 PUBLIC include)
target_link_libraries(nbtpp2 PRIVATE Boost::iostreams ZLIB::ZLIB)

if (${NBTPP2_BUILD_TESTS})
    add_executable(tests src/tests.cpp)
    target_link_libraries(tests nbtpp2)
endif()

# Copy bigtest.nbt for the tests
file(COPY assets/bigtest.nbt DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS nbtpp2 DESTINATION lib)
export(PACKAGE nbtpp2)
install(DIRECTORY include/nbtpp2 DESTINATION include)