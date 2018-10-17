#ifndef NBTPP2_TAG_INT_ARRAY_HPP
#define NBTPP2_TAG_INT_ARRAY_HPP

#include <cstdint>
#include "number_array_tag.hpp"
#include "tag_byte_array.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Int_Array
class TagIntArray: public NumberArrayTag<std::int32_t, std::uint32_t>
{
    using ElemT = std::int32_t;
    using ValT = std::vector<ElemT>;
public:
    explicit TagIntArray(ValT value);

    /**
     * @brief Read a TAG_Int_Array
     * @param in istream to read from
     * @param endianness Endianness to read TAG_Int_Array in
     * @return Read TagIntArray
     */
    static TagIntArray *read(std::istream &in, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_INT_ARRAY_HPP