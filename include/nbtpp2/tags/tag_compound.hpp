#ifndef NBTPP2_TAG_COMPOUND_HPP
#define NBTPP2_TAG_COMPOUND_HPP

#include "nbtpp2/tag.hpp"
#include "nbtpp2/read_tag.hpp"
#include "nbtpp2/util.hpp"

#include <map>

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_Compound
class TagCompound: public Tag
{
    using ValT = std::map<std::string, Tag *>;
public:
    ValT value;

    explicit TagCompound(ValT value);

    /**
     * @brief Write a TagCompound to an ostream
     * @param out ostream to write to
     * @param endianness Endianness to write the TagCompound's contents in
     */
    void write(std::ostream &out, Endianness endianness) override;

    /**
     * @brief Read a TAG_Compound
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_Compound's contents in
     * @return Read TagCompound
     */
    static TagCompound *read(std::istream &in, Endianness endianness);

    /// @brief Custom destructor for deleting Tags in {@link value}
    ~TagCompound() override
    {
        for (auto &it: value) {
            delete it.second;
        }
    }
};

}

}

#endif //NBTPP2_TAG_COMPOUND_HPP
