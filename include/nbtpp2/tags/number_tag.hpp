#ifndef NBTPP2_INT_TAG_HPP
#define NBTPP2_INT_TAG_HPP

#include <iostream>
#include "nbtpp2/tag.hpp"
#include "nbtpp2/util.hpp"

namespace nbtpp2
{

namespace tags
{

template<typename NumberT, typename NumberTUnsigned>
class NumberTag: public Tag
{
public:
    NumberT value = 0;

    /**
     * @param value Value
     * @param type Tag type as TagType (used for identify())
     */
    explicit NumberTag(NumberT value, TagType type)
        : Tag{type}, value{value}
    {}

    /**
     * @brief Write NumberTag
     * @param out ostream to write to
     * @param endianness Endianness to write NumberTag in
     */
    void write(std::ostream &out, Endianness endianness) override
    {
        write_number<NumberT, NumberTUnsigned>(value, out, endianness);
    }

    /**
     * @brief Read tag of type @p ResultT (extending NumberTag)
     * @tparam ResultT Result tag class type
     * @param in istream to read from
     * @param endianness Endianness to read the NumberTag in
     * @return The resulting NumberTag as @p ResultT
     */
    template<typename ResultT>
    static auto read(std::istream &in, Endianness endianness)
    {
        return new ResultT{read_number<NumberT, NumberTUnsigned>(in, endianness)};
    }
};

}

}

#endif //NBTPP2_INT_TAG_HPP
