#ifndef NBTPP2_TAG_STRING_HPP
#define NBTPP2_TAG_STRING_HPP

#include "nbtpp2/tag.hpp"
#include "nbtpp2/util.hpp"

namespace nbtpp2
{

namespace tags
{

/// @brief TAG_String
class TagString: public Tag
{
    using ValT = std::string;
public:
    ValT value;

    explicit TagString(ValT value);

    /**
     * @brief Write a TAG_String
     * @param out istream to Write
     * @param endianness Endianness to write the TAG_String's length in
     */
    void write(std::ostream &out, Endianness endianness) override;

    /**
     * @brief Read a TAG_String
     * @param in istream to read from
     * @param endianness Endianness to read the TAG_String's length in
     * @return Read TagString
     */
    static TagString *read(std::istream &in, Endianness endianness);
};

}

}

#endif //NBTPP2_TAG_STRING_HPP
