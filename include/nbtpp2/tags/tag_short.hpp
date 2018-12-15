#ifndef NBTPP2_TAG_SHORT_HPP
#define NBTPP2_TAG_SHORT_HPP

#include "number_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Short
class TagShort: public NumberTag<std::int16_t, std::uint16_t>
{
    using ValT = std::int16_t;
public:
    explicit TagShort(ValT value);

    /**
     * @brief Read a TAG_Short
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_Short in
     * @return Read TagShort
     */
    static TagShort *read(std::istream &in, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_SHORT_HPP
