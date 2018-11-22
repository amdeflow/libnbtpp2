#ifndef NBTPP2_TAG_LIST_HPP
#define NBTPP2_TAG_LIST_HPP

#include <vector>
#include "nbtpp2/read_tag.hpp"
#include "nbtpp2/tag.hpp"
#include "nbtpp2/util.hpp"

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
     * @param out ostream to write to
     * @param endianness Endianness to write the TAG_List in
     */
    void write(std::ostream &out, Endianness endianness) override;

    /**
     * @brief Read a TAG_List
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_List in
     * @return Read TAG_List
     */
    static TagList *read(std::istream &in, Endianness endianness);

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
