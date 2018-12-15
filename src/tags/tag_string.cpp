#include "nbtpp2/tags/tag_string.hpp"
#include "nbtpp2/util.hpp"

namespace nbtpp2
{

namespace tags
{

TagString::TagString(ValT value)
    : Tag{TagType::TagString}, value{std::move(value)}
{}

void TagString::write(std::ostream &out, Endianness endianness)
{
    write_string(value, out, endianness);
}

TagString *TagString::read(std::istream &in, Endianness endianness)
{
    return new TagString{read_string(in, endianness)};
}

}

}