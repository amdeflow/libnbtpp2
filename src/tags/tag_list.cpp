#include <nbtpp2/tags/tag_list.hpp>
#include <nbtpp2/util.hpp>

namespace nbtpp2
{

namespace tags
{

TagList::TagList(ValT value)
    : Tag{TagType::TagList}, value{std::move(value)}
{
    auto expected_tag_type = value.empty() ? TagType::TagEnd : value[0]->identify();
    for (auto &item : value) {
        if (item->identify() != expected_tag_type)
            throw std::runtime_error("TAG_List can only contain homogeneous tag types");
    }
}

void TagList::write(BinaryWriter &writer, Endianness endianness)
{
    auto expected_tag_type = value.empty() ? TagType::TagEnd : value[0]->identify();
    write_tag_id(expected_tag_type, writer);
    write_number<std::int32_t, std::uint32_t>(static_cast<std::int32_t>(value.size()), writer, endianness);
    auto i = std::int32_t{0};
    for (auto &it : value) {
        ++i;
        it->write(writer, endianness);
        if (i == INT32_MAX) break;
    }
}

TagList *TagList::read(BinaryReader &reader, Endianness endianness)
{
    auto value = ValT{};
    auto tag_type = read_tag_id(reader);
    auto len = read_number<std::int32_t, std::uint32_t>(reader, endianness);
    if (len > 0) {
        if (tag_type == TagType::TagEnd) {
            throw std::runtime_error("TAG_List with size greater than 0 is not allowed to have type TAG_End");
        }
        for (std::int32_t i = 0; i < len; ++i) {
            value.push_back(read_tag(tag_type, reader, endianness));
        }
    }

    return new TagList(value);
}

}

}