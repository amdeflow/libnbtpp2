#include "nbtpp2/tags/tag_byte.hpp"

namespace nbtpp2
{

namespace tags
{

TagByte::TagByte(ValType value)
    : NumberTag{value, TagType::TagByte}
{}

TagByte *TagByte::read(std::istream &in)
{
    return NumberTag::read<TagByte>(in, SYSTEM_ENDIANNESS);
}

}

}