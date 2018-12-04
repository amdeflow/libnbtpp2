#ifndef NBTPP2_TAG_HPP
#define NBTPP2_TAG_HPP

#include <stdexcept>
#include "tag_type.hpp"
#include "nbtpp2/endianness.hpp"

namespace nbtpp2
{

/// @brief The namespace for all classes extending Tag
namespace tags
{
}

/**
 * @class Tag
 * @brief Tag is the abstract class all tags must extend to work with nbtpp2
 */
class Tag
{
    const TagType type;
public:
    /**
     * @brief Tag constructor
     * @param type The tag type as TagType (used for identify())
     */
    explicit Tag(TagType type);

    /**
     * @brief Destructor for Tag (overridable)
     */
    virtual ~Tag() = default;

    /**
     * @brief Write tag to ostream with desired endianness
     * @param out ostream to write the tag to
     * @param endianness Endianness to write tag to the ostream in
     */
    virtual void write(std::ostream &out, Endianness endianness) = 0;

    /**
     * @brief Get the internal tag type of the tag
     * @return The internal tag type of the tag
     */
    TagType identify();

    /**
     * @brief Shorthand for casting tag to desired tag type
     * @tparam TagT Tag type to cast to
     * @return Tag as TagT&
     * @throws std::runtime_error If the tag cannot be cast to TagT
     */
    template<typename TagT>
    auto &as()
    {
        auto result = dynamic_cast<TagT *>(this);
        if (result == nullptr) {
            throw std::runtime_error("error casting tag to desired type");
        }
        return *result;
    }
};

}

#endif //NBTPP2_TAG_HPP
