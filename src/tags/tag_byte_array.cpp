#include "nbtpp2/tags/tag_byte_array.hpp"

namespace nbtpp2
{

namespace tags
{

TagByteArray::TagByteArray(ValT value)
    : NumberArrayTag{std::move(value), TagType::TagByteArray}
{}

TagByteArray *TagByteArray::read(std::istream &in, Endianness endianness)
{
    return NumberArrayTag::read<TagByteArray>(in, endianness);
}

}

}