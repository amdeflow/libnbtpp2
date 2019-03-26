#include <utility>
#include <nbtpp2/nbt_file.hpp>
#include <zlib.h>

#include <nbtpp2/nbt_file.hpp>
#include <nbtpp2/util.hpp>
#include <cstdio>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

namespace nbtpp2
{

void NbtFile::read(BinaryReader &reader, Endianness endianness)
{
    auto tag_id = read_tag_id(reader);
    root_name = read_string(reader, endianness);
    root.reset(read_tag(tag_id, reader, endianness));
}

void NbtFile::read_gzip(const std::string &path, Endianness endianness)
{
    write_compression = Compression::Gzip;
    auto file = gzopen(path.c_str(), "rb");
    auto reader = GzReader{file};
    read(reader, endianness);
    gzclose(file);
}

void NbtFile::read_zlib(const std::string &path, Endianness endianness)
{
    auto file = fopen(path.c_str(), "rb");
    auto reader = ZlibReader{file};
    read(reader, endianness);
    fclose(file);
}

void NbtFile::write(BinaryWriter &writer, Endianness endianness)
{
    write_tag_id(root->identify(), writer);
    write_string(root_name, writer, endianness);
    root->write(writer, endianness);
}

void NbtFile::write_gzip(const std::string &path, Endianness endianness)
{
    auto file = gzopen(path.c_str(), "wb");
    auto writer = GzWriter{file};
    write(writer, endianness);
    gzclose(file);
}

void NbtFile::write_zlib(const std::string &path, Endianness endianness)
{
    auto file = fopen(path.c_str(), "wb");
    {
        auto writer = ZlibWriter{file, DEFLATE_LEVEL};
        write(writer, endianness);
    }
    fclose(file);
}

void NbtFile::write(const std::string &path, Endianness endianness, Compression compression)
{
    switch (compression) {
    case Compression::Detect:
        switch (write_compression) {
        case Compression::Gzip: write_gzip(path, endianness);
            break;
        case Compression::Zlib: write_zlib(path, endianness);
            break;
        default:;
        }
        break;
    case Compression::Gzip: write_gzip(path, endianness);
        break;
    case Compression::Zlib: write_zlib(path, endianness);
        break;
    default: {
        auto file = fopen(path.c_str(), "wb");
        auto writer = FileWriter{file};
        write(writer, endianness);
        fclose(file);
    }
    }
}

NbtFile::NbtFile(const std::string &path, nbtpp2::Endianness endianness, Compression compression)
{
    std::ifstream stream{path, std::ios_base::binary};
    if (!stream) throw std::runtime_error("could not open file");
    int first_byte = stream.peek();
    stream.close();

    switch (compression) {
    case Compression::Detect: {
        switch (first_byte) {
        case 0x1f: read_gzip(path, endianness);
            return;
        case 0x78: read_zlib(path, endianness);
            return;
        default:;
        }
    }
    case Compression::Gzip: read_gzip(path, endianness);
        return;
    case Compression::Zlib: read_zlib(path, endianness);
        return;
    default: {
        auto file = fopen(path.c_str(), "rb");
        auto reader = FileReader{file};
        read(reader, endianness);
        fclose(file);
    }
    }
}

NbtFile::NbtFile(std::shared_ptr<tags::TagCompound> root, std::string root_name)
    : root{std::move(root)}, root_name{std::move(root_name)}
{}

NbtFile::NbtFile(std::string root_name)
    : root{std::make_shared<tags::TagCompound>(tags::TagCompound({}))}, root_name{std::move(root_name)}
{}

std::map<std::string, Tag *> &NbtFile::get_root_tag_compound()
{ return root->as<tags::TagCompound>().value; }

Tag &NbtFile::get_root_tag()
{ return *root; }

bool NbtFile::set_write_compression(Compression compression)
{
    if (compression == Compression::Detect) return false;
    else write_compression = compression;
    return true;
}

}