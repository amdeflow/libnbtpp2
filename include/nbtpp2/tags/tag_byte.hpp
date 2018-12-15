#ifndef NBTPP2_TAG_BYTE_HPP
#define NBTPP2_TAG_BYTE_HPP

#include "number_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Byte
class TagByte: public NumberTag<std::int8_t, std::uint8_t>
{
    using ValType = std::int8_t;
public:
    explicit TagByte(ValType value);

    /**
     * @brief Read a TAG_Byte
     * @param in istream to read from
     * @return Read TagByte
     */
    static TagByte *read(std::istream &in);
};

}

}

#endif //NBTPP2_TAG_BYTE_HPP
