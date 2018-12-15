#ifndef NBTPP2_TAG_BYTE_ARRAY_HPP
#define NBTPP2_TAG_BYTE_ARRAY_HPP

#include "number_array_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Byte_Array
class TagByteArray: public NumberArrayTag<std::int8_t, std::uint8_t>
{
    using ElemT = std::int8_t;
    using ValT = std::vector<ElemT>;
public:
    explicit TagByteArray(ValT value);

    /**
     * @brief Read a TAG_Byte_Array
     * @param in istream to read from
     * @param endianness Endianness to read TAG_Byte_Array's length in
     * @return Read TagByteArray
     */
    static TagByteArray *read(std::istream &in, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_BYTE_ARRAY_HPP
