#ifndef NBTPP2_UTIL_HPP
#define NBTPP2_UTIL_HPP

#include <cstdint>
#include <ostream>
#include <istream>
#include <string>
#include "converters.hpp"
#include "endianness.hpp"
#include "tag_type.hpp"

namespace nbtpp2
{

/**
 * @brief Reverse an unsigned integer
 * @tparam UintT Type of the unsigned integer
 * @param value Value of the unsigned integer
 * @return Reversed unsigned integer
 */
template<typename UintT>
auto reverse_uint(UintT value)
{
    UintT result = 0;
    for (std::size_t i = 0; i < sizeof(value); ++i) {
        result |= ((value >> (i * 8)) & 0xFF) << ((sizeof(value) - i) * 8 - 8);
    }
    return result;
}

/**
 * @brief Reverse an unsigned integer if the system endianness does not equal the target endianness
 * @tparam UintT Type of the unsigned integer
 * @param value Value of the unsigned integer
 * @param target_endianness Target endianness
 * @return Reversed unsigned integer
 */
template<typename UintT>
auto optional_reverse_uint(UintT value, Endianness target_endianness)
{
    return target_endianness != SYSTEM_ENDIANNESS ? reverse_uint(value) : value;
}

/**
 * @brief Write a number to an ostream
 * @tparam NumberT (signed) input number type
 * @tparam NumberTUnsigned Unsigned version of NumberT (can also be the same if NumberT is already unsigned)
 * @param value Value of the number in NumberT
 * @param out ostream to write to
 * @param endianness Endianness to write the number in
 */
template<typename NumberT, typename NumberTUnsigned>
void write_number(NumberT value, std::ostream &out, Endianness endianness)
{
    static_assert(sizeof(NumberT) == sizeof(NumberTUnsigned), "NumberT and NumberTUnsigned must have the same size");

    out.write(
        ConvertToChars<NumberTUnsigned>{
            optional_reverse_uint(Convert<NumberT, NumberTUnsigned>{value}.b, endianness)
        }.chars,
        sizeof(NumberTUnsigned)
    );
}

/**
 * @brief Write a string to an ostream
 * @param str String to write
 * @param out ostream to write to
 * @param endianness Endianness to write the string's length in
 */
void write_string(const std::string &str, std::ostream &out, Endianness endianness);

/**
 * @brief Read a number from an istream
 * @tparam NumberT (signed) number type
 * @tparam NumberTUnsigned Unsigned version of NumberT (can also be the same if NumberT is already unsigned)
 * @param in istream to read from
 * @param endianness Endianness to read the number in
 * @return Read number
 */
template<typename NumberT, typename NumberTUnsigned>
auto read_number(std::istream &in, Endianness endianness)
{
    static_assert(sizeof(NumberT) == sizeof(NumberTUnsigned), "NumberT and NumberTUnsigned must have the same size");

    auto converter = ConvertToChars<NumberTUnsigned>{0};
    in.read(converter.chars, sizeof(NumberTUnsigned));
    auto result = Convert<NumberTUnsigned, NumberT>{
        optional_reverse_uint(
            converter.int_type,
            endianness
        )
    };

    return result.b;
}

/**
 * @brief Read a string from an istream
 * @param in ostream to read from
 * @param endianness Endianness to read the string's length in
 * @return Read string
 */
std::string read_string(std::istream &in, Endianness endianness);

/**
 * @brief Write a TagType (tag id) to an ostream
 * @param type TagType to write (tag id)
 * @param out ostream to write to
 */
void write_tag_id(TagType type, std::ostream &out);

/**
 * @brief Read a TagType (tag id) from an istream
 * @param in ostream to read from
 * @return Tag id (TagType)
 */
TagType read_tag_id(std::istream &in);

}

#endif //NBTPP2_UTIL_HPP
