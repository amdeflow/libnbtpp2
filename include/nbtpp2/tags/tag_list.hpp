#ifndef NBTPP2_TAG_LIST_HPP
#define NBTPP2_TAG_LIST_HPP

#include <nbtpp2/tag.hpp>

#include <vector>

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_List
class TagList: public Tag
{
    using ValT = std::vector<Tag *>;
public:
    ValT value;

    explicit TagList(ValT value);

    /**
     * @brief Write a TAG_List
     * @param writer BinaryWriter to write to
     * @param endianness Endianness to write the TAG_List in
     */
    void write(BinaryWriter &writer, Endianness endianness) override;

    /**
     * @brief Read a TAG_List
     * @param reader BinaryReader to read from
     * @param endianness Endianness to read the TAG_List in
     * @return Read TAG_List
     */
    static TagList *read(BinaryReader &reader, Endianness endianness);

    Tag *traverse(std::vector<std::string> path_parts);

    /// @brief Custom destructor to delete tags in {@link value}
    ~TagList() override
    {
        for (auto &it : value) {
            delete it;
        }
    }
};

}

}

#endif //NBTPP2_TAG_LIST_HPP
