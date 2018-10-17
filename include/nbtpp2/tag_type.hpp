#ifndef NBTPP2_TAG_TYPE_HPP
#define NBTPP2_TAG_TYPE_HPP

#include <cstdint>
#include <string>

namespace nbtpp2
{

/**
 * @enum TagType
 * @brief Enum class of the valid NBT tags
 */
enum class TagType: std::uint8_t
{
    TagEnd, ///< TAG_End
    TagByte, ///< TAG_Byte
    TagShort, ///< TAG_Short
    TagInt, ///< TAG_Int
    TagLong, ///< TAG_Long
    TagFloat, ///< TAG_Float
    TagDouble, ///< TAG_Double
    TagByteArray, ///< TAG_Byte_Array
    TagString, ///< TAG_String
    TagList, ///< TAG_List
    TagCompound, ///< TAG_Compound
    TagIntArray, ///< TAG_Int_Array
    TagLongArray, ///< TAG_Long_Array
};

/**
 * @fn tag_type_to_string
 * @brief Converts a TagType to the std::string representation
 * @param tag_type The TagType
 * @return tag_type as std::string
 */
std::string tag_type_to_string(TagType tag_type);

}

#endif //NBTPP2_TAG_TYPE_HPP
