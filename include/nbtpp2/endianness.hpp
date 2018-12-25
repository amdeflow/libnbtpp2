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
extern const Endianness SYSTEM_ENDIANNESS;

}

#endif //NBTPP2_ENDIANNESS_HPP
