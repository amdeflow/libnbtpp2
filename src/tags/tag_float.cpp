#include <nbtpp2/tags/tag_float.hpp>

namespace nbtpp2
{

namespace tags
{

TagFloat::TagFloat(ValT value)
    : NumberTag{value, TagType::TagFloat}
{}

TagFloat *TagFloat::read(BinaryReader &reader, Endianness endianness)
{
    return NumberTag::read<TagFloat>(reader, endianness);
}

}

}