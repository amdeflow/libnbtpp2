#ifndef NBTPP2_TAG_DEF_HPP
#define NBTPP2_TAG_DEF_HPP

#include <memory>
#include "tag.hpp"

namespace nbtpp2
{

/**
 * @brief Read a tag
 * @param type Tag type (tag id) of the tag to read
 * @param in istream to read the tag from
 * @param endianness Endianness to read the tag in
 * @return Resulting tag as Tag *
 */
Tag *read_tag(TagType type, std::istream &in, Endianness endianness);

}

#endif //NBTPP2_TAG_DEF_HPP
