#include "nbtpp2/tag_type.hpp"

std::string nbtpp2::tag_type_to_string(TagType tag_type)
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