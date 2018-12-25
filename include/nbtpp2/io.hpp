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
    char * buf = nullptr;

public:
    explicit ZlibReader(FILE *file)
        : file(file)
    {
        fseek(file, 0, SEEK_END);
        auto file_size = static_cast<std::int64_t>(ftell(file));
        rewind(file);
        deflateInit(stream, DEFLATE_LEVEL);
    }

    void read(char *buf, std::uint32_t n) override
    {
        auto nread = fread(buf, sizeof(*buf), CHUNK, file);
        stream->next_in = (std::uint8_t *) buf;
        stream->total_in = n;
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
    z_stream *stream;

public:
    explicit ZlibWriter(z_stream *stream)
        : stream(stream)
    {}

    void write(const char *buf, std::uint32_t n) override
    {
        stream->next_out = (std::uint8_t *) buf;
        stream->avail_out = n;
        inflate(stream, false);
    }
};

}

#endif //NBTPP2_IO_HPP
