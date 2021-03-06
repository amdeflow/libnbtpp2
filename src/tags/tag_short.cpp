#include <nbtpp2/tags/tag_short.hpp>

namespace nbtpp2
{

namespace tags
{

TagShort::TagShort(ValT value)
    : NumberTag{value, TagType::TagShort}
{}

TagShort *TagShort::read(BinaryReader &reader, Endianness endianness)
{
    return NumberTag::read<TagShort>(reader, endianness);
}

}

}