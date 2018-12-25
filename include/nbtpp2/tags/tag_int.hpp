#ifndef NBTPP2_TAG_INT_HPP
#define NBTPP2_TAG_INT_HPP

#include "nbtpp2/number_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Int
class TagInt: public NumberTag<std::int32_t, std::uint32_t>
{
    using ValT = std::int32_t;
public:
    explicit TagInt(ValT value);

    /**
     * @brief Read a TAG_Int
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_Int in
     * @return Read TagInt
     */
    static TagInt *read(BinaryReader &reader, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_INT_HPP
