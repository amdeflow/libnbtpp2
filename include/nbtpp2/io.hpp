#ifndef NBTPP2_IO_HPP
#define NBTPP2_IO_HPP

#include <cstdint>
#include <istream>
#include <ostream>
#include <zlib.h>
#include <nbtpp2/converters.hpp>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#   include <fcntl.h>
#   include <io.h>
#   define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#   define SET_BINARY_MODE(file)
#endif

#if defined(WIN32)
    #define _CRT_SECURE_NO_DEPRECATE
#endif

namespace nbtpp2
{

const unsigned int DEFLATE_LEVEL = 5;
const unsigned int CHUNK = 16384;

class BinaryReader
{
public:
    // Read buffer from stream
    virtual void read(char *buf, std::uint32_t n) = 0;
};

class BinaryWriter
{
public:
    // Write buffer to stream
    virtual void write(const char *buf, std::uint32_t n) = 0;
};

class IStreamReader: public BinaryReader
{
    std::istream *istream;

public:
    explicit IStreamReader(std::istream *istream)
        : istream(istream)
    {}

    void read(char *buf, std::uint32_t n) override
    {
        istream->read(buf, n);
    }
};

class OstreamWriter: public BinaryWriter
{
    std::ostream *ostream;

public:
    explicit OstreamWriter(std::ostream *ostream)
        : ostream(ostream)
    {}

    void write(const char *buf, std::uint32_t n) override
    {
        ostream->write(buf, n);
    }
};

class FileReader: public BinaryReader
{
    FILE *file;

public:
    explicit FileReader(FILE *file)
        : file(file)
    {}

    void read(char *buf, std::uint32_t n) override
    {
        fread(buf, sizeof(*buf), n, file);
    }
};

class FileWriter: public BinaryWriter
{
    FILE *file;

public:
    explicit FileWriter(FILE *file)
        : file(file)
    {}

    void write(const char *buf, std::uint32_t n) override
    {
        fwrite(buf, sizeof(*buf), n, file);
    }
};

class GzReader: public BinaryReader
{
    gzFile file;

public:
    explicit GzReader(gzFile file)
        : file(file)
    {}

    void read(char *buf, std::uint32_t n) override
    {
        gzread(file, buf, n);
    }
};

class GzWriter: public BinaryWriter
{
    gzFile file;

public:
    explicit GzWriter(gzFile file)
        : file(file)
    {}

    void write(const char *buf, std::uint32_t n) override
    {
        gzwrite(file, buf, n);
    }
};

class ZlibReader: public BinaryReader
{
    FILE *file;
    z_stream *stream = {};
    std::uint8_t * buf = nullptr;
    std::size_t buf_used = 0;

public:
    explicit ZlibReader(FILE *file)
        : file(file)
    {
        fseek(file, 0, SEEK_END);
        auto file_size = static_cast<std::int64_t>(ftell(file));
        rewind(file);
        deflateInit(stream, DEFLATE_LEVEL);
        stream->next_in = this->buf;
    }

    void read_buf() {
        buf_used += fread(this->buf, sizeof(*this->buf), CHUNK - buf_used, file);
    }

    void read(char *buf, std::uint32_t n) override
    {
        if (buf_used <= n) read_buf();
        stream->total_in = buf_used;
        stream->avail_in = n;
        stream->avail_out = n;
        stream->total_out = n;
        stream->next_out = (std::uint8_t *) buf;
        deflate(stream, false);
    }

    ~ZlibReader()
    {
        deflateEnd(stream);
        delete buf;
    }
};

class ZlibWriter: public BinaryWriter
{
    std::int32_t ret = 0;
    std::uint32_t have = 0;
    z_stream stream = z_stream{};
    std::uint8_t in[CHUNK] = {0};
    std::uint8_t out[CHUNK] = {0};
    FILE *dest;

    void write_internal(const char *buf, std::uint32_t n, bool flush) {
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
        } while (stream.avail_out == 0);
        if (stream.avail_in != 0) throw std::runtime_error("Error while trying to deflate");
    }

public:
    explicit ZlibWriter(FILE *dest, std::int32_t level)
        : dest(dest)
    {
        stream.zalloc = Z_NULL;
        stream.zfree = Z_NULL;
        stream.opaque = Z_NULL;
        ret = deflateInit(&stream, level);
        if (ret != Z_OK)
            throw std::runtime_error("Could not initialize deflate");
    }

    void write(const char *buf, std::uint32_t n) override
    {
        write_internal(buf, n, false);
    }

    ~ZlibWriter() {
        write_internal(nullptr, 0, true);
        deflateEnd(&stream);
    }
};

}

#endif //NBTPP2_IO_HPP
