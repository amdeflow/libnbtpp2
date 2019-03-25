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

class IstreamReader: public BinaryReader
{
    std::istream *istream;

public:
    explicit IstreamReader(std::istream *istream);

    void read(char *buf, std::uint32_t n) override;
};

class OstreamWriter: public BinaryWriter
{
    std::ostream *ostream;

public:
    explicit OstreamWriter(std::ostream *ostream);

    void write(const char *buf, std::uint32_t n) override;
};

class FileReader: public BinaryReader
{
    FILE *file;

public:
    explicit FileReader(FILE *file);

    void read(char *buf, std::uint32_t n) override;
};

class FileWriter: public BinaryWriter
{
    FILE *file;

public:
    explicit FileWriter(FILE *file);

    void write(const char *buf, std::uint32_t n) override;
};

class GzReader: public BinaryReader
{
    gzFile file;

public:
    explicit GzReader(gzFile file);

    void read(char *buf, std::uint32_t n) override;
};

class GzWriter: public BinaryWriter
{
    gzFile file;

public:
    explicit GzWriter(gzFile file);

    void write(const char *buf, std::uint32_t n) override;
};

class ZlibReader: public BinaryReader
{
    FILE *file;
    z_stream stream = z_stream{};
    std::uint8_t *buf = nullptr;
    std::size_t buf_used = 0;
    std::size_t file_size = 0;
    std::int32_t ret = 0;

    void buffer_shift_back(std::size_t amount);

public:
    explicit ZlibReader(FILE *file);

    void read_buf();

    void read(char *data, std::uint32_t n) override;

    ~ZlibReader();
};

class ZlibWriter: public BinaryWriter
{
    std::int32_t ret = 0;
    std::uint32_t have = 0;
    z_stream stream = z_stream{};
    std::uint8_t in[CHUNK] = {0};
    std::uint8_t out[CHUNK] = {0};
    FILE *dest;

    void write_internal(const char *buf, std::uint32_t n, bool flush);

public:
    explicit ZlibWriter(FILE *dest, std::int32_t level);

    void write(const char *buf, std::uint32_t n) override;

    ~ZlibWriter();
};

}

#endif //NBTPP2_IO_HPP
