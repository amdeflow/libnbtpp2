#include "nbtpp2/read_tag.hpp"
#include "nbtpp2/all_tags.hpp"

namespace nbtpp2
{

Tag *read_tag(TagType type, std::istream &in, Endianness endianness)
{
    using namespace tags;

    switch (type) {
    case TagType::TagByte: return TagByte::read(in);
    case TagType::TagShort: return TagShort::read(in, endianness);
    case TagType::TagInt: return TagInt::read(in, endianness);
    case TagType::TagLong: return TagLong::read(in, endianness);
    case TagType::TagFloat: return TagFloat::read(in, endianness);
    case TagType::TagDouble: return TagDouble::read(in, endianness);
    case TagType::TagByteArray: return TagByteArray::read(in, endianness);
    case TagType::TagString: return TagString::read(in, endianness);
    case TagType::TagList: return TagList::read(in, endianness);
    case TagType::TagCompound: return TagCompound::read(in, endianness);
    case TagType::TagIntArray: return TagIntArray::read(in, endianness);
    case TagType::TagLongArray: return TagLongArray::read(in, endianness);
    default: throw std::runtime_error("tag type not matched");
    }
}

}