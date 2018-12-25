#ifndef NBTPP2_TAG_DOUBLE_HPP
#define NBTPP2_TAG_DOUBLE_HPP

#include "nbtpp2/number_tag.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Double
class TagDouble: public NumberTag<double, std::uint64_t>
{
    using ValT = double;
public:
    explicit TagDouble(ValT value);

    /**
     * @brief Read a TAG_Double
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_Double in
     * @return Read TagDouble
     */
    static TagDouble *read(BinaryReader &reader, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_DOUBLE_HPP
