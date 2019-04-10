#ifndef NBTPP2_TAG_LONG_HPP
#define NBTPP2_TAG_LONG_HPP

#include <nbtpp2/number_tag.hpp>

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Long
class TagLong: public NumberTag<std::int64_t, std::uint64_t>
{
    using ValT = std::int64_t;
public:
    explicit TagLong(ValT value);

    /**
     * @brief Read a TAG_Long
     * @param reader BinaryReader to read from
     * @param endianness Endianness to read the TAG_Long in
     * @return Read TagLong
     */
    static TagLong *read(BinaryReader &reader, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_LONG_HPP
