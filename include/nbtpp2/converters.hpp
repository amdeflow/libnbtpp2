#ifndef NBTPP2_CONVERTERS_HPP
#define NBTPP2_CONVERTERS_HPP

#include <cstdint>

namespace nbtpp2
{

/**
 * @brief Basic union for converting between types
 * @tparam A Type converted from
 * @tparam B Type converted to
 */
template<typename A, typename B>
union Convert
{
    static_assert(sizeof(A) == sizeof(B), "A and B must have the same size");

    A a;
    B b;
};

/**
 * @brief Basic union for converting between char arrays and (unsigned) integer types
 * @tparam IntT Integer type converted to/from
 */
template<typename IntT>
union ConvertToChars
{
    IntT int_type;
    char chars[sizeof(IntT)];
};

}

#endif //NBTPP2_CONVERTERS_HPP
