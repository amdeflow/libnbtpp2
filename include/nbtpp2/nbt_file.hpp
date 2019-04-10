#ifndef NBTPP2_NBT_FILE_HPP
#define NBTPP2_NBT_FILE_HPP

#include <nbtpp2/tags/tag_compound.hpp>
#include <nbtpp2/io.hpp>

#include <fstream>
#include <memory>

/// @brief The namespace where all nbtpp2 functions and classes are located
namespace nbtpp2
{

/**
 * @class NbtFile
 * @brief NBT file container with read and write support
 */
class NbtFile
{
public:
    /**
     * @enum Compression
     * @brief Compression type for reading and writing NBT files
     */
    enum class Compression
    {
        Detect, ///< Detects compression when reading, uses reading compression when writing (or none when constructor was called with the default parameter)
        Gzip, ///< Uses gzip compression
        Zlib, ///< Uses zlib compression
        None, ///< Disables compression
    };
private:
    /// The root tag
    std::shared_ptr<Tag> root;

    /// The compression used for writing the NbtFile
    Compression write_compression = Compression::None;

    /**
     * @brief Reads reader contents to {@link root_name} and {@link root}
     * @param reader BinaryReader to read from
     * @param endianness Endianness to read from the istream in
     */
    void read(BinaryReader &reader, nbtpp2::Endianness endianness);

    /**
     * @brief Reads gzip-compressed file
     * @param path Path to read from
     * @param endianness Endianness to read from the istream in
     */
    void read_gzip(const std::string &path, nbtpp2::Endianness endianness);

    /**
     * @brief Reads zlib-compressed file
     * @param path Path to read from
     * @param endianness Endianness to read from the istream in
     */
    void read_zlib(const std::string &path, nbtpp2::Endianness endianness);

    /**
     * @brief Writes {@link root_name} and {@link root} to a BinaryWriter
     * @param writer BinaryWriter to write to
     * @param endianness endianness to write to the ostream (@p out) in
     */
    void write(BinaryWriter &writer, nbtpp2::Endianness endianness);

    /**
     * @brief Writes file as gzip-compressed NBT file
     * @param path Path to write to
     * @param endianness Endianness to write in
     */
    void write_gzip(const std::string &path, nbtpp2::Endianness endianness);

    /**
     * @brief Writes file as zlib-compressed NBT file
     * @param path Path to write to
     * @param endianness Endianness to write in
     */
    void write_zlib(const std::string &path, nbtpp2::Endianness endianness);

public:
    /// The name of the root TAG_Compound. Used for writing to a file.
    std::string root_name;

    /**
     * @brief Construct an NbtFile by reading from an NBT file
     * @param path Path of the NBT file to open
     * @param endianness Endianness of the NBT file to open
     * @param compression Compression used in the file (detected automatically by default)
     */
    NbtFile(const std::string &path, nbtpp2::Endianness endianness, Compression compression = Compression::Detect);

    /**
     * @brief Construct an NbtFile with a root and root name
     * @param root Pointer to TAG_Compound tag
     * @param root_name Name of the root (TAG_Compound) tag
     * @note This constructor does not set {@link write_compression} by default. Use {@link set_write_compression} to set the write compression
     */
    NbtFile(std::shared_ptr<tags::TagCompound> root, std::string root_name);

    /**
     * @brief Construct an NbtFile
     * @param root_name Name of the root (TAG_Compound) tag
     */
    explicit NbtFile(std::string root_name = "");

    /**
     * @brief Write {@link root_name} with {@link root} TAG_Compound to @p path
     * @param path Path to write the NbtFile to
     * @param endianness Endianness to write the NbtFile in
     * @param compression The compression used for compressing the NbtFile (compression set by the constructor)
     */
    void write(const std::string &path, nbtpp2::Endianness endianness, Compression compression = Compression::Detect);

    /**
     * @brief Get the root TAG_Compound contents of the NbtFile
     * @return Root TAG_Compound contents of the NbtFile
     */
    std::map<std::string, Tag *> &get_root_tag_compound();

    /**
     * @brief Get the root Tag of the NbtFile
     * @return Root Tag of the NbtFile
     */
    Tag &get_root_tag();

    /**
     * @param compression Compression to set the NbtFile's compression to
     * @return Success
     * @note Compression must not be Compression::Detect. The function will not set {@link write_compression} and return false.
     */
    bool set_write_compression(Compression compression);
};

}

#endif //NBTPP2_NBT_FILE_HPP
