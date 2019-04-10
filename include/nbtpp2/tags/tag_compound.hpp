#ifndef NBTPP2_TAG_COMPOUND_HPP
#define NBTPP2_TAG_COMPOUND_HPP

#include <nbtpp2/tag.hpp>

#include <map>
#include <vector>

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
     * @param writer BinaryWriter to write to
     * @param endianness Endianness to write the TagCompound's contents in
     */
    void write(BinaryWriter &writer, Endianness endianness) override;

    /**
     * @brief Read a TAG_Compound
     * @param reader BinaryReader to read from
     * @param endianness Endianness to read the TAG_Compound's contents in
     * @return Read TagCompound
     */
    static TagCompound *read(BinaryReader &reader, Endianness endianness);

    /// @brief Custom destructor for deleting Tags in {@link value}
    ~TagCompound() override
    {
        for (auto &it : value) {
            delete it.second;
        }
    }

    /**
     * @brief Traverse TagCompound to find tag quickly
     * @param path_parts names of TagCompounds you want to traverse (last part is the tag you want as the result)
     * @return The found tag
     */
    Tag *traverse(std::vector<std::string> path_parts);
};

}

}

#endif //NBTPP2_TAG_COMPOUND_HPP
