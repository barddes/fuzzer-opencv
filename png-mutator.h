//
// Created by barddes on 21/04/2021.
//

#ifndef FUZZER_OPENCV_PNG_MUTATOR_H
#define FUZZER_OPENCV_PNG_MUTATOR_H

#include <ostream>
#include <vector>

#define PNG_HEADER "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"

class Png {
public:
    class Chunk {
    public:
        uint32_t length;
        uint8_t name[4];
        std::vector<uint8_t> data;
        uint32_t crc;
    };

    Png() {};
    Png(const char* filename);
    uint32_t width();
    uint32_t height();

    std::vector<Chunk> chunks;

    void load_raw_data(const std::vector<uint8_t>& data);

private:

    std::vector<uint8_t> _raw;
    bool _ihdr = false;
    bool _plte = false;
    bool _idat = false;
    bool _iend = false;

    uint32_t _width{};
    uint32_t _height{};
    uint8_t _bit_depth{};
    uint8_t _color_type{};
    uint8_t _compression_method{};
    uint8_t _filter_method{};
    uint8_t _interlace_method{};

    static std::vector<uint8_t> _read_file(const char *filename);
    void _parse_raw();

    void _load_ihdr(Chunk &c);
};

#endif //FUZZER_OPENCV_PNG_MUTATOR_H
