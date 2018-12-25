#include "nbtpp2/tags/tag_string.hpp"
#include "nbtpp2/util.hpp"

namespace nbtpp2
{

namespace tags
{

TagString::TagString(ValT value)
    : Tag{TagType::TagString}, value{std::move(value)}
{}

void TagString::write(BinaryWriter &writer, Endianness endianness)
{
    write_string(value, writer, endianness);
}

TagString *TagString::read(BinaryReader &reader, Endianness endianness)
{
    return new TagString{read_string(reader, endianness)};
}

}

}