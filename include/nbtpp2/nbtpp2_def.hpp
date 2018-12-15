#ifndef NBTPP2_NBTPP2_DEF_HPP
#define NBTPP2_NBTPP2_DEF_HPP

#include <string>
namespace nbtpp2
{

const int VERSION_MAJOR = 1;

const int VERSION_MINOR = 0;

const int VERSION_PATCH = 0;

std::string ver_str() {
    return std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "." + std::to_string(VERSION_PATCH);
}

}

#endif //NBTPP2_NBTPP2_DEF_HPP
