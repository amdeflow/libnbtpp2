#include "nbtpp2/tags/tag_long_array.hpp"

namespace nbtpp2
{

namespace tags
{

TagLongArray::TagLongArray(ValT value)
    : NumberArrayTag{std::move(value), TagType::TagLongArray}
{}

TagLongArray *TagLongArray::read(std::istream &in, Endianness endianness)
{
    return NumberArrayTag::read<TagLongArray>(in, endianness);
}

}

}