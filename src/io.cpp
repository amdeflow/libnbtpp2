#include <nbtpp2/io.hpp>


namespace nbtpp2
{

IstreamReader::IstreamReader(std::istream *istream)
    : istream(istream)
{}

void IstreamReader::read(char *buf, std::uint32_t n)
{
    istream->read(buf, n);
}

OstreamWriter::OstreamWriter(std::ostream *ostream)
    : ostream(ostream)
{}

void OstreamWriter::write(const char *buf, std::uint32_t n)
{
    ostream->write(buf, n);
}

FileReader::FileReader(FILE *file)
    : file(file)
{}

void FileReader::read(char *buf, std::uint32_t n)
{
    std::fread(buf, sizeof(*buf), n, file);
}

FileWriter::FileWriter(FILE *file)
    : file(file)
{}

void FileWriter::write(const char *buf, std::uint32_t n)
{
    fwrite(buf, sizeof(*buf), n, file);
}

GzReader::GzReader(gzFile file)
    : file(file)
{}

void GzReader::read(char *buf, std::uint32_t n)
{
    gzread(file, buf, n);
}

GzWriter::GzWriter(gzFile file)
    : file(file)
{}

void GzWriter::write(const char *buf, std::uint32_t n)
{
    gzwrite(file, buf, n);
}

ZlibReader::ZlibReader(FILE *file)
    : file(file)
{
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    ret = inflateInit(&stream);
    if (ret != Z_OK)
        throw std::runtime_error("Could not initialize deflate");

    std::fseek(file, 0, SEEK_END);
    file_size = static_cast<std::int64_t>(std::ftell(file));
    std::rewind(file);

    stream.next_in = buf;
}

void ZlibReader::read_buf()
{
    std::size_t n_possible = CHUNK;
    if (file_size - file_read < CHUNK)
        n_possible = file_size - file_read;

    if (buf_used < n_possible) {
        std::size_t free = (CHUNK - buf_used);
        std::size_t n_to_read = free > n_possible ? n_possible : free;
        auto actually_read = std::fread(buf + buf_used, sizeof(char), n_to_read, file);
        if (actually_read != n_to_read)
            throw std::runtime_error("Could not read desired amount of bytes from file");

        buf_used += actually_read;
        file_read += actually_read;

        stream.avail_in += actually_read;
    }
}

void ZlibReader::buffer_shift_back(std::size_t amount) {
    for (; amount > 0; amount--) {
        for (std::size_t i = 0; i < buf_used && i < CHUNK; i++) {
            buf[i] = buf[i+1];
        }
    }
}

void ZlibReader::read(char *data, std::uint32_t n)
{
    std::size_t prior_total = stream.total_in;
    std::size_t cur_read = 0;

    while (cur_read < n) {
        read_buf();

        if (file_size - stream.total_in < n - cur_read)
            throw std::runtime_error("File is not big enough");

        stream.next_out = (unsigned char *) data;
        stream.avail_out = n;
        ret = inflate(&stream, Z_SYNC_FLUSH);
        if (ret != Z_OK && ret != Z_STREAM_END && ret != Z_NEED_DICT)
            throw std::runtime_error("Could not inflate file");

        cur_read = stream.total_in - prior_total;
        buffer_shift_back(cur_read);
        stream.next_in = buf;
    }
}

ZlibReader::~ZlibReader()
{
    inflateEnd(&stream);
}

void ZlibWriter::write_internal(const char *buf, std::uint32_t n, bool flush)
{
    stream.avail_in = n;
    stream.next_in = (unsigned char *) buf;

    do {
        stream.avail_out = CHUNK;
        stream.next_out = out;

        ret = deflate(&stream, flush ? Z_FINISH : Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR) throw std::runtime_error("Error while trying to deflate");

        have = CHUNK - stream.avail_out;
        if (have == 0) continue;
        if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
            deflateEnd(&stream);
            throw std::runtime_error("Error writing to destination");
        }
    }
    while (stream.avail_out == 0);
    if (stream.avail_in != 0) throw std::runtime_error("Error while trying to deflate");
}

ZlibWriter::ZlibWriter(FILE *dest, std::int32_t level)
    : dest(dest)
{
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    ret = deflateInit(&stream, level);
    if (ret != Z_OK)
        throw std::runtime_error("Could not initialize deflate");
}

void ZlibWriter::write(const char *buf, std::uint32_t n)
{
    write_internal(buf, n, false);
}

ZlibWriter::~ZlibWriter()
{
    write_internal(nullptr, 0, true);
    deflateEnd(&stream);
}

}
