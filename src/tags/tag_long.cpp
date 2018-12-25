#include "nbtpp2/tags/tag_long.hpp"

namespace nbtpp2
{

namespace tags
{

TagLong::TagLong(ValT value)
    : NumberTag{value, TagType::TagLong}
{}

TagLong *TagLong::read(BinaryReader &reader, Endianness endianness)
{
    return NumberTag::read<TagLong>(reader, endianness);
}

}

}