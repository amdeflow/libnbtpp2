#include <nbtpp2/util.hpp>
#include <nbtpp2/tags/tag_compound.hpp>

#include <utility>
#include <iostream>
#include <nbtpp2/all_tags.hpp>

namespace nbtpp2
{

namespace tags
{

TagCompound::TagCompound(ValT value)
    : Tag{TagType::TagCompound}, value{std::move(value)}
{}

void TagCompound::write(BinaryWriter &writer, Endianness endianness)
{
    for (auto &it : value) {
        write_tag_id(it.second->identify(), writer);
        write_string(it.first, writer, endianness);
        it.second->write(writer, endianness);
    }
    write_tag_id(TagType::TagEnd, writer);
}

TagCompound *TagCompound::read(BinaryReader &reader, Endianness endianness)
{
    auto value = ValT{};
    while (true) {
        auto id = read_tag_id(reader);
        if (id == TagType::TagEnd) break;
        auto name = read_string(reader, endianness);
        value[name] = read_tag(id, reader, endianness);
    }
    return new TagCompound(value);
}

Tag *TagCompound::traverse(std::vector<std::string> path_parts)
{
    if (!path_parts.empty()) {
        if (path_parts.size() == 1) {
            return value[path_parts[0]];
        }
        switch (value[path_parts[0]]->identify()) {
        case TagType::TagCompound:
            return value[path_parts[0]]->as<TagCompound>().traverse(
                std::vector<std::string>{
                    path_parts.begin() + 1,
                    path_parts.end()
                }
            );
        case TagType::TagList:
            return value[path_parts[0]]->as<TagList>().traverse(
                std::vector<std::string>{
                    path_parts.begin() + 1,
                    path_parts.end()
                }
            );
        default:
            throw std::runtime_error("Expected TagCompound or TagList for path part");
        }
    }
    return this;
}

}

}