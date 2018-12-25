#include <nbtpp2/endianness.hpp>
#include <nbtpp2/converters.hpp>

namespace nbtpp2
{

const Endianness SYSTEM_ENDIANNESS = static_cast<Endianness>(
    ConvertToChars<std::uint16_t>{
        std::uint16_t{0x0001}
    }.chars[0]
);

}