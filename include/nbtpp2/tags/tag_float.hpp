#ifndef NBTPP2_TAG_FLOAT_HPP
#define NBTPP2_TAG_FLOAT_HPP

#include "number_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Float
class TagFloat: public NumberTag<float, std::uint32_t>
{
    using ValT = float;
public:
    explicit TagFloat(ValT value);

    /**
     * @brief Read a TAG_Float
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_Float in
     * @return Read TagFloat
     */
    static TagFloat *read(std::istream &in, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_FLOAT_HPP
