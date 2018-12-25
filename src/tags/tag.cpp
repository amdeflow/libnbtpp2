#include <nbtpp2/tag.hpp>

namespace nbtpp2
{

Tag::Tag(TagType type)
    : type{type}
{}

TagType Tag::identify()
{
    return type;
}

}