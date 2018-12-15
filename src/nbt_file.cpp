#include <utility>
#include <nbtpp2/nbt_file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "nbtpp2/nbt_file.hpp"
#include "nbtpp2/util.hpp"
#include "nbtpp2/read_tag.hpp"

namespace nbtpp2
{

void NbtFile::read(std::istream &in, Endianness endianness)
{
    auto tag_id = read_tag_id(in);
    if (tag_id != TagType::TagCompound) {
        throw std::runtime_error("root tag type must be TAG_Compound");
    }
    root_name = read_string(in, endianness);
    root.reset(&read_tag(tag_id, in, endianness)->as<tags::TagCompound>());
}

void NbtFile::read_gzip(std::istream &in, Endianness endianness)
{
    write_compression = Compression::Gzip;
    boost::iostreams::filtering_istream istream{};
    istream.push(boost::iostreams::gzip_decompressor());
    istream.push(in);
    read(istream, endianness);
}

void NbtFile::read_zlib(std::istream &in, Endianness endianness)
{
    boost::iostreams::filtering_istream istream{};
    istream.push(boost::iostreams::zlib_decompressor());
    istream.push(in);
    read(istream, endianness);
}

void NbtFile::write(std::ostream &out, Endianness endianness)
{
    write_tag_id(root->identify(), out);
    write_string(root_name, out, endianness);
    root->write(out, endianness);
}

void NbtFile::write_gzip(std::ostream &out, Endianness endianness)
{
    boost::iostreams::filtering_ostream ostream{};
    ostream.push(boost::iostreams::gzip_compressor());
    ostream.push(out);
    write(ostream, endianness);
}

void NbtFile::write_zlib(std::ostream &out, Endianness endianness)
{
    boost::iostreams::filtering_ostream ostream{};
    ostream.push(boost::iostreams::zlib_compressor());
    ostream.push(out);
    write(ostream, endianness);
}

void NbtFile::write(const std::string &path, Endianness endianness, Compression compression)
{
    std::ofstream out{path};

    switch (compression) {
    case Compression::Detect:
        switch (write_compression) {
        case Compression::Gzip: write_gzip(out, endianness);
            break;
        case Compression::Zlib: write_zlib(out, endianness);
            break;
        default: {};
        }
        break;
    case Compression::Gzip: write_gzip(out, endianness);
        break;
    case Compression::Zlib: write_zlib(out, endianness);
        break;
    default: write(out, endianness);
    }
}

NbtFile::NbtFile(const std::string &path, nbtpp2::Endianness endianness, Compression compression)
{
    std::ifstream stream{path, std::ios_base::binary};
    if (!stream) throw std::runtime_error("could not open file");

    switch (compression) {
    case Compression::Detect: {
        switch (stream.peek()) {
        case 0x1f: read_gzip(stream, endianness);
            break;
        case 0x78: read_zlib(stream, endianness);
            break;
        default: read(stream, endianness);
        }
        break;
    }
    case Compression::Gzip: read_gzip(stream, endianness);
        break;
    case Compression::Zlib: read_zlib(stream, endianness);
        break;
    default: read(stream, endianness);
    }
}

NbtFile::NbtFile(std::shared_ptr<tags::TagCompound> root, std::string root_name)
    : root{std::move(root)}, root_name{std::move(root_name)}
{}

NbtFile::NbtFile(std::string root_name)
    : root{std::make_shared<tags::TagCompound>(tags::TagCompound({}))}, root_name{std::move(root_name)}
{}

std::map<std::string, Tag *> &NbtFile::get_root()
{ return root->value; }

Tag *NbtFile::traverse(std::vector<std::string> path_parts)
{ return root->traverse(std::move(path_parts)); }

tags::TagCompound &NbtFile::get_root_tag()
{ return *root; }

bool NbtFile::set_write_compression(Compression compression)
{
    if (compression == Compression::Detect) return false;
    else write_compression = compression;
    return true;
}

}