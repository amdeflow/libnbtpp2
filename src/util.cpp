#include "nbtpp2/util.hpp"

namespace nbtpp2
{

void write_string(const std::string &str, std::ostream &out, Endianness endianness)
{
    write_number<std::uint16_t, std::uint16_t>(static_cast<std::uint16_t>(str.size()), out, endianness);
    out.write(str.data(), static_cast<std::uint16_t>(str.size()));
}

std::string read_string(std::istream &in, Endianness endianness)
{
    auto len = read_number<std::uint16_t, std::uint16_t>(in, endianness);
    auto res = std::string(len, ' ');
    in.read(&res[0], static_cast<std::size_t>(len));
    return res;
}

void write_tag_id(TagType type, std::ostream &out)
{
    write_number<std::uint8_t, std::uint8_t>(static_cast<std::uint8_t>(type), out, SYSTEM_ENDIANNESS);
}

TagType read_tag_id(std::istream &in)
{
    return read_number<TagType, std::uint8_t>(in, SYSTEM_ENDIANNESS);
}

}