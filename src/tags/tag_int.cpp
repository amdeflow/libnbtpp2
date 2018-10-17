#include "nbtpp2/tags/tag_int.hpp"

namespace nbtpp2
{

namespace tags
{

TagInt::TagInt(ValT value)
    : NumberTag{value, TagType::TagInt}
{}

TagInt *TagInt::read(std::istream &in, Endianness endianness)
{
    return NumberTag::read<TagInt>(in, endianness);
}

}

}