#ifndef NBTPP2_ENDIANNESS_HPP
#define NBTPP2_ENDIANNESS_HPP

#include <cstdint>
#include "converters.hpp"

namespace nbtpp2
{

/**
 * @enum Endianness
 * @brief Specifies endianness (big or little)
 */
enum class Endianness
{
    Big, ///< Big-endian
    Little, ///< Little-endian
};

/**
 * @var SYSTEM_ENDIANNESS
 * @brief Calculates system endianness statically
 */
const auto SYSTEM_ENDIANNESS = static_cast<Endianness>( // NOLINT(cert-err58-cpp)
    ConvertToChar<std::uint16_t>{
        std::uint16_t{0x0001}
    }.chars[0]
);

}

#endif //NBTPP2_ENDIANNESS_HPP
