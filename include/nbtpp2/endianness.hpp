#ifndef NBTPP2_ENDIANNESS_HPP
#define NBTPP2_ENDIANNESS_HPP

#include <cstdint>

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
    reinterpret_cast<const char *>(
        new std::uint16_t{0x0001}
    )[0]
);

}

#endif //NBTPP2_ENDIANNESS_HPP
