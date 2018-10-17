#include <utility>

#include <iostream>
#include "nbtpp2/tags/tag_compound.hpp"

namespace nbtpp2
{

namespace tags
{

TagCompound::TagCompound(ValT value)
    : Tag{TagType::TagCompound}, value{std::move(value)}
{}

void TagCompound::write(std::ostream &out, Endianness endianness)
{
    for (auto &it: value) {
        write_tag_id(it.second->identify(), out);
        write_string(it.first, out, endianness);
        it.second->write(out, endianness);
    }
    write_tag_id(TagType::TagEnd, out);
}

TagCompound *TagCompound::read(std::istream &in, Endianness endianness)
{
    auto value = ValT{};
    while (true) {
        auto id = read_tag_id(in);
        if (id == TagType::TagEnd) break;
        auto name = read_string(in, endianness);
        value[name] = read_tag(id, in, endianness);
    }
    return new TagCompound(value);
}

}

}