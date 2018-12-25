#include <nbtpp2/tags/tag_byte_array.hpp>

namespace nbtpp2
{

namespace tags
{

TagByteArray::TagByteArray(ValT value)
    : NumberArrayTag{std::move(value), TagType::TagByteArray}
{}

TagByteArray *TagByteArray::read(BinaryReader &reader, Endianness endianness)
{
    return NumberArrayTag::read<TagByteArray>(reader, endianness);
}

}

}