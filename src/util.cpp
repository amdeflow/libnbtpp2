#include <nbtpp2/util.hpp>

namespace nbtpp2
{

void write_string(const std::string &str, BinaryWriter &writer, Endianness endianness)
{
    write_number<std::uint16_t, std::uint16_t>(static_cast<std::uint16_t>(str.size()), writer, endianness);
    writer.write(str.data(), static_cast<std::uint16_t>(str.size()));
}

std::string read_string(BinaryReader &reader, Endianness endianness)
{
    auto len = read_number<std::uint16_t, std::uint16_t>(reader, endianness);
    auto res = std::string(len, ' ');
    reader.read(&res[0], len);
    return res;
}

void write_tag_id(TagType type, BinaryWriter &writer)
{
    write_number<std::uint8_t, std::uint8_t>(static_cast<std::uint8_t>(type), writer, SYSTEM_ENDIANNESS);
}

TagType read_tag_id(BinaryReader &reader)
{
    return read_number<TagType, std::uint8_t>(reader, SYSTEM_ENDIANNESS);
}

std::string tag_type_to_string(TagType tag_type)
{
    switch (tag_type) {
    case TagType::TagEnd: return "TAG_End";
    case TagType::TagByte: return "TAG_Byte";
    case TagType::TagShort: return "TAG_Short";
    case TagType::TagInt: return "TAG_Int";
    case TagType::TagLong: return "TAG_Long";
    case TagType::TagFloat: return "TAG_Float";
    case TagType::TagDouble: return "TAG_Double";
    case TagType::TagByteArray: return "TAG_Byte_Array";
    case TagType::TagString: return "TAG_String";
    case TagType::TagList: return "TAG_List";
    case TagType::TagCompound: return "TAG_Compound";
    case TagType::TagIntArray: return "TAG_Int_Array";
    case TagType::TagLongArray: return "TAG_Long_Array";
    default: return "";
    }
}

}