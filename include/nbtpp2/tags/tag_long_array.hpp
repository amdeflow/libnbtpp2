#ifndef NBTPP2_TAG_LONG_ARRAY_HPP
#define NBTPP2_TAG_LONG_ARRAY_HPP

#include <cstdint>

#include "nbtpp2/endianness.hpp"
#include "number_array_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Long_Array
class TagLongArray: public NumberArrayTag<std::int64_t, std::uint64_t>
{
    using ElemT = std::int64_t;
    using ValT = std::vector<ElemT>;
public:
    explicit TagLongArray(ValT value);

    /**
     * @brief Read a TAG_Long_Array
     * @param in istream to read from
     * @param endianness Endianness to read TAG_Long_Array in
     * @return Read TagLongArray
     */
    static TagLongArray *read(std::istream &in, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_LONG_ARRAY_HPP
