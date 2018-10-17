#ifndef NBTPP2_ARRAY_TAG_HPP
#define NBTPP2_ARRAY_TAG_HPP

#include "nbtpp2/tag.hpp"

#include <functional>
#include <iostream>
#include <vector>
#include "nbtpp2/tag.hpp"
#include "nbtpp2/util.hpp"

namespace nbtpp2
{

namespace tags
{

/**
 * @brief Extendable class for reading and writing number array tags
 * @tparam NumberT Number type
 * @tparam NumberTUnsigned Unsigned number type (used for bitshifting)
 */
template<typename NumberT, typename NumberTUnsigned>
class NumberArrayTag: public Tag
{
    using ValT = std::vector<NumberT>;
public:
    ValT value;

    /**
     * @param value Value
     * @param type Tag type as TagType (used for identify())
     */
    explicit NumberArrayTag(ValT value, TagType type)
        : Tag{type}, value{std::move(value)}
    {}

    /**
     * @brief Write NumberArrayTag
     * @param out ostream to write to
     * @param endianness Endianness to write NumberArrayTag in
     */
    void write(std::ostream &out, Endianness endianness) override
    {
        write_number<std::int32_t, std::uint32_t>(static_cast<std::int32_t>(value.size()), out, endianness);
        for (auto &elem: value) {
            out.write(ConvertToChar<NumberT>{elem}.chars, sizeof(NumberT));
        }
    }

    /**
     * @brief Read tag of type @p ResultT (extending NumberArrayTag)
     * @tparam ResultT Result tag class type
     * @param in istream of file to read from
     * @param endianness Endianness to read the NumberArrayTag in
     * @return The resulting NumberArrayTag as @p ResultT
     */
    template<typename ResultT>
    static auto read(std::istream &in, Endianness endianness)
    {
        auto len = read_number<std::int32_t, std::uint32_t>(in, endianness);
        auto elems = ValT();
        for (std::int32_t i = 0; i < len; ++i) {
            auto elem = read_number<NumberT, NumberTUnsigned>(in, endianness);
            elems.push_back(elem);
        }
        return new ResultT{std::move(elems)};
    }
};

}

}

#endif //NBTPP2_ARRAY_TAG_HPP
