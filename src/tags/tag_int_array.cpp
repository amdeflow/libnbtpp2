#include <nbtpp2/tags/tag_int_array.hpp>

namespace nbtpp2
{

namespace tags
{

TagIntArray::TagIntArray(ValT value)
    : NumberArrayTag{std::move(value), TagType::TagIntArray}
{}

TagIntArray *TagIntArray::read(BinaryReader &reader, Endianness endianness)
{
    return NumberArrayTag::read<TagIntArray>(reader, endianness);
}

}

}