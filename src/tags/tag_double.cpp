#include <nbtpp2/tags/tag_double.hpp>

namespace nbtpp2
{

namespace tags
{

TagDouble::TagDouble(ValT value)
    : NumberTag{value, TagType::TagDouble}
{}

TagDouble *TagDouble::read(BinaryReader &reader, Endianness endianness)
{
    return NumberTag::read<TagDouble>(reader, endianness);
}

}

}