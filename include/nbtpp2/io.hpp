#ifndef NBTPP2_INPUT_STREAM_HPP
#define NBTPP2_INPUT_STREAM_HPP

#include <cstdint>
#include <istream>
#include <ostream>
#include <zlib.h>
#include <nbtpp2/converters.hpp>

namespace nbtpp2
{

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
    std::istream *in;

public:
    explicit IStreamReader(std::istream *in)
        : in(in)
    {}

    void read(char *buf, std::uint32_t n) override
    {
        in->read(buf, n);
    }
};

class OStreamWriter: public BinaryWriter
{
    std::ostream *out;

public:
    explicit OStreamWriter(std::ostream *out)
        : out(out)
    {}

    void write(const char *buf, std::uint32_t n) override
    {
        out->write(buf, n);
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
    z_stream *stream;

public:
    explicit ZlibReader(z_stream *stream)
        : stream(stream)
    {}

    void read(char *buf, std::uint32_t n) override
    {
        stream->next_in = (unsigned char *) buf;
        stream->avail_in = n;
        deflate(stream, false);
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
        stream->next_out = (unsigned char *) buf;
        stream->avail_out = n;
        inflate(stream, false);
    }
};

}

#endif //NBTPP2_INPUT_STREAM_HPP
