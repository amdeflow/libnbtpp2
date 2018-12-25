#include "nbtpp2/all_tags.hpp"

namespace nbtpp2
{

Tag *read_tag(TagType type, BinaryReader &reader, Endianness endianness)
{
    using namespace tags;

    switch (type) {
    case TagType::TagByte: return TagByte::read(reader);
    case TagType::TagShort: return TagShort::read(reader, endianness);
    case TagType::TagInt: return TagInt::read(reader, endianness);
    case TagType::TagLong: return TagLong::read(reader, endianness);
    case TagType::TagFloat: return TagFloat::read(reader, endianness);
    case TagType::TagDouble: return TagDouble::read(reader, endianness);
    case TagType::TagByteArray: return TagByteArray::read(reader, endianness);
    case TagType::TagString: return TagString::read(reader, endianness);
    case TagType::TagList: return TagList::read(reader, endianness);
    case TagType::TagCompound: return TagCompound::read(reader, endianness);
    case TagType::TagIntArray: return TagIntArray::read(reader, endianness);
    case TagType::TagLongArray: return TagLongArray::read(reader, endianness);
    default: throw std::runtime_error("tag type not matched");
    }
}

}