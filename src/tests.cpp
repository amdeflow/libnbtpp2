#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "nbtpp2/tags/tag_byte.hpp"
#include "nbtpp2/tags/tag_compound.hpp"
#include "nbtpp2/tags/tag_short.hpp"
#include "nbtpp2/tags/tag_int.hpp"
#include "nbtpp2/tags/tag_long.hpp"
#include "nbtpp2/tags/tag_float.hpp"
#include "nbtpp2/tags/tag_double.hpp"
#include "nbtpp2/tags/tag_byte_array.hpp"
#include "nbtpp2/tags/tag_string.hpp"
#include "nbtpp2/tags/tag_list.hpp"
#include "nbtpp2/tags/tag_compound.hpp"
#include "nbtpp2/tags/tag_int_array.hpp"
#include "nbtpp2/tags/tag_long_array.hpp"
#include "nbtpp2/nbt_file.hpp"

template <typename T, typename TUnsigned>
void as_bytes(const T * in, std::size_t in_size, std::vector<char> &output, nbtpp2::Endianness endianness) {
    for (auto i = 0; i < in_size; ++i) {
        for (auto &c: nbtpp2::ConvertToChar<TUnsigned>{
            nbtpp2::optional_reverse_uint(nbtpp2::Convert<T, TUnsigned>{
                    in[i]
                }.b, endianness
            )
        }.chars) {
            output.push_back(c);
        }
    }
}

template<typename T, typename TUnsigned>
void as_bytes(std::vector<T> vector, std::vector<char> &output, nbtpp2::Endianness endianness)
{
    as_bytes<T, TUnsigned>(vector.data(), vector.size(), output, endianness);
}

struct membuf: std::streambuf
{
    membuf(char *begin, char *end)
    {
        this->setg(begin, begin, end);
    }
};

TEST_CASE("TAG_Byte", "[tag_byte]")
{
    char contents[] = {0x20};
    auto buf = membuf(contents, contents + sizeof(contents));
    std::istream stream(&buf);

    auto t = nbtpp2::tags::TagByte::read(stream);
    REQUIRE(t->value == 32);
    delete t;
}

TEST_CASE("TAG_Short", "[tag_short]")
{
    char contents[] = {0x20, 0x20};
    auto buf = membuf(contents, contents + sizeof(contents));
    std::istream stream(&buf);

    auto t = nbtpp2::tags::TagShort::read(stream, nbtpp2::Endianness::Big);
    REQUIRE(t->value == 8224);
    delete t;
}

TEST_CASE("TAG_Int", "[tag_int]")
{
    char contents[] = {0x01, 0x10, 0x01, 0x10};
    auto buf = membuf(contents, contents + sizeof(contents));
    std::istream stream(&buf);

    auto t = nbtpp2::tags::TagInt::read(stream, nbtpp2::Endianness::Big);
    REQUIRE(t->value == 17826064);
    delete t;
}

TEST_CASE("TAG_Long", "[tag_long]")
{
    char contents[] = {0x01, 0x10, 0x01, 0x10, 0x01, 0x10, 0x01, 0x10};
    auto buf = membuf(contents, contents + sizeof(contents));
    std::istream stream(&buf);

    auto t = nbtpp2::tags::TagLong::read(stream, nbtpp2::Endianness::Big);
    REQUIRE(t->value == 76562361914229008);
    delete t;
}

TEST_CASE("TAG_Float", "[tag_float]")
{
    std::uint8_t contents[] = {0x43, 0x8C, 0x0F, 0xBE};
    auto buf = membuf(reinterpret_cast<char *>(contents), reinterpret_cast<char *>(contents) + sizeof(contents));
    std::istream stream(&buf);

    auto t = nbtpp2::tags::TagFloat::read(stream, nbtpp2::Endianness::Big);
    REQUIRE(t->value == 280.123f);
    delete t;
}

TEST_CASE("TAG_Double", "[tag_double]")
{
    std::uint8_t contents[] = {0x40, 0x71, 0x81, 0xF9, 0xAC, 0xFF, 0xA7, 0xEB};
    auto buf = membuf(reinterpret_cast<char *>(contents), reinterpret_cast<char *>(contents) + sizeof(contents));
    std::istream stream(&buf);

    auto t = nbtpp2::tags::TagDouble::read(stream, nbtpp2::Endianness::Big);
    REQUIRE(t->value == 280.123456);
    delete t;
}

auto random_string(std::vector<std::pair<char, char>> constraints, std::size_t len)
{
    auto out = std::string();
    std::random_device generator;
    auto constraint_distribution = std::uniform_int_distribution<std::size_t>(0, constraints.size() - 1);

    for (; len > 0; --len) {
        auto picked_constraint = constraints[constraint_distribution(generator)];
        auto distribution = std::uniform_int_distribution<char>(picked_constraint.first, picked_constraint.second);
        out += distribution(generator);
    }

    return out;
}

template<typename T, typename TUnsigned, TUnsigned t_unsigned_max>
auto random_t_array(std::size_t len, TUnsigned minimum)
{
    auto out = std::vector<T>();

    std::random_device generator;
    std::uniform_int_distribution<TUnsigned> distribution(minimum, t_unsigned_max);

    for (; len > 0; --len) {
        out.push_back(nbtpp2::Convert<TUnsigned, T>{distribution(generator)}.b);
    }

    return out;
}

TEST_CASE("TAG_String", "[tag_string]")
{
    GIVEN("A random string of numbers and letters with the length of 257") {
        auto random_str = random_string({{'0', '9'}, {'A', 'Z'}, {'a', 'z'}}, 1024);
        auto random_array_bytes = std::vector<char>{0x04, 0x00};
        as_bytes<char, std::uint8_t>(random_str.data(), random_str.size(), random_array_bytes, nbtpp2::Endianness::Big);
        auto buf = membuf(random_array_bytes.data(), random_array_bytes.data() + random_array_bytes.size());
        std::istream stream{&buf};

        auto t = nbtpp2::tags::TagString::read(stream, nbtpp2::Endianness::Big);
        REQUIRE(t->value == random_str);
        delete t;
    }
}

TEST_CASE("TAG_Byte_Array", "[tag_byte_array]")
{
    GIVEN("A random array of bytes with the length of 1024") {
        auto random_array = random_t_array<std::int8_t, std::uint8_t, UINT8_MAX>(1024, 1);
        auto random_array_bytes = std::vector<char>{0x00, 0x00, 0x04, 0x00};
        as_bytes<std::int8_t, std::uint8_t>(random_array, random_array_bytes, nbtpp2::Endianness::Big);
        auto buf = membuf(random_array_bytes.data(), random_array_bytes.data() + random_array_bytes.size());
        std::istream stream{&buf};

        auto t = nbtpp2::tags::TagByteArray::read(stream, nbtpp2::Endianness::Big);
        REQUIRE(t->value == random_array);
        delete t;
    }
}

TEST_CASE("TAG_List", "[tag_list]")
{
    GIVEN("A TAG_List of TAG_Short items") {
        auto bytes = std::vector<char>{static_cast<char>(nbtpp2::TagType::TagShort), 0x00, 0x00, 0x00, 0x04};
        auto push_short = [&](std::int16_t val)
        {
            auto convert = nbtpp2::ConvertToChar<std::uint16_t>{
                nbtpp2::optional_reverse_uint<std::uint16_t>(
                    nbtpp2::Convert<std::int16_t, std::uint16_t>{
                        val
                    }.b, nbtpp2::Endianness::Big
                )
            };

            bytes.push_back(convert.chars[0]);
            bytes.push_back(convert.chars[1]);
        };
        auto short_array = std::vector<std::int16_t>{501, 930, -6860, -2200};
        for (auto &s: short_array) { push_short(s); }

        auto buf = membuf(bytes.data(), bytes.data() + bytes.size());
        std::istream stream(&buf);

        auto t = nbtpp2::tags::TagList::read(stream, nbtpp2::Endianness::Big);

        auto same = [&]()
        {
            auto i = std::size_t(0);
            for (auto &elem: t->value) {
                if (elem->as<nbtpp2::tags::TagShort>().value != short_array[i])return false;
                ++i;
            }
            return true;
        };

        REQUIRE(same());
        delete t;
    }
}

TEST_CASE("TAG_Compound", "[tag_compound]")
{
    GIVEN("A TAG_Compound filled with tags") {
        auto f = nbtpp2::NbtFile("bigtest.nbt", nbtpp2::Endianness::Big);

        using namespace nbtpp2;
        auto t = tags::TagCompound({
            {"Hello, World!", new tags::TagInt(3)},
            {"Bye, World!", new tags::TagCompound({
                    {"test", new tags::TagList({
                            new tags::TagByte('a'),
                            new tags::TagByte('b'),
                        }
                    )},
                }
            )},
        });

        REQUIRE(f.get_root()
        ["byteArrayTest (the first 1000 values of (n*n*255+n*7)%100, starting with n=0 (0, 62, 34, 16, 8, ...))"]
            ->as<nbtpp2::tags::TagByteArray>().value.size() == 1000);

        std::cout << f.get_root()["nested compound test"]
            ->as<nbtpp2::tags::TagCompound>().value["egg"]
            ->as<nbtpp2::tags::TagCompound>().value["name"]
            ->as<nbtpp2::tags::TagString>().value
            << std::endl;

        f.write("bigtest_out.nbt", Endianness::Big);
    }
}

TEST_CASE("TAG_Int_Array", "[tag_int_array]")
{
    GIVEN("A random array of integers with the length of 1024") {
        auto random_array = random_t_array<std::int32_t, std::uint32_t, UINT32_MAX>(1024, 0);
        auto random_array_bytes = std::vector<char>{0x00, 0x00, 0x04, 0x00};
        as_bytes<std::int32_t, std::uint32_t>(random_array, random_array_bytes, nbtpp2::Endianness::Big);
        auto buf = membuf(random_array_bytes.data(), random_array_bytes.data() + random_array_bytes.size());
        std::istream stream(&buf);

        auto t = nbtpp2::tags::TagIntArray::read(stream, nbtpp2::Endianness::Big);
        REQUIRE(t->value == random_array);
        delete t;
    }
}

TEST_CASE("TAG_Long_Array", "[tag_long_array]")
{
    GIVEN("A random array of integers with the length of 1024") {
        auto random_array = random_t_array<std::int64_t, std::uint64_t, UINT64_MAX>(1024, 0);
        auto random_array_bytes = std::vector<char>{0x00, 0x00, 0x04, 0x00};
        as_bytes<std::int64_t, std::uint64_t>(random_array, random_array_bytes, nbtpp2::Endianness::Big);
        auto buf = membuf(random_array_bytes.data(), random_array_bytes.data() + random_array_bytes.size());
        std::istream stream(&buf);

        auto t = nbtpp2::tags::TagLongArray::read(stream, nbtpp2::Endianness::Big);
        REQUIRE(t->value == random_array);
        delete t;
    }
}